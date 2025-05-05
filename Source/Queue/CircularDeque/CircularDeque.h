#include <vector>

class MyCircularDeque 
{
public:
    MyCircularDeque() = delete;
    ~MyCircularDeque() = default;

    MyCircularDeque(const MyCircularDeque& other) = delete;
    MyCircularDeque& operator=(const MyCircularDeque& other) = delete;

    MyCircularDeque(MyCircularDeque&& other) = delete;
    MyCircularDeque& operator=(MyCircularDeque&& other) = delete;

    MyCircularDeque(int k);
    
    bool InsertFront(int value);
    bool InsertLast(int value);
    
    bool DeleteFront();
    bool DeleteLast();

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
        return m_count == m_queueSize;
    }

private:
    std::vector<int> m_storage;

    int m_count;
    int m_front;
    int m_back;

    const int m_queueSize;
};