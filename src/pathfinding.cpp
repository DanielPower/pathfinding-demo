#include "pathfinding.h"

Pathfinding::Pathfinding(const Map& map)
	: map(map)
{}

Pathfinding::~Pathfinding()
{}

PathStatus Pathfinding::getStatus()
{
	return status;
}

tileArray Pathfinding::getPath()
{
	return path;
}

uint Pathfinding::getOrigin()
{
	return origin;
}

uint Pathfinding::getDestination()
{
	return destination;
}

void Pathfinding::makePath(PathNode destination)
{
	path.clear();
	auto curNode = destination;
	while (curNode.parent != nullptr)
	{
		path.push_back(curNode.tile);
		curNode = *curNode.parent;
	}
	path.push_back(curNode.tile);
}
