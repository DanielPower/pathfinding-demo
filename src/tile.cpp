#include "tile.h"

Tile::Tile() {};

void Tile::setSector(float sector) {
	m_sector = sector;
}

void Tile::setIndex(uint index)
{
	m_index = index;
}

const uint Tile::getSector() const
{
	return m_sector;
}

const uint Tile::getIndex() const
{
	return m_index;
}

const uint Tile::getX(const uint& width) const
{
	return m_index%width;
}

const uint Tile::getY(const uint& width) const
{
	return m_index/width;
}
