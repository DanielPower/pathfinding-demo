#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.h"
#include <vector>
#include <queue>
class AStar
{
public:
	Map map;
	AStar(const Map& _map);
	std::vector<Tile> vanilla(Tile start, Tile end);

private:
	//heuristics
	//float (AStar::*heuristic)(Tile p1, Tile p2) = h_Euclidian;
	float h_Manhattan4(Tile p1, Tile p2);
	float h_Manhattan8(Tile p1, Tile p2);
	float h_Euclidian(Tile p1, Tile p2);
};

struct path_node 
{
	Tile tile;
	uint gCost;
	uint hCost = 0;
	path_node(Tile t);
	friend bool operator< (const path_node& lhs, const path_node& rhs) { return lhs.gCost + lhs.hCost < rhs.gCost + rhs.hCost; };
	friend bool operator> (const path_node& lhs, const path_node& rhs) { return rhs < lhs; }
	friend bool operator<=(const path_node& lhs, const path_node& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const path_node& lhs, const path_node& rhs) { return !(lhs < rhs); }
};



#endif