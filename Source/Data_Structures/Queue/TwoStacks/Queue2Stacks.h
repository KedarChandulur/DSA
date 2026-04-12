#include <stack>
#include <iostream>

template <typename T>
class Queue2Stacks
{
public:
    Queue2Stacks();
    ~Queue2Stacks() = default;

    Queue2Stacks(const Queue2Stacks& other) = delete;
    Queue2Stacks& operator=(const Queue2Stacks& other) = delete;

    Queue2Stacks(Queue2Stacks&& other) = delete;
    Queue2Stacks& operator=(Queue2Stacks&& other) = delete;

    void Enqueue(T data);
    void Dequeue();
    T Front();
    void Print();
    void RunDemo();
        
private:
    void RefillOutBuffer();

private:
    enum class InputType : int
    {
        Enqueue = 1,
        Dequeue = 2,
        Print = 3
    };
    
private:
    std::stack<T> input;
    std::stack<T> output;
};

template <typename T>
inline Queue2Stacks<T>::Queue2Stacks()
{
    std::cout << "\nWelcome to Queue two stacks Program\n" << std::endl;
}

template <typename T>
inline void Queue2Stacks<T>::Enqueue(T data)
{
    input.push(data);
}

template <typename T>
inline void Queue2Stacks<T>::Dequeue()
{               
    if(output.empty())
    {           
        RefillOutBuffer();
    }
    
    if(output.empty())
    {
        return;
    }

    output.pop();
}

template <typename T>
inline T Queue2Stacks<T>::Front()
{
    if(output.empty())
    {
        RefillOutBuffer();
    }
    
    return output.top();
}

template <typename T>
inline void Queue2Stacks<T>::Print()
{
    if(output.empty())
    {
        RefillOutBuffer();
    }
    
    if(output.empty())
    {
        return;
    }
    
    std::cout << output.top() << "\n";
}

template <typename T>
inline void Queue2Stacks<T>::RefillOutBuffer()
{
    if(input.empty())
    {
        return;
    }
            
    while(!input.empty())
    {
        output.push(input.top());
        input.pop();
    }
}

template <typename T>
inline void Queue2Stacks<T>::RunDemo()
{
    std::cout << "Enter your queries count: (Example: 10)\n";

    int querySize;
    
    std::cin >> querySize;

    std::cout << "\n";
        
    for(int query = 1; query <= querySize; ++query)
    {
        std::cout << "Enter your query no: " << query << "\n\n";

        std::cout << "Use number: 1 For Enqueue\n";
        std::cout << "            2 for Dequeue\n";
        std::cout << "            3 for printing the front element\n\n";

        int type;
        std::cin >> type;
        std::cout << "\n";
        
        const InputType inputType = static_cast<InputType>(type);
        
        switch(inputType)
        {
            case InputType::Enqueue:
                std::cout << "What do you wanna enqueue: ";
                int value;
                std::cin >> value;
                this->Enqueue(value);
                std::cout << "Successfully Enqueued: " << value;
                break;

            case InputType::Dequeue:
                this->Dequeue();
                std::cout << "Dequeue complete.";
                break;
            case InputType::Print:
                std::cout << "Alright printing the Front element of the queue: ";
                this->Print();
                break;
            default:
                std::cout << "Invalid query, enter your query again...";
                --query;
                break;
        }

        std::cout << "\n\n";
    }
}