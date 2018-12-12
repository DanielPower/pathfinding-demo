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
	std::shared_ptr<PathNode> parent = nullptr;
	PathNode(std::shared_ptr<Tile> t) : tile(t)
	{
	}
	friend bool operator < (const PathNode& lhs, const PathNode& rhs) { return lhs.getCost() < rhs.getCost(); };
	friend bool operator > (const PathNode& lhs, const PathNode& rhs) { return rhs < lhs; }
	friend bool operator <= (const PathNode& lhs, const PathNode& rhs) { return !(lhs > rhs); }
	friend bool operator >= (const PathNode& lhs, const PathNode& rhs) { return !(lhs < rhs); }
};

class Pathfinding
{
public:
	explicit Pathfinding(const Map& map);
	virtual ~Pathfinding();

	virtual void setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination) = 0;
	virtual void step() = 0;
	virtual tileArray getOpenList() = 0;
	virtual tileArray getClosedList() = 0;
	PathStatus getStatus();
	tileArray getPath();
	uint getOrigin();
	uint getDestination();

protected:
	const Map& map;
	PathStatus status = IN_PROGRESS;
	tileArray path;
	uint origin;
	uint destination;

	void makePath(PathNode destination);
};

#endif
