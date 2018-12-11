#include "pathfinding.h"

Pathfinding::Pathfinding(const Map& map)
	: map(map)
{}

Pathfinding::~Pathfinding()
{}

tileArray Pathfinding::getPath()
{
	return path;
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
