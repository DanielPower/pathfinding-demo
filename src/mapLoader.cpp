#include <fstream>
#include "mapLoader.h"
#include "map.h"

Map MapLoader::fromImage(std::string filename)
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
			// HACK - some better way of determining sectors should be used in the future
			if (value > 0.7f)
			{
				tile.setSector(2);
			}
			else if (value < 0.3f)
			{
				tile.setSector(0);
			}
			else
			{
				tile.setSector(1);
			}
			tile.setIndex(x + y * size.y);
			map.set(x, y, tile);
		}
	}

	return map;
}

// WARNING - Assumes characters are in a perfect rectangle. Undefined behavior
// will occur if all lines do not have the same length
Map MapLoader::fromText(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "File not found" << std::endl;
		exit(-1);
	}
	// Read dimensions of map from first line
	int width;
	int height;
	file >> width >> height;

	Map map(width, height);
	uint index = 0;
	char c;
	while (file >> c)
	{
		Tile tile;
		tile.setIndex(index);
		tile.setSector((uint)(c - '0'));
		map.set(index, tile);
		index++;
	}

	return map;
}
