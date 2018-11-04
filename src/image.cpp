#include "image.h"
#include "map.h"

Map Image::load(std::string filename) {
	sf::Image image;
	image.loadFromFile(filename);
	sf::Vector2u size = image.getSize();
	Map map(size.x, size.y);

	for (uint x = 0; x < size.x; x++) {
		for (uint y = 0; y < size.y; y++) {
			sf::Color pixel = image.getPixel(x, y);
			float value = (pixel.r + pixel.g + pixel.b) / 3;
			Tile tile(value);
			map.map[x][y] = tile;
		}
	}

	return map;
}