#pragma once

#include <memory>
#include <iostream>

template <typename NDSP>
struct DListNode_SP
{
	NDSP data;
	std::unique_ptr<DListNode_SP<NDSP>> next;
	DListNode_SP<NDSP>* prev;

	DListNode_SP();
	DListNode_SP(const NDSP& val);
	DListNode_SP(NDSP&& val);

	DListNode_SP& operator=(const NDSP& other);
	DListNode_SP& operator=(NDSP&& other);

	~DListNode_SP() = default;
};

template<typename NDSP>
inline DListNode_SP<NDSP>::DListNode_SP()
	: data{}, next(nullptr), prev(nullptr)
{
}

template<typename NDSP>
inline DListNode_SP<NDSP>::DListNode_SP(const NDSP& val)
	: data(val), next(nullptr), prev(nullptr)
{
}

template<typename NDSP>
inline DListNode_SP<NDSP>::DListNode_SP(NDSP&& val)
	: data(std::move(val)), next(nullptr), prev(nullptr)
{
}

template<typename NDSP>
inline DListNode_SP<NDSP>& DListNode_SP<NDSP>::operator=(const NDSP& other)
{ 
	data = other;
	return *this;
}

template<typename NDSP>
inline DListNode_SP<NDSP>& DListNode_SP<NDSP>::operator=(NDSP&& other)
{ 
	data = std::move(other);
	return *this;
}

template <typename TDSP>
class DoublyLinkedList_SP
{
public:
	DoublyLinkedList_SP();
	~DoublyLinkedList_SP();

	DoublyLinkedList_SP(const DoublyLinkedList_SP& other) = delete;
	DoublyLinkedList_SP& operator=(const DoublyLinkedList_SP& other) = delete;

	DoublyLinkedList_SP(DoublyLinkedList_SP&& other) noexcept;
	DoublyLinkedList_SP& operator=(DoublyLinkedList_SP&& other) noexcept;

	void PushFront(const TDSP& val);
	void PushFront(TDSP&& val);
	void PushBack(const TDSP& val);
	void PushBack(TDSP&& val);

	bool PopFront(TDSP& outVal);
	bool PopBack(TDSP& outVal);

	template<typename Predicate>
	bool RemoveIf(Predicate pred);

	bool GetHeadValue(TDSP& outVal) const;
	bool GetTailValue(TDSP& outVal) const;

	const DListNode_SP<TDSP>* GetHead() const;
	const DListNode_SP<TDSP>* GetTail() const;

	bool IsEmpty() const;
	void PrintFromHead() const;
	void PrintFromTail() const;
	void RunDemo();

private:
	enum class InputType : int
	{
		PushFront = 1,
		PushBack = 2,
		PopFront = 3,
		PopBack = 4,
		GetHead = 5,
		GetTail = 6,
		PrintFromHead = 7,
		PrintFromTail = 8
	};

private:
	std::unique_ptr<DListNode_SP<TDSP>> head;
	DListNode_SP<TDSP>* tail;
};

template<typename TDSP>
inline DoublyLinkedList_SP<TDSP>::DoublyLinkedList_SP()
	: head(nullptr), tail(nullptr)
{
}

template<typename TDSP>
inline DoublyLinkedList_SP<TDSP>::~DoublyLinkedList_SP()
{
	while (this->head != nullptr)
	{
		/* 
		*  Iterative destructor as the smart pointer will trigger
		*  chain of destructors and it will cause stack overflow at one point.
		*  By doing the regular iterative destructor you are using std::move which
		*  destroys the current object and takes control of the coming obj - in the
		*  below case curr is the curr and curr->next is the coming.
		*/
		this->head = std::move(this->head->next);
	}
}

template<typename TDSP>
inline DoublyLinkedList_SP<TDSP>::DoublyLinkedList_SP(DoublyLinkedList_SP&& other) noexcept
	: head(std::move(other.head)), tail(other.tail)
{
	other.head = nullptr;
	other.tail = nullptr;
}

