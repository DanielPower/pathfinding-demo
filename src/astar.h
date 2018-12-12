#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.hpp"
#include <vector>
#include "pathfinding.h"
#include <queue>
#include <unordered_map>
#include "heuristics.hpp"


//Pathnodes for A* make use of two values for their cost fxn
struct AStarNode : PathNode
{
	uint gCost = 0;
	uint hCost = 0;
	explicit AStarNode(const std::shared_ptr<Tile>& t)
		: PathNode(t)
	{
	}
	uint getCost() const override { return gCost + hCost; }
};

//Function used by our priority queue to compare nodes
struct CompareNode : public std::binary_function<std::shared_ptr<AStarNode>, std::shared_ptr<AStarNode>, bool>
{
	bool operator()(const std::shared_ptr<AStarNode> lhs, const std::shared_ptr<AStarNode> rhs) const
	{
		return (lhs->hCost + lhs->gCost) > (rhs->hCost + rhs->gCost);
	}
};

//This is implemented because the default priority doesn't allow iterative access to the underlying vector
//And we want access to the vector for visualization purposes
class aStarQueue : public std::priority_queue<std::shared_ptr<AStarNode>, std::vector<std::shared_ptr<AStarNode>>, CompareNode> {
public:
	std::vector<std::shared_ptr<AStarNode>>& get_vec() { return c; }
};

/*
 * A* Search Algorithm
 */
class AStar : public Pathfinding
{
public:
	aStarQueue openList;
	std::unordered_map<uint, uint> closedList; //tile.index -> cost
	AStar(const Map& map)
		: Pathfinding(map)
	{
	}
	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
	std::vector<std::shared_ptr<PathNode>> getOpenNodes() override;
	void setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination) override;
	Heuristic heuristic = EUCLIDEAN;
private:
	uint calcHScore(const std::shared_ptr<Tile>& t);

};



#endif
