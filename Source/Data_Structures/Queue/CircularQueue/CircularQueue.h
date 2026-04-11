#include <vector>

class MyCircularQueue 
{
public:
    MyCircularQueue() = delete;
    ~MyCircularQueue() = default;

    MyCircularQueue(const MyCircularQueue& other) = delete;
    MyCircularQueue& operator=(const MyCircularQueue& other) = delete;

    MyCircularQueue(MyCircularQueue&& other) = delete;
    MyCircularQueue& operator=(MyCircularQueue&& other) = delete;

    MyCircularQueue(const int k);
    
    const bool EnQueue(const int value);
    const bool DeQueue();
    void RunDemo();
    
    inline const int GetFront() const
    {
        return m_storage[m_front];
    }
    
    inline const int GetRear() const
    {
        const int rearIndex = (m_back - 1 + m_queueSize) % m_queueSize;
        return m_storage[rearIndex];
    }
    
    inline const bool IsEmpty() const
    {
        return m_count == 0;
    }
    
    inline const bool IsFull() const
    {
        // https://en.wikipedia.org/wiki/Circular_buffer
        //return (m_back + 1) % m_queueSize == m_front;
        return m_count == m_queueSize;
    }
    
private:
    std::vector<int> m_storage;

    int m_count;
    int m_front;
    int m_back;

    const int m_queueSize;
};