template<typename TDSP>
inline DoublyLinkedList_SP<TDSP>& DoublyLinkedList_SP<TDSP>::operator=(DoublyLinkedList_SP&& other) noexcept
{
	if (this != &other)
	{
		// Destroy existing nodes first
		while (this->head != nullptr)
		{
			/*
			*  Iterative destructor as the smart pointer will trigger
			*  chain of destructors and it will cause stack overflow at one point.
			*  By doing the regular iterative destructor you are using std::move which
			*  destroys the current object and takes control of the coming obj - in the
			*  below case curr is the curr and curr->next is the coming.
			*/
			this->head = std::move(this->head->next);
		}

		head = std::move(other.head);
		other.head = nullptr;

		tail = other.tail;
		other.tail = nullptr;
	}

	return *this;
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PushFront(const TDSP& val)
{
	std::unique_ptr<DListNode_SP<TDSP>> newNode = std::make_unique<DListNode_SP<TDSP>>(val);

	if (this->head)
	{
		this->head->prev = newNode.get();
	}
	else
	{
		this->tail = newNode.get();
	}
	
	newNode->next = std::move(this->head);

	this->head = std::move(newNode);
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PushFront(TDSP&& val)
{
	std::unique_ptr<DListNode_SP<TDSP>> newNode = std::make_unique<DListNode_SP<TDSP>>(std::move(val));

	if (this->head)
	{
		this->head->prev = newNode.get();
	}
	else
	{
		this->tail = newNode.get();
	}

	newNode->next = std::move(this->head);

	this->head = std::move(newNode);
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PushBack(const TDSP& val)
{
	std::unique_ptr<DListNode_SP<TDSP>> newNode = std::make_unique<DListNode_SP<TDSP>>(val);
	newNode->prev = this->tail;

	if (this->tail)
	{
		this->tail->next = std::move(newNode);

		this->tail = this->tail->next.get();
	}
	else
	{
		this->head = std::move(newNode);

		this->tail = this->head.get();
	}
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PushBack(TDSP&& val)
{
	std::unique_ptr<DListNode_SP<TDSP>> newNode = std::make_unique<DListNode_SP<TDSP>>(std::move(val));
	newNode->prev = this->tail;

	if (this->tail)
	{
		this->tail->next = std::move(newNode);

		this->tail = this->tail->next.get();
	}
	else
	{
		this->head = std::move(newNode);

		this->tail = this->head.get();
	}
}

template<typename TDSP>
inline bool DoublyLinkedList_SP<TDSP>::PopFront(TDSP& outVal)
{
	if (!this->head)
	{
		return false;
	}

	if (this->head.get() == this->tail)
	{
		this->tail = nullptr;
	}

	outVal = this->head->data;

	this->head = std::move(this->head->next);
	
	if (head)
	{
		this->head->prev = nullptr;
	}

	return true;
}

template<typename TDSP>
inline bool DoublyLinkedList_SP<TDSP>::PopBack(TDSP& outVal)
{
	if (!this->tail)
	{
		return false;
	}

	outVal = this->tail->data;

	if (this->tail == this->head.get())
	{
		this->tail = nullptr;
		this->head = std::move(this->head->next);
	}
	else
	{
		DListNode_SP<TDSP>* tailPrev = this->tail->prev;
		tailPrev->next.reset();
		this->tail = tailPrev;
	}

	return true;
}

template<typename TDSP>
template<typename Predicate>
inline  bool DoublyLinkedList_SP<TDSP>::RemoveIf(Predicate pred)
{
	DListNode_SP<TDSP>* curr = head.get();

	bool result = false;

	while (curr != nullptr)
	{
		DListNode_SP<TDSP>* currNextCache = curr->next.get();

		if (pred(curr->data))
		{
			if (curr->next)
			{
				curr->next->prev = curr->prev;
			}
			else
			{
				this->tail = curr->prev;
			}

			if (curr->prev)
			{
				curr->prev->next = std::move(curr->next);
			}
			else
			{
				this->head = std::move(curr->next);
			}

			result = true;
		}

		curr = currNextCache;
	}

	return result;
}

template<typename TDSP>
inline bool DoublyLinkedList_SP<TDSP>::GetHeadValue(TDSP& outVal) const
{
	bool result = false;

	if (this->head)
	{
		outVal = this->head->data;
		result = true;
	}

	return result;
}

template<typename TDSP>
inline bool DoublyLinkedList_SP<TDSP>::GetTailValue(TDSP& outVal) const
{
	bool result = false;

	if (this->tail)
	{
		outVal = this->tail->data;
		result = true;
	}

	return result;
}

template<typename TDSP>
inline const DListNode_SP<TDSP>* DoublyLinkedList_SP<TDSP>::GetHead() const
{
	return this->head.get();
}

template<typename TDSP>
inline const DListNode_SP<TDSP>* DoublyLinkedList_SP<TDSP>::GetTail() const
{
	return this->tail;
}

template<typename TDSP>
inline bool DoublyLinkedList_SP<TDSP>::IsEmpty() const
{
	return this->head == nullptr;
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PrintFromHead() const
{
	DListNode_SP<TDSP>* curr = head.get();

	while (curr)
	{
		std::cout << curr->data << "\n";
		curr = curr->next.get();
	}

	std::cout << "\n";
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::PrintFromTail() const
{
	DListNode_SP<TDSP>* curr = tail;

	while (curr)
	{
		std::cout << curr->data << "\n";
		curr = curr->prev;
	}

	std::cout << "\n";
}

template<typename TDSP>
inline void DoublyLinkedList_SP<TDSP>::RunDemo()
{
	std::cout << "Enter your queries count: (Example: 10)\n";

	int querySize;

	std::cin >> querySize;

	std::cout << "\n";

	for (int query = 1; query <= querySize; ++query)
	{
		std::cout << "Enter your query no: " << query << "\n\n";

		std::cout << "Use number: 1 For Push Front\n";
		std::cout << "            2 For Push Back\n";
		std::cout << "            3 For Pop Front\n";
		std::cout << "            4 For Pop Back\n";
		std::cout << "            5 Get Head Value\n";
		std::cout << "            6 Get Tail Value\n";
		std::cout << "            7 Print From Head\n";
		std::cout << "            8 Print From Tail\n\n";

		int type;
		std::cin >> type;
		std::cout << "\n";

		const InputType inputType = static_cast<InputType>(type);

		// For the demo im using only primitive data types
		// Custom class will also work
		TDSP value{};

		switch (inputType)
		{
		case InputType::PushFront:
			std::cout << "What do you wanna push to front: ";
			std::cin >> value;
			this->PushFront(value);
			std::cout << "Successfully Pushed to Front: " << value;
			break;

		case InputType::PushBack:
			std::cout << "What do you wanna push to back: ";
			std::cin >> value;
			this->PushBack(value);
			std::cout << "Successfully Pushed to Back: " << value;
			break;

		case InputType::PopFront:
			if (this->PopFront(value))
			{
				std::cout << "Successfully Popped from Front: " << value;
			}
			else
			{
				std::cout << "List is empty, nothing to pop.";
			}
			break;

		case InputType::PopBack:
			if (this->PopBack(value))
			{
				std::cout << "Successfully Popped from Back: " << value;
			}
			else
			{
				std::cout << "List is empty, nothing to pop.";
			}
			break;

		case InputType::GetHead:
			if (this->GetHeadValue(value))
			{
				std::cout << "Head value: " << value;
			}
			else
			{
				std::cout << "List is empty.";
			}
			break;

		case InputType::GetTail:
			if (this->GetTailValue(value))
			{
				std::cout << "Tail value: " << value;
			}
			else
			{
				std::cout << "List is empty.";
			}
			break;

		case InputType::PrintFromHead:
			std::cout << "Printing from Head:\n";
			this->PrintFromHead();
			break;

		case InputType::PrintFromTail:
			std::cout << "Printing from Tail:\n";
			this->PrintFromTail();
			break;

		default:
			std::cout << "Invalid query, enter your query again...";
			--query;
			break;
		}

		std::cout << "\n\n";
	}
}