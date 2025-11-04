#pragma once

#include <vector>
#include <map>

/*
* GTA - Graph Traversal Algorithms
* Using for -> DFS, BFS
*/
class GTA
{
public:
	GTA();
	virtual ~GTA() = default;

	GTA(const GTA& other) = delete;
    GTA& operator=(const GTA& other) = delete;

    GTA(GTA&& other) = delete;
    GTA& operator=(GTA&& other) = delete;

	void PrintAdjacencyList();

	virtual void Execute() = 0;

	void AddAdjacentElements(const char _pKey, std::vector<char>& _pAdjacentElementsList);
	void AddAdjacentElements(const char _pKey, std::vector<char>&& _pAdjacentElementsList);

	inline void ClearAdjacencyList()
	{
		adjacencyList.clear();
	}

	inline const bool IsAdjacencyListEmpty() const
	{
		return adjacencyList.empty();
	}

	inline const char GetSourceNode() const
	{
		return adjacencyList.begin()->first;
	}

	inline std::vector<char>* GetNeighbours(const char _pKey)
	{
		std::map<char, std::vector<char>>::iterator it = adjacencyList.find(_pKey);

		if (it == adjacencyList.end())
		{
			return nullptr;
		}

		return &it->second;
	}

protected:
	void Test();

private:
	std::map<char, std::vector<char>> adjacencyList;
};

typedef GTA GraphTraversalAlgorithm;