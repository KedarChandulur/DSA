#pragma once

#include "GTA.h"

class BFS : public GTA
{
public:
	BFS();
	virtual ~BFS() = default;

    BFS(const BFS& other) = delete;
    BFS& operator=(const BFS& other) = delete;

    BFS(BFS&& other) = delete;
    BFS& operator=(BFS&& other) = delete;

	void Execute() override final;

	void RunDemo();
};

typedef BFS BreadthFirstSearch;