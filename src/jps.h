#ifndef JPS_H
#define JPS_H
#include "map.h"
#include "common.hpp"
#include "pathfinding.h"
#include "astar.h"
#include <queue>
#include <unordered_map>
#include "heuristics.hpp"


/*
 * A* Search Algorithm
 */
class JPS : public AStar
{
public:
	aStarQueue openList;
	std::unordered_map<uint, uint> closedList; //tile.index -> cost
	JPS(const Map& map)
		: AStar(map)
	{
	}
	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
	aStarQueue cardinalScan(std::shared_ptr<AStarNode> node, int dx, int dy);
	aStarQueue hScan(std::shared_ptr<AStarNode> node, int dx);
	aStarQueue diagScan(std::shared_ptr<AStarNode> node, int dx, int dy);
	std::vector<std::shared_ptr<PathNode>> getOpenNodes() override;
	void setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination) override;
	Heuristic heuristic = EUCLIDEAN;
private:
	float calcHScore(const std::shared_ptr<Tile>& t);
};

#endif
