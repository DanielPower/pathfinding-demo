#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tile.h"
#include "common.h"

class Map
{
public:
	enum LegalActions{CARDINAL, DIAGONAL};
	std::vector<Tile> map;
	uint width;
	uint height;
	uint size;

	Map(uint width, uint height);
	Tile get(uint x, uint y);
	void set(uint x, uint y, Tile tile);
	int getIndex(uint x, uint y);
	tileArray Map::getLegalNeighbours(Tile t);
	void setLegalActions(LegalActions actions);
	bool isOOB(int x, int y);
private:
	LegalActions currentLegalActions = DIAGONAL;
	std::vector<std::vector<int>> legalActions;
};

#endif
