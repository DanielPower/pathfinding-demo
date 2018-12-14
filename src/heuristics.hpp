#ifndef HEURISTICS
#define HEURISTICS
#include "common.hpp"
#include "map.h"

enum Heuristic
{
	MANHATTAN,
	EUCLIDEAN,
};

inline float manhattanCardinal(const Map& m, const std::shared_ptr<Tile>& t, const std::shared_ptr<Tile>& destination)
{
	const float x1 = t->getX(m.getWidth());
	const float y1 = t->getY(m.getWidth());
	const float x2 = destination->getX(m.getWidth());
	const float y2 = destination->getY(m.getWidth());
	return fabs(x1-x2) + fabs(y1-y2);
}

inline float euclidean(const Map& m, const std::shared_ptr<Tile>& t, const std::shared_ptr<Tile>& destination)
{
	const float x1 = t->getX(m.getWidth());
	const float y1 = t->getY(m.getWidth());
	const float x2 = destination->getX(m.getWidth());
	const float y2 = destination->getY(m.getWidth());
	const float x = x1 - x2;
	const float y = y1 - y2;
	const float dist = sqrt(pow(x, 2) + pow(y, 2));
	return dist;
}

#endif
