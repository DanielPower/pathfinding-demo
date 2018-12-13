#include "map.h"
#include <iostream>


Map::Map(uint width, uint height)
	: width(width)
	, height(height)
{
	size = width * height;
	map.resize(width*height);
	setLegalActions(DIAGONAL);
}

const int Map::getIndex(uint x, uint y) const
{
	return y * width + x;
}

const tileArray Map::getLegalNeighbours(std::shared_ptr<Tile> tile) const
{
	tileArray out;
	uint x = tile->getIndex() % width;
	uint y = tile->getIndex() / width;
	for (auto dir : legalActions)
	{
		uint nx = dir[0] + x; //can't use uint because values might be negative and we need to know for OOB
		uint ny = dir[1] + y;
		if (isOOB(nx, ny)) { continue; }
		auto neighbor = get(nx, ny);
		if (neighbor->getSector() == tile->getSector())
		{
			out.push_back(neighbor);
		}
	}
	return out;
}


void Map::setLegalActions(LegalActions moves)
{
	currentLegalActions = moves;
	std::vector<std::vector<int>> card{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	std::vector<std::vector<int>> diag{ { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };
	switch (currentLegalActions)
	{
		case CARDINAL: { legalActions = card; }
		case DIAGONAL:
		{
			legalActions = card;
			legalActions.insert(legalActions.end(), diag.begin(), diag.end());
			break;
		}
		default: { break; }
	}
}

const bool Map::isOOB(uint x, uint y) const
{
	// We get to ignore the case of x<0 or y<0 because these values would
	// overflow to exceptionally large values which would be greater than
	// width and height. This saves some boolean checks.
	return (x >= width || y >= height);
}

const std::shared_ptr<Tile> Map::get(uint index) const
{
	return std::make_shared<Tile>(map[index]);
}

const std::shared_ptr<Tile> Map::get(uint x, uint y) const
{
	return std::make_shared<Tile>(map[getIndex(x, y)]);
}

void Map::set(uint x, uint y, Tile tile)
{
	map[getIndex(x, y)] = tile;
}

void Map::set(uint index, Tile tile)
{
	map[index] = tile;
}

const uint Map::getWidth() const
{
	return width;
}

const uint Map::getHeight() const
{
	return height;
}

bool Map::isDiagonal(std::shared_ptr<Tile> t1, std::shared_ptr<Tile> t2) const
{
	auto dx = fmax(t1->getX(width), t2->getX(width)) - fmin(t1->getX(width), t2->getX(width));
	auto dy = fmax(t1->getY(width), t2->getY(width)) - fmin(t1->getY(width), t2->getY(width));
	return (dx + dy) > 1;
}
