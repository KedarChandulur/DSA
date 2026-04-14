#pragma once

#include <iostream>
#include <utility>

template <typename N>
struct ListNode
{
	N data;
	ListNode<N>* next;

	ListNode();
	ListNode(const N& val);
	ListNode(N&& val);
	~ListNode() = default;
};

template<typename N>
inline ListNode<N>::ListNode()
	: data{}, next(nullptr)
{
}

template<typename N>
inline ListNode<N>::ListNode(const N& val)
	: data(val), next(nullptr)
{
}

template<typename N>
inline ListNode<N>::ListNode(N&& val)
	: data(std::move(val)), next(nullptr)
{
}

template <typename T>
class SingleLinkedList
{
public:
	SingleLinkedList();
	~SingleLinkedList();

	SingleLinkedList(const SingleLinkedList& other) = delete;
	SingleLinkedList& operator=(const SingleLinkedList& other) = delete;

	SingleLinkedList(SingleLinkedList&& other) noexcept;
	SingleLinkedList& operator=(SingleLinkedList&& other) noexcept;

	void PushFront(const T& val);
	void PushFront(T&& val);

	bool PopFront(T& val);
	bool GetFrontValue(T& val) const;
	ListNode<T>* GetHead();
	const ListNode<T>* GetHead() const;

	//void PushBack(T val);
	//void PopBack();
	//T GetBackValue() const;

	void Print() const;
	void RunDemo();

private:
	enum class InputType : int
	{
		PushFront = 1,
		PopFront = 2,
		GetFront = 3,
		Print = 4,
		//PushBack = 5,
		//PopBack = 6,
		//GetBack = 7
	};

private:
	ListNode<T>* head;
	//ListNode<T>* tail;
};

template<typename T>
inline SingleLinkedList<T>::SingleLinkedList()
	: head(nullptr)//, tail(nullptr)
{
}

template<typename T>
inline SingleLinkedList<T>::~SingleLinkedList()
{
	ListNode<T>* curr = head;

	while (curr != nullptr)
	{
		ListNode<T>* deleteMe = curr;
		curr = curr->next;

		deleteMe->next = nullptr;

		delete deleteMe;
		deleteMe = nullptr;
	}
}

template<typename T>
inline SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& other) noexcept
    : head(other.head)
{
    other.head = nullptr;
}

template<typename T>
inline SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& other) noexcept
{
	if (this != &other)
	{
		// Destroy existing nodes first
		ListNode<T>* curr = head;
		while (curr != nullptr)
		{
			ListNode<T>* deleteMe = curr;
			curr = curr->next;
			delete deleteMe;
		}

		head = other.head;
		other.head = nullptr;
	}
	return *this;
}

template<typename T>
inline void SingleLinkedList<T>::PushFront(const T& val)
{
	ListNode<T>* newNode = new ListNode<T>(val);
	newNode->next = this->head;
	this->head = newNode;
}

template<typename T>
inline void SingleLinkedList<T>::PushFront(T&& val)
{
	ListNode<T>* newNode = new ListNode<T>(std::move(val));
	newNode->next = this->head;
	this->head = newNode;
}

template<typename T>
inline bool SingleLinkedList<T>::PopFront(T& val)
{
	if (!this->head)
	{
		return false;
	}

	val = this->head->data;

	ListNode<T>* deleteMe = this->head;

	this->head = this->head->next;

	deleteMe->next = nullptr;

	delete deleteMe;
	deleteMe = nullptr;

	return true;
}

template<typename T>
inline bool SingleLinkedList<T>::GetFrontValue(T& val) const
{
	if (!this->head)
	{
		return false;
	}

	val = this->head->data;

	return true;
}

template<typename T>
inline ListNode<T>* SingleLinkedList<T>::GetHead()
{
	return this->head;
}

template<typename T>
inline const ListNode<T>* SingleLinkedList<T>::GetHead() const
{
	return this->head;
}

template<typename T>
inline void SingleLinkedList<T>::Print() const
{
	ListNode<T>* curr = head;

	std::cout << "\nPrinting Single Linked List nodes...\n";

	while (curr)
	{
		std::cout << curr->data << "\n";
		curr = curr->next;
	}

	std::cout << "\n";
}

template<typename T>
inline void SingleLinkedList<T>::RunDemo()
{
	std::cout << "Enter your queries count: (Example: 10)\n";

	int querySize;

	std::cin >> querySize;

	std::cout << "\n";

	for (int query = 1; query <= querySize; ++query)
	{
		std::cout << "Enter your query no: " << query << "\n\n";

		std::cout << "Use number: 1 For Push Front\n";
		std::cout << "            2 for Pop Front\n";
		std::cout << "            3 Get Front\n";
		std::cout << "            4 Print\n\n";
		//std::cout << "            5 For Push Back\n";
		//std::cout << "            6 for Pop Back\n";
		//std::cout << "            7 Get Back\n\n";

		int type;
		std::cin >> type;
		std::cout << "\n";

		const InputType inputType = static_cast<InputType>(type);

		// For the demo im using only primitive data types
		// Custom class will also work
		T value{};

		switch (inputType)
		{
		case InputType::PushFront:
			std::cout << "What do you wanna push: ";
			std::cin >> value;
			this->PushFront(value);
			std::cout << "Successfully Pushed: " << value;
			break;

		case InputType::PopFront:
			if (this->PopFront(value))
			{
				std::cout << "Successfully Poped";
			}
			break;

		case InputType::GetFront:
			if (this->GetFrontValue(value))
			{
				std::cout << "Alright printing the Front element of the queue: " << value;
			}
			break;

		case InputType::Print:
			std::cout << "Alright printing the Linked list: ";
			this->Print();
			break;

		//case InputType::PushBack:
		//	break;

		//case InputType::PopBack:
		//	break;

		//case InputType::GetBack:
		//	break;

		default:
			std::cout << "Invalid query, enter your query again...";
			--query;
			break;
		}

		std::cout << "\n\n";
	}
}

