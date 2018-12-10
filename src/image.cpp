#include "image.h"
#include "map.h"

Map image::load(std::string filename)
{
	sf::Image image;
	image.loadFromFile(filename);
	sf::Vector2u size = image.getSize();
	Map map(size.x, size.y);

	for (uint x = 0; x < size.x; x++)
	{
		for (uint y = 0; y < size.y; y++)
		{
			sf::Color pixel = image.getPixel(x, y);
			float value = (float)(pixel.r + pixel.g + pixel.b) / 765;
			Tile tile;
			tile.setHeight(value);
			tile.setIndex(x + y * size.y);
			map.set(x, y, tile);
		}
	}

	return map;
}