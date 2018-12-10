#include "pathfinding.h"

void Pathfinding::setGoal(Tile& _origin, Tile& _destination)
{
	origin = _origin.getIndex();
	destination = _destination.getIndex();
}

void Pathfinding::makePath(PathNode destination)
{
	//todo make path by following destination node backwards
}
