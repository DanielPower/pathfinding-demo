#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tile.h"
#include "common.hpp"

class Map
{
public:
	enum LegalActions {
		CARDINAL,
		DIAGONAL
	};

	std::vector<Tile> map;
	uint width;
	uint height;
	uint size;

	Map(uint width, uint height);
	const std::shared_ptr<Tile> get(uint x, uint y) const;
	void set(uint x, uint y, Tile tile);
	const int getIndex(uint x, uint y) const;
	const tileArray getLegalNeighbours(std::shared_ptr<Tile> t) const;
	void setLegalActions(LegalActions actions);
	const bool isOOB(uint x, uint y) const;
private:
	LegalActions currentLegalActions = DIAGONAL;
	std::vector<std::vector<int>> legalActions;
};

#endif
