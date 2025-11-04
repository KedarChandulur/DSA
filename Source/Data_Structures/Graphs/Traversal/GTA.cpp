#include "GTA.h"
#include <iostream>

GTA::GTA()
{
    std::cout << "\nWelcome to GTA Program\n" << std::endl;
}

void GTA::PrintAdjacencyList()
{
	if (adjacencyList.size() == 0)
	{
		std::cout << "Adjacency list is empty." << std::endl;
		return;
	}

	std::cout << std::endl;

	std::cout << "--- Printing adjacency list ---" << std::endl;

	for (const auto& pair : adjacencyList)
	{
		std::cout << "\nKey: " << pair.first << ",\t";

		if (pair.second.size() == 0)
		{
			std::cout << "Neighbours list is empty." << std::endl;
			continue;
		}

		std::cout << "Neighbours:\t";

		for (const char ch : pair.second)
		{
			std::cout << ch << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "--- Printing done ---" << std::endl;
}

void GTA::AddAdjacentElements(const char _pKey, std::vector<char>& _pAdjacentElementsList)
{
	std::map<char, std::vector<char>>::iterator it = adjacencyList.find(_pKey);

	if (it != adjacencyList.end())
	{
		auto& adjList = it->second;

		for (const char ch : _pAdjacentElementsList)
		{
			adjList.emplace_back(ch);
		}
	}
	else
	{
		adjacencyList.emplace(_pKey, std::move(_pAdjacentElementsList));
	}
}

void GTA::AddAdjacentElements(const char _pKey, std::vector<char>&& _pAdjacentElementsList)
{
	std::map<char, std::vector<char>>::iterator it = adjacencyList.find(_pKey);

	if (it != adjacencyList.end())
	{
		auto& adjList = it->second;

		for (const char ch : _pAdjacentElementsList)
		{
			adjList.emplace_back(ch);
		}
	}
	else
	{
		adjacencyList.emplace(_pKey, std::move(_pAdjacentElementsList));
	}
}

void GTA::Test()
{
	adjacencyList.clear();

	this->AddAdjacentElements('a', { 'b', 'd' });
	this->AddAdjacentElements('b', {});

	std::vector<char> tempList;
	this->AddAdjacentElements('c', tempList);

	std::vector<char> tempList1 = { 'e', 'g' };
	this->AddAdjacentElements('d', tempList1);

	std::vector<char> tempList2 = { 'c' };
	this->AddAdjacentElements('e', tempList2);

	this->AddAdjacentElements('f', {});

	this->AddAdjacentElements('g', {'f'});

	this->PrintAdjacencyList();
}