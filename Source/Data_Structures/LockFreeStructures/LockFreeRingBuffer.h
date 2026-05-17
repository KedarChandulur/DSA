#pragma once

#include <cstdint>
#include <atomic>
#include <vector>
#include <cassert>

/*
*  Single-Producer Single-Consumer (SPSC) lock-free ring buffer.
*
*  SIZE is now a runtime parameter passed to the constructor.
*  This allows the buffer size to be calculated at runtime
*
*  Uses % for wrapping instead of & to support non-power-of-2 sizes.
*
*  One slot is intentionally left unused to distinguish full from empty:
*    Empty : head == tail
*    Full  : (tail + 1) % m_Size == head
*
*  Memory ordering per operation:
*    Push: reads head with acquire (checks full), stores tail with release (signals data ready)
*    Pop : reads tail with acquire (checks empty), stores head with release (signals slot free)
*/
template<typename Data>
class LockFreeRingBuffer
{
public:
    ~LockFreeRingBuffer() = default;

    LockFreeRingBuffer() = delete;
    LockFreeRingBuffer(const LockFreeRingBuffer& _other) = delete;
    LockFreeRingBuffer& operator=(const LockFreeRingBuffer& _other) = delete;
    LockFreeRingBuffer(LockFreeRingBuffer&& _other) = delete;
    LockFreeRingBuffer& operator=(LockFreeRingBuffer&& _other) = delete;

    explicit LockFreeRingBuffer(uint32_t _size)
        : m_Buffer(_size),
          m_Head(0),
          m_Tail(0),
          m_Size(_size)
    {
        assert(_size >= 2 && "LockFreeRingBuffer size must be at least 2");

        static_assert(std::atomic<uint32_t>::is_always_lock_free,
                      "atomic<uint32_t> is NOT lock-free on this platform");
    }

    bool Push(const Data& _item)
    {
        const uint32_t tail = m_Tail.load(std::memory_order_relaxed);
        const uint32_t nextTail = (tail + 1) % m_Size;

        if (nextTail == m_Head.load(std::memory_order_acquire))
        {
            return false; // Buffer full
        }

        m_Buffer[tail] = _item;

        // Release: guarantees m_Buffer[tail] write is visible to consumer
        // before the tail pointer update is observed.
        m_Tail.store(nextTail, std::memory_order_release);

        return true;
    }

    bool Pop(Data& _item)
    {
        const uint32_t head = m_Head.load(std::memory_order_relaxed);

        if (head == m_Tail.load(std::memory_order_acquire))
        {
            return false; // Buffer empty
        }

        _item = m_Buffer[head];

        // Release: signals producer that this slot is now free to write into.
        m_Head.store((head + 1) % m_Size, std::memory_order_release);

        return true;
    }

    inline bool IsEmpty() const
    {
        return m_Head.load(std::memory_order_acquire) ==
               m_Tail.load(std::memory_order_acquire);
    }

    inline bool IsFull() const
    {
        const uint32_t tail = m_Tail.load(std::memory_order_acquire);

        return ((tail + 1) % m_Size) == m_Head.load(std::memory_order_acquire);
    }

    inline uint32_t Capacity() const
    {
        return m_Size - 1; // One slot wasted for full/empty distinction
    }

private:
    std::vector<Data> m_Buffer;

    // alignas(64) places head and tail on separate 64-byte cache lines.
    // Without this, both atomics share a cache line causing false sharing:
    // every producer write invalidates the consumer's cache line and vice versa,
    // adding unnecessary cache coherence traffic between cores.
    alignas(64) std::atomic<uint32_t> m_Head;
    alignas(64) std::atomic<uint32_t> m_Tail;

    uint32_t m_Size;
};