#include "astar.h"

std::vector<Tile> astar_vanilla(Map map, Tile start, Tile end)
{
	std::priority_queue<path_node> q;
	return std::vector<Tile>();
}

path_node::path_node(Tile t): tile(t), gCost(t.getTravelCost())
{
}

