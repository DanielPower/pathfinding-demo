#ifndef PATHFINDING
#define PATHFINDING

#include "common.hpp"
#include "map.h"

enum PathStatus
{
	IN_PROGRESS,
	FINISHED,
	FAILED,
};

struct PathNode
{
	std::shared_ptr<Tile> tile;
	uint gCost;
	uint getCost() const { return gCost; }
	Tile* parent = nullptr;
	PathNode(std::shared_ptr<Tile> t) : tile(t)
	{
	}
	friend bool operator< (const PathNode& lhs, const PathNode& rhs) { return lhs.getCost() < rhs.getCost(); };
	friend bool operator> (const PathNode& lhs, const PathNode& rhs) { return rhs < lhs; }
	friend bool operator<=(const PathNode& lhs, const PathNode& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const PathNode& lhs, const PathNode& rhs) { return !(lhs < rhs); }
};

class Pathfinding
{
public:
	const Map& map;
	uint origin;
	uint destination;
	PathStatus status = IN_PROGRESS;

	explicit Pathfinding(const Map& map)
		: map(map)
	{
	}
	void setGoal(Tile& _origin, Tile& _destination);
	virtual void step() = 0;
	virtual tileArray getOpenList() = 0;
	virtual tileArray getClosedList() = 0;

protected:
	void makePath(PathNode destination);
	tileArray path;
};

#endif

