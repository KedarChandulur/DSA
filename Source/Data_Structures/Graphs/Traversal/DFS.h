#pragma once

#include "GTA.h"

class DFS : public GTA
{
public:
	DFS();
	virtual ~DFS() = default;

    DFS(const DFS& other) = delete;
    DFS& operator=(const DFS& other) = delete;

    DFS(DFS&& other) = delete;
    DFS& operator=(DFS&& other) = delete;

	void Execute() override final;

	void RunDemo();
};

typedef DFS DepthFirstSearch;