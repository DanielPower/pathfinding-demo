#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "common.hpp"


class Tile
{
public:
	Tile();
	void setSector(float sector);
	void setIndex(uint index);
	const uint getSector() const;
	const uint getIndex() const;
	const uint getX(const uint& width) const;
	const uint getY(const uint& width) const;
private:
	uint m_index;
	uint m_sector;
};

typedef std::vector<std::shared_ptr<Tile>> tileArray;

#endif
