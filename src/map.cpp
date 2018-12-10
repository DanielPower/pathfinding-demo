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

int Map::getIndex(uint x, uint y)
{
	return y * width + x;
}

tileArray Map::getLegalNeighbours(Tile t)
{
	tileArray out;
	uint x = t.getIndex() % width;
	uint y = t.getIndex() / width;
	for (auto dir : legalActions)
	{
		int nx = dir[0] + x; //can't use uint because values might be negative and we need to know for OOB
		int ny = dir[1] + y;
		if (isOOB(nx, ny)) continue;
		//todo: check for tile 'type' sameness
		auto tile = std::make_shared<Tile>(get(nx, ny));
		out.push_back(tile);
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
	case CARDINAL:
		legalActions = card;
	case DIAGONAL:
		legalActions = card;
		legalActions.insert(legalActions.end(), diag.begin(), diag.end());
		break;
	default:;
	}
}

bool Map::isOOB(int x, int y)
{
	return (x < 0 || y < 0 || x >= width || y >= height);
}

Tile Map::get(uint x, uint y)
{
	return map[getIndex(x, y)];
}

void Map::set(uint x, uint y, Tile tile)
{
	map[getIndex(x, y)] = tile;
}