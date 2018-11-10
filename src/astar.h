#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.h"
#include <vector>
#include <queue>

std::vector<Tile> astar_vanilla(Map map, Tile start, Tile end);

struct path_node
{
	Tile tile;
	uint gCost;
	uint hCost =0 ;
	path_node(Tile t);
};

#endif