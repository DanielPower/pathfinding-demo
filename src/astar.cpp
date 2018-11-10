#include "astar.h"

AStar::AStar(const Map& _map): map(_map)
{
}

std::vector<Tile> AStar::vanilla(Tile start, Tile end)
{
	std::priority_queue<path_node, std::vector<path_node>, std::greater<path_node>> q;
	//heuristic = h_Euclidian;
	//auto h = (*heuristic)(start, end);
	return std::vector<Tile>();
}

/* ==============
 * = HEURISTICS =
 * ============== 
 */
float AStar::h_Manhattan4(Tile p1, Tile p2)
{
	return 0;
}

float AStar::h_Manhattan8(Tile p1, Tile p2)
{
	return 0;
}

float AStar::h_Euclidian(Tile p1, Tile p2)
{
	return 0;
}

// Node struct for open list
path_node::path_node(Tile t) : tile(t), gCost(t.getTravelCost())
{

}

