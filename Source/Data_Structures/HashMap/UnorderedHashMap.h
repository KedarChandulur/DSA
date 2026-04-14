#pragma once

#include <type_traits>  // std::is_arithmetic
#include <cstring>      // std::memcpy
#include <functional>   // std::function
#include <vector>
#include <iostream>

#include "SingleLinkedList.h"

template<typename D>
struct DefaultHasher
{
	static_assert(
		std::is_arithmetic<D>::value ||
		std::is_invocable_r<size_t, std::hash<D>, const D&>::value,
		"[DefaultHasher] Key type must be arithmetic or have a std::hash specialization. "
		"For fully custom types without std::hash, use RuntimeHasher<T> and provide your own hash function."
		);

	size_t operator()(const D& key) const
	{
		if constexpr (std::is_arithmetic<D>::value)
		{
			// Bit-mixing hash using MurmurHash3 finalizer constants.
			// Copies the raw bytes of the primitive into a size_t,
			// then applies three rounds of xor-shift + multiply to
			// achieve strong avalanche (each output bit depends on every input bit).
			// Constants 0xff51afd7ed558ccd and 0xc4ceb9fe1a85ec53 are the
			// MurmurHash3 64-bit finalizer mix constants.

			size_t hash = 0;
			static_assert(sizeof(D) <= sizeof(size_t), "Type too large for default hash");
			std::memcpy(&hash, &key, sizeof(D));

			// MurmurHash3 finalizer bit mix
			hash ^= hash >> 33;
			hash *= 0xff51afd7ed558ccdULL;
			hash ^= hash >> 33;
			hash *= 0xc4ceb9fe1a85ec53ULL;
			hash ^= hash >> 33;

			return hash;
		}
		else
		{
			// Tier 2: delegate to std::hash<D> (std::string, etc.)
			return std::hash<D>{}(key);
		}
	}
};

/*  Example use case:

	// Something as Key, int as Value
	auto smtHasher = [](const Something& s) -> size_t
	{
		size_t h = 0;
		std::memcpy(&h, &s.id, sizeof(s.id));
		h ^= h >> 33;
		h *= 0xff51afd7ed558ccdULL;
		return h;
	};

	struct Something
	{
	    int id;
	    float x, y;
	
	    bool operator==(const Something& other) const
	    {
	        return id == other.id && x == other.x && y == other.y;
	    }
	};

	inline void RunSomethingDemo()
	{
		UnorderedHashMap<Something, int, RunTimeHandler<Something>>
		    smtStringMap(RunTimeHandler<Something>(smtHasher));

		smtStringMap.InsertorUpdate({1, 0.5f, 1.0f}, 100);
		smtStringMap.InsertorUpdate({2, 1.5f, 2.0f}, 200);
		smtStringMap.Print();

		int val = 0;
		if (smtStringMap.Find({1, 0.5f, 1.0f}, val))
		    std::cout << "\nFound: " << val;

		// int as Key, Something as Value
		UnorderedHashMap<int, Something> intSomethingMap;  // DefaultHasher<int>

		intSomethingMap.InsertorUpdate(1, {10, 1.0f, 2.0f});
		intSomethingMap.InsertorUpdate(2, {20, 3.0f, 4.0f});
		intSomethingMap.Print();

		Something found{};
		if (intSomethingMap.Find(1, found))
		    std::cout << "\nFound: " << found;
	}
*/
template<typename R>
struct RunTimeHandler
{
	RunTimeHandler(std::function<size_t(const R&)> func)
		: hashFunc(func)
	{
	}

	size_t operator()(const R& key) const
	{
		return hashFunc(key);
	}

private:
	std::function<size_t(const R&)> hashFunc;
};


template<typename Key, typename Value, typename Hasher = DefaultHasher<Key>>
class UnorderedHashMap
{
private:
	struct MapData
	{
		Key key;
		Value value;

		MapData() = default;

		MapData(const Key& k, const Value& v)
			: key(k), value(v) {
		}

		MapData(Key&& k, Value&& v)
			: key(std::move(k)), value(std::move(v)) {
		}

		MapData(const MapData&) = default;
		MapData& operator=(const MapData&) = default;

		MapData(MapData&&) = default;
		MapData& operator=(MapData&&) = default;
	};

public:
	UnorderedHashMap();
	UnorderedHashMap(Hasher customHasher);
	~UnorderedHashMap() = default;

	void InsertorUpdate(const Key& key, const Value& value);
	bool Find(const Key& key, Value& value) const;
	bool Remove(const Key& key);
	const size_t GetHashIndex(const Key& key) const;

	void Rehash();
	size_t GetElementCount() const;

	void Print() const;
	void RunDemo();

private:
	enum class InputType : int
	{
		InsertOrUpdate = 1,
		Find = 2,
		Remove = 3,
		Print = 4,
	};

private:
	std::vector<SingleLinkedList<MapData>> dataMap;
	Hasher hasher;
	size_t elementCount;

	static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
};

template<typename Key, typename Value, typename Hasher>
inline UnorderedHashMap<Key, Value, Hasher>::UnorderedHashMap()
	: dataMap(), elementCount(0)
{
	dataMap.resize(DEFAULT_BUCKET_COUNT);
}

template<typename Key, typename Value, typename Hasher>
inline UnorderedHashMap<Key, Value, Hasher>::UnorderedHashMap(Hasher customHasher)
	: dataMap(), elementCount(0), hasher(std::move(customHasher))
{
	dataMap.resize(DEFAULT_BUCKET_COUNT);
}

template<typename Key, typename Value, typename Hasher>
inline void UnorderedHashMap<Key, Value, Hasher>::InsertorUpdate(const Key& key, const Value& value)
{
	const size_t hashedIndex = GetHashIndex(key);

	ListNode<MapData>* current = dataMap[hashedIndex].GetHead();

	while (current != nullptr)
	{
		if (current->data.key == key)
		{
			current->data.value = value;
			break;
		}

		current = current->next;
	}

	if (current == nullptr)
	{
		dataMap[hashedIndex].PushFront({ key, value });
		++elementCount;

		const float loadFactor = static_cast<float>(elementCount) / dataMap.size();
		
		if (loadFactor > 0.75f)
		{
			Rehash();
		}
	}
}

template<typename Key, typename Value, typename Hasher>
inline bool UnorderedHashMap<Key, Value, Hasher>::Find(const Key& key, Value& value) const
{
	bool result = false;

	const size_t hashedIndex = GetHashIndex(key);

	ListNode<MapData>* current = dataMap[hashedIndex].GetHead();

	while (current != nullptr)
	{
		if (current->data.key == key)
		{
			value = current->data.value;
			result = true;
			break;
		}

		current = current->next;
	}

	return result;
}

template<typename Key, typename Value, typename Hasher>
inline bool UnorderedHashMap<Key, Value, Hasher>::Remove(const Key& key)
{
	const size_t hashedIndex = GetHashIndex(key);

	const bool removed = dataMap[hashedIndex].RemoveIf(
		[&key](const MapData& data)
		{
			return data.key == key;
		}
	);

	if (removed)
		--elementCount;

	return removed;
}

template<typename Key, typename Value, typename Hasher>
inline const size_t UnorderedHashMap<Key, Value, Hasher>::GetHashIndex(const Key& key) const
{
	return hasher(key) % dataMap.size();
}

template<typename Key, typename Value, typename Hasher>
inline void UnorderedHashMap<Key, Value, Hasher>::Rehash()
{
	std::vector<SingleLinkedList<MapData>> newMap;
	newMap.resize(dataMap.size() * 2);

	for (SingleLinkedList<MapData>& list : dataMap)
	{
		ListNode<MapData>* curr = list.GetHead();
		while (curr)
		{
			size_t newIndex = hasher(curr->data.key) % newMap.size();
			newMap[newIndex].PushFront(std::move(curr->data));
			curr = curr->next;
		}
	}

	dataMap = std::move(newMap);
}

template<typename Key, typename Value, typename Hasher>
inline size_t UnorderedHashMap<Key, Value, Hasher>::GetElementCount() const
{
	return elementCount;
}

template<typename Key, typename Value, typename Hasher>
inline void UnorderedHashMap<Key, Value, Hasher>::Print() const
{
	for (const SingleLinkedList<MapData>& mapData : dataMap)
	{
		const ListNode<MapData>* curr = mapData.GetHead();

		while (curr)
		{
			std::cout << "\nkey: " << curr->data.key << " | value: " << curr->data.value;
			curr = curr->next;
		}
	}
}

template<typename Key, typename Value, typename Hasher>
inline void UnorderedHashMap<Key, Value, Hasher>::RunDemo()
{
	std::cout << "Enter your queries count: (Example: 10)\n";

	int querySize;
	std::cin >> querySize;
	std::cout << "\n";

	for (int query = 1; query <= querySize; ++query)
	{
		std::cout << "Enter your query no: " << query << "\n\n";

		std::cout << "Use number: 1 For InsertOrUpdate\n";
		std::cout << "            2 For Find\n";
		std::cout << "            3 For Remove\n";
		std::cout << "            4 For Print\n\n";

		int type;
		std::cin >> type;
		std::cout << "\n";

		const InputType inputType = static_cast<InputType>(type);

		Key key{};
		Value value{};

		switch (inputType)
		{
		case InputType::InsertOrUpdate:
			std::cout << "Enter key: ";
			std::cin >> key;
			std::cout << "Enter value: ";
			std::cin >> value;
			this->InsertorUpdate(key, value);
			std::cout << "Successfully Inserted/Updated key: " << key;
			break;

		case InputType::Find:
			std::cout << "Enter key to find: ";
			std::cin >> key;
			if (this->Find(key, value))
				std::cout << "Found! Value: " << value;
			else
				std::cout << "Key not found.";
			break;

		case InputType::Remove:
			std::cout << "Enter key to remove: ";
			std::cin >> key;
			if (this->Remove(key))
				std::cout << "Successfully Removed key: " << key;
			else
				std::cout << "Key not found.";
			break;

		case InputType::Print:
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