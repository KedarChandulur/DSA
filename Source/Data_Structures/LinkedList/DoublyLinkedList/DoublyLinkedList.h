#pragma once

#include <iostream>

template <typename ND>
struct DListNode
{
	ND data;
	DListNode<ND>* next;
	DListNode<ND>* prev;

	DListNode();
	DListNode(const ND& val);
	DListNode(ND&& val);

	DListNode& operator=(const ND& other);
	DListNode& operator=(ND&& other);

	~DListNode() = default;
};

template<typename ND>
inline DListNode<ND>::DListNode()
	: data{}, next(nullptr), prev(nullptr)
{
}

template<typename ND>
inline DListNode<ND>::DListNode(const ND& val)
	: data(val), next(nullptr), prev(nullptr)
{
}

template<typename ND>
inline DListNode<ND>::DListNode(ND&& val)
	: data(std::move(val)), next(nullptr), prev(nullptr)
{
}

template<typename ND>
inline DListNode<ND>& DListNode<ND>::operator=(const ND& other)
{ 
	data = other;
	return *this;
}

template<typename ND>
inline DListNode<ND>& DListNode<ND>::operator=(ND&& other)
{ 
	data = std::move(other);
	return *this;
}

template <typename TD>
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();

	DoublyLinkedList(const DoublyLinkedList& other) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList& other) = delete;

	DoublyLinkedList(DoublyLinkedList&& other) noexcept;
	DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

	void PushFront(const TD& val);
	void PushFront(TD&& val);
	void PushBack(const TD& val);
	void PushBack(TD&& val);

	bool PopFront(TD& outVal);
	bool PopBack(TD& outVal);

	template<typename Predicate>
	bool RemoveIf(Predicate pred);

	bool GetHeadValue(TD& outVal) const;
	bool GetTailValue(TD& outVal) const;

	const DListNode<TD>* GetHead() const;
	const DListNode<TD>* GetTail() const;

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
	DListNode<TD>* head;
	DListNode<TD>* tail;
};

template<typename TD>
inline DoublyLinkedList<TD>::DoublyLinkedList()
	: head(nullptr), tail(nullptr)
{
}

template<typename TD>
inline DoublyLinkedList<TD>::~DoublyLinkedList()
{
	DListNode<TD>* curr = head;

	while (curr != nullptr)
	{
		DListNode<TD>* deleteMe = curr;
		curr = curr->next;

		deleteMe->next = nullptr;
		deleteMe->prev = nullptr;

		delete deleteMe;
		deleteMe = nullptr;
	}
}

template<typename TD>
inline DoublyLinkedList<TD>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
	: head(other.head), tail(other.tail)
{
	other.head = nullptr;
	other.tail = nullptr;
}

template<typename TD>
inline DoublyLinkedList<TD>& DoublyLinkedList<TD>::operator=(DoublyLinkedList&& other) noexcept
{
	if (this != &other)
	{
		// Destroy existing nodes first
		DListNode<TD>* curr = head;
		while (curr != nullptr)
		{
			DListNode<TD>* deleteMe = curr;
			curr = curr->next;
			delete deleteMe;
		}

		head = other.head;
		other.head = nullptr;

		tail = other.tail;
		other.tail = nullptr;
	}

	return *this;
}

template<typename TD>
inline void DoublyLinkedList<TD>::PushFront(const TD& val)
{
	DListNode<TD>* newNode = new DListNode<TD>(val);
	newNode->next = this->head;

	if (this->head)
	{
		this->head->prev = newNode;
	}
	else
	{
		this->tail = newNode;
	}
	
	this->head = newNode;
}

template<typename TD>
inline void DoublyLinkedList<TD>::PushFront(TD&& val)
{
	DListNode<TD>* newNode = new DListNode<TD>(std::move(val));
	newNode->next = this->head;

	if (this->head)
	{
		this->head->prev = newNode;
	}
	else
	{
		this->tail = newNode;
	}

	this->head = newNode;
}

