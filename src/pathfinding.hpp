#ifndef PATHFINDING
#define PATHFINDING

#include "common.h"
#include "map.h"

enum PathStatus
{
	IN_PROGRESS,
	FINISHED,
	FAILED,
};

struct PathNode
{
	Tile& tile;
	uint gCost;
	uint getCost() const { return gCost; }
	Tile* parent = nullptr;
	PathNode(Tile t) : tile(t)
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
	std::vector<Tile&> path;
	uint origin;
	uint destination;
	PathStatus status = IN_PROGRESS;

	explicit Pathfinding(const Map& map)
		: map(map)
	{
	}

	void setGoal(Tile& _origin, Tile& _destination)
	{
		origin = _origin.getIndex();
		destination = _destination.getIndex();
	}
	virtual void step() = 0;
	virtual std::vector<Tile&> getPath() = 0;
	virtual std::vector<Tile&> getOpenList() = 0;
	virtual std::vector<Tile&> getClosedList() = 0;

private:
	// once you have reached the destination, we iterate back over the pathnodes and add their Tiles
	void setPath(PathNode destination)
	{
		//todo 
	}

};



#endif

