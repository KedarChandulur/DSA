#include <iostream>

#include "CircularQueue.h"

MyCircularQueue::MyCircularQueue(const int k)
    : m_count(0), m_front(0), m_back(0), m_queueSize(k)
{
    m_storage.resize(m_queueSize);
    for(int i = 0; i < m_queueSize; ++i)
    {
        m_storage[i] = -1;
    }
}

const bool MyCircularQueue::EnQueue(const int value) 
{
    if(this->IsFull())
    {
        return false;
    }
    m_storage[m_back] = value;
    m_back = (m_back + 1) % m_queueSize;
    ++m_count;        
    return true;
}

const bool MyCircularQueue::DeQueue() 
{
    if(this->IsEmpty())
    {
        return false;
    }
    m_storage[m_front] = -1;
    m_front = (m_front + 1) % m_queueSize;
    --m_count;
    return true;
}

void MyCircularQueue::RunDemo()
{
    std::cout << "Queue Size: " << m_queueSize << "\n";

    {
        constexpr int insertValue = 5;

        const bool param_1 = this->EnQueue(insertValue);

        if(param_1 == true)
        {
            std::cout << "Successfully Enqueued: " << insertValue << "\n";
        }
    }

    const bool param_2 = this->DeQueue();

    if(param_2 == true)
    {
        std::cout << "Successfully Dequeued." << "\n";
    }

    {
        const int param_3 = this->GetFront();

        std::cout << "Front Value: " << param_3 << "\n";
    }

    {
        const int param_4 = this->GetRear();

        std::cout << "Rear Value: " << param_4 << "\n";
    }

    {
        const bool param_5 = this->IsEmpty();

        std::cout << "Is Empty?: " << (bool)param_5 << "\n";
    }

    {
        const bool param_6 = this->IsFull();

        std::cout << "Is Full?: " << (bool)param_6 << "\n";
    }

    {
        constexpr int insertValue = 7;

        const bool param_1 = this->EnQueue(insertValue);
        
        if(param_1 == true)
        {
            std::cout << "Successfully Enqueued: " << insertValue << "\n";
        }
    }

    {
        constexpr int insertValue = 6;

        const bool param_1 = this->EnQueue(insertValue);
        
        if(param_1 == true)
        {
            std::cout << "Successfully Enqueued: " << insertValue << "\n";
        }
    }

    {
        const int param_3 = this->GetFront();

        std::cout << "Front Value: " << param_3 << "\n";
    }

    {
        const int param_4 = this->GetRear();

        std::cout << "Rear Value: " << param_4 << "\n";
    }

    {
        const bool param_5 = this->IsEmpty();

        std::cout << "Is Empty?: " << (bool)param_5 << "\n";
    }

    {
        const bool param_6 = this->IsFull();
        
        std::cout << "Is Full?: " << (bool)param_6 << "\n";
    }
}