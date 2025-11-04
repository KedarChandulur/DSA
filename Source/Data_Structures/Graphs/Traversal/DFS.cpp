#include "DFS.h"

#include <iostream>
#include <stack>

DFS::DFS()
{
    std::cout << "\nWelcome to DFS Program\n" << std::endl;
}

void DFS::Execute()
{
	if (IsAdjacencyListEmpty())
	{
		std::cout << "Adjacency list is empty." << std::endl;
		return;
	}
	
	std::cout << std::endl;

	std::cout << "--- Executing DFS ---" << std::endl;

	std::stack<char> st;
	st.push(this->GetSourceNode());

	while (!st.empty())
	{
		const char top = st.top();
		st.pop();

		std::vector<char>* neighbours = this->GetNeighbours(top);

		if (neighbours != nullptr)
		{
			for (const char ch : *neighbours)
			{
				st.push(ch);
			}
		}

		std::cout << "Processed: " << top << "\n";
	}

	std::cout << "--- Finished execution ---" << std::endl;
}

void DFS::RunDemo()
{
	this->Test();
	this->Execute();
}