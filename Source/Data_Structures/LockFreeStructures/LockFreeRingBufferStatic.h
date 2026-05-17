#pragma once

#include <cstdint>
#include <atomic>

/*
*  Single-Producer Single-Consumer (SPSC) lock-free ring buffer - Static/Compile-time version.
*
*  SIZE is a compile-time template parameter allowing:
*  - Stack allocation instead of heap (faster, cache friendly)
*  - Bitwise AND wrapping instead of modulo (~1 CPU cycle vs ~20-40 cycles)
*  - Full compiler optimization and inlining
*
*  Limitation: SIZE must be a power of 2 and known at compile time.
*  Memory constraint (<=m) must be manually verified:
*    B1->B2 buffer(4) + sliding window(9) + B2 output buffer(4) = 17 bytes minimum.
*    If m < 17, memory constraint is violated silently.
*
*  Current submission uses LockFreeRingBuffer (runtime version) instead,
*  which correctly satisfies memory constraint for any m >= 16.
*  This file is provided as a performance reference only.
*
*  One slot is intentionally left unused to distinguish full from empty:
*    Empty : head == tail
*    Full  : (tail + 1) & (SIZE - 1) == head
*
*  Memory ordering per operation:
*    Push: reads head with acquire (checks full), stores tail with release (signals data ready)
*    Pop : reads tail with acquire (checks empty), stores head with release (signals slot free)
*/
template<typename Data, uint32_t SIZE>
class LockFreeRingBufferStatic
{
    static_assert(SIZE >= 2, "SIZE must be at least 2");
    static_assert((SIZE & (SIZE - 1)) == 0, "SIZE must be a power of 2");

public:
    ~LockFreeRingBufferStatic() = default;
    LockFreeRingBufferStatic(const LockFreeRingBufferStatic& _other) = delete;
    LockFreeRingBufferStatic& operator=(const LockFreeRingBufferStatic& _other) = delete;
    LockFreeRingBufferStatic(LockFreeRingBufferStatic&& _other) = delete;
    LockFreeRingBufferStatic& operator=(LockFreeRingBufferStatic&& _other) = delete;

    LockFreeRingBufferStatic()
        : m_Buffer(),
          m_Head(0),
          m_Tail(0)
    {
        static_assert(std::atomic<uint32_t>::is_always_lock_free,
            "atomic<uint32_t> is NOT lock-free on this platform");
    }

    bool Push(const Data& _item)
    {
        const uint32_t tail = m_Tail.load(std::memory_order_relaxed);
        const uint32_t nextTail = (tail + 1) & (SIZE - 1);

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
        m_Head.store((head + 1) & (SIZE - 1), std::memory_order_release);

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

        return ((tail + 1) & (SIZE - 1)) == m_Head.load(std::memory_order_acquire);
    }

    inline constexpr uint32_t Capacity() const
    {
        return SIZE - 1; // One slot wasted for full/empty distinction
    }

private:
    Data m_Buffer[SIZE];

    // alignas(64) places head and tail on separate 64-byte cache lines.
    // Without this, both atomics share a cache line causing false sharing:
    // every producer write invalidates the consumer's cache line and vice versa,
    // adding unnecessary cache coherence traffic between cores.
    alignas(64) std::atomic<uint32_t> m_Head;
    alignas(64) std::atomic<uint32_t> m_Tail;
};