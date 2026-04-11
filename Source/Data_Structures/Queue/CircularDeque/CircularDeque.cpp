#include <iostream>

#include "CircularDeque.h"

MyCircularDeque::MyCircularDeque(int k) 
    : m_count(0), m_front(0), m_back(0), m_queueSize(k)
{
    m_storage.resize(m_queueSize);
    for(int i = 0; i < m_queueSize; ++i)
    {
        m_storage[i] = -1;
    }
}

bool MyCircularDeque::InsertFront(int value) 
{
    if(this->IsFull())
    {
        return false;
    }
    m_front = (m_front - 1 + m_queueSize) % m_queueSize;
    m_storage[m_front] = value;
    ++m_count;
    return true;
}

bool MyCircularDeque::InsertLast(int value) 
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

bool MyCircularDeque::DeleteFront() 
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

bool MyCircularDeque::DeleteLast() 
{
    if(this->IsEmpty())
    {
        return false;
    }
    const int lastIndex = (m_back - 1 + m_queueSize) % m_queueSize;
    m_storage[lastIndex] = -1;
    
    m_back = lastIndex;
    --m_count;
    return true;
}

void MyCircularDeque::RunDemo()
{
    std::cout << "Queue Size: " << m_queueSize << "\n";

    {
        constexpr int insertValue = 6;

        const bool param_1 = this->InsertFront(insertValue);

        if(param_1 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the front" << "\n";
        }
    }

    {
        constexpr int insertValue = 7;

        const bool param_2 = this->InsertLast(insertValue);

        if(param_2 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the last" << "\n";
        }
    }

    const bool param_3 = this->DeleteFront();

    if(param_3 == true)
    {
        std::cout << "Successfully deleted element from front." << "\n";
    }

    const bool param_4 = this->DeleteLast();

    if(param_4 == true)
    {
        std::cout << "Successfully deleted element from last." << "\n";
    }

    {
        const int param_5 = this->GetFront();

        std::cout << "Front Value: " << param_5 << "\n";
    }

    {
        const int param_6 = this->GetRear();

        std::cout << "Rear Value: " << param_6 << "\n";
    }

    {
        const bool param_7 = this->IsEmpty();

        std::cout << "Is Empty?: " << (bool)param_7 << "\n";
    }

    {
        const bool param_8 = this->IsFull();

        std::cout << "Is Full?: " << (bool)param_8 << "\n";
    }

    {
        constexpr int insertValue = 6;

        const bool param_1 = this->InsertFront(insertValue);

        if(param_1 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the front" << "\n";
        }
    }

    {
        constexpr int insertValue = 7;

        const bool param_2 = this->InsertLast(insertValue);

        if(param_2 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the last" << "\n";
        }
    }

    {
        constexpr int insertValue = 9;

        const bool param_1 = this->InsertFront(insertValue);

        if(param_1 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the front" << "\n";
        }
    }

    {
        constexpr int insertValue = 4;

        const bool param_2 = this->InsertLast(insertValue);

        if(param_2 == true)
        {
            std::cout << "Successfully inserted " << insertValue << " to the last" << "\n";
        }
    }

    {
        const int param_5 = this->GetFront();

        std::cout << "Front Value: " << param_5 << "\n";
    }

    {
        const int param_6 = this->GetRear();

        std::cout << "Rear Value: " << param_6 << "\n";
    }

    {
        const bool param_7 = this->IsEmpty();

        std::cout << "Is Empty?: " << (bool)param_7 << "\n";
    }

    {
        const bool param_8 = this->IsFull();

        std::cout << "Is Full?: " << (bool)param_8 << "\n";
    }
}