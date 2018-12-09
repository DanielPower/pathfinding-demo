#ifndef PATHFINDING
#define PATHFINDING

#include "common.h"
#include "map.h"

class Pathfinding
{
public:
	const Map& map;
	std::vector<Tile> path;

	explicit Pathfinding(const Map& map)
		: map(map)
	{
	}
	virtual std::vector<Tile> getPath() = 0;
	virtual void step() = 0;
	virtual std::vector<Tile> getOpenList() = 0;
	virtual std::vector<Tile> getClosedList() = 0;
};

struct PathNode
{
	Tile tile;
	uint gCost;
	uint getCost() const { return gCost; }
	PathNode(Tile t): tile(t)
	{
	}
	friend bool operator< (const PathNode& lhs, const PathNode& rhs) { return lhs.getCost() < rhs.getCost(); };
	friend bool operator> (const PathNode& lhs, const PathNode& rhs) { return rhs < lhs; }
	friend bool operator<=(const PathNode& lhs, const PathNode& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const PathNode& lhs, const PathNode& rhs) { return !(lhs < rhs); }
};


#endif

