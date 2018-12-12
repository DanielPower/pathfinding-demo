#ifndef HEURISTICS
#define HEURISTICS
#include "common.hpp"
#include "map.h"

enum Heuristic
{
	EUCLIDEAN,
};

inline uint euclidean(const Map& m, const std::shared_ptr<Tile> t, const Tile& destination)
{
	float x1 = t->getX(m.width);
	float y1 = t->getY(m.width);
	float x2 = destination.getX(m.width);
	float y2 = destination.getY(m.width);
	float x = x1 - x2;
	float y = y1 - y2;
	float dist = sqrt(pow(x, 2) + pow(y, 2));
	return uint(dist);
}

#endif