template<typename TD>
inline void DoublyLinkedList<TD>::PushBack(const TD& val)
{
	DListNode<TD>* newNode = new DListNode<TD>(val);
	newNode->prev = this->tail;

	if (this->tail)
	{
		this->tail->next = newNode;
	}
	else
	{
		this->head = newNode;
	}

	this->tail = newNode;
}

template<typename TD>
inline void DoublyLinkedList<TD>::PushBack(TD&& val)
{
	DListNode<TD>* newNode = new DListNode<TD>(std::move(val));
	newNode->prev = this->tail;

	if (this->tail)
	{
		this->tail->next = newNode;
	}
	else
	{
		this->head = newNode;
	}

	this->tail = newNode;
}

template<typename TD>
inline bool DoublyLinkedList<TD>::PopFront(TD& outVal)
{
	if (!this->head)
	{
		return false;
	}

	if (this->head == this->tail)
	{
		this->tail = nullptr;
	}

	outVal = this->head->data;

	DListNode<TD>* deleteMe = this->head;

	this->head = this->head->next;

	if (this->head)
	{
		this->head->prev = nullptr;
	}

	deleteMe->next = nullptr;

	delete deleteMe;
	deleteMe = nullptr;

	return true;
}

template<typename TD>
inline bool DoublyLinkedList<TD>::PopBack(TD& outVal)
{
	if (!this->tail)
	{
		return false;
	}

	if (this->tail == this->head)
	{
		this->head = nullptr;
	}

	outVal = this->tail->data;

	DListNode<TD>* deleteMe = this->tail;

	this->tail = this->tail->prev;

	if (this->tail)
	{
		this->tail->next = nullptr;
	}

	deleteMe->prev = nullptr;

	delete deleteMe;
	deleteMe = nullptr;

	return true;
}

template<typename TD>
template<typename Predicate>
inline  bool DoublyLinkedList<TD>::RemoveIf(Predicate pred)
{
	DListNode<TD>* curr = head;

	while (curr != nullptr)
	{
		if (pred(curr->data))
		{
			if (curr->prev)
			{
				curr->prev->next = curr->next;
			}
			else
			{
				this->head = curr->next;
			}

			if (curr->next)
			{
				curr->next->prev = curr->prev;
			}
			else
			{
				this->tail = curr->prev;
			}

			curr->next = nullptr;
			curr->prev = nullptr;

			delete curr;
			curr = nullptr;

			return true;
		}

		curr = curr->next;
	}

	return false;
}

template<typename TD>
inline bool DoublyLinkedList<TD>::GetHeadValue(TD& outVal) const
{
	bool result = false;

	if (this->head)
	{
		outVal = this->head->data;
		result = true;
	}

	return result;
}

template<typename TD>
inline bool DoublyLinkedList<TD>::GetTailValue(TD& outVal) const
{
	bool result = false;

	if (this->tail)
	{
		outVal = this->tail->data;
		result = true;
	}

	return result;
}

template<typename TD>
inline const DListNode<TD>* DoublyLinkedList<TD>::GetHead() const
{
	return this->head;
}

template<typename TD>
inline const DListNode<TD>* DoublyLinkedList<TD>::GetTail() const
{
	return this->tail;
}


template<typename TD>
inline bool DoublyLinkedList<TD>::IsEmpty() const
{
	return this->head ? false : true;
}

template<typename TD>
inline void DoublyLinkedList<TD>::PrintFromHead() const
{
	DListNode<TD>* curr = head;

	while (curr)
	{
		std::cout << curr->data << "\n";
		curr = curr->next;
	}

	std::cout << "\n";
}

template<typename TD>
inline void DoublyLinkedList<TD>::PrintFromTail() const
{
	DListNode<TD>* curr = tail;

	while (curr)
	{
		std::cout << curr->data << "\n";
		curr = curr->prev;
	}

	std::cout << "\n";
}

template<typename TD>
inline void DoublyLinkedList<TD>::RunDemo()
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
		TD value{};

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