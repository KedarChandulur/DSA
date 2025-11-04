#include "BFS.h"

#include <iostream>
#include <queue>

BFS::BFS()
{
    std::cout << "\nWelcome to BFS Program\n" << std::endl;
}

void BFS::Execute()
{
	if (IsAdjacencyListEmpty())
	{
		std::cout << "Adjacency list is empty." << std::endl;
		return;
	}

	std::cout << std::endl;

	std::cout << "--- Executing BFS ---" << std::endl;

	std::queue<char> q;
	q.push(this->GetSourceNode());

	while (!q.empty())
	{
		const char front = q.front();
		q.pop();

		std::vector<char>* neighbours = this->GetNeighbours(front);

		if (neighbours != nullptr)
		{
			for (const char ch : *neighbours)
			{
				q.push(ch);
			}
		}

		std::cout << "Processed: " << front << "\n";
	}

	std::cout << "--- Finished execution ---" << std::endl;
}

void BFS::RunDemo()
{
	this->Test();
	this->Execute();
}