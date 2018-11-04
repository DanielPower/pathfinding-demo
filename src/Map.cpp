#include "Map.h"

Tile Map::get(int x, int y)
{
	return map[x][y];
}

sf::Sprite Map::getSprite()
{
	sf::Image img;
	sf::Texture txt;
	sf::Sprite sprite;
	img.create(width, height);
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			auto tile = get(x, y);
			img.setPixel(x, y, tile.getColor());
		}
	}
	txt.loadFromImage(img);
	sprite.setTexture(txt);
	return sprite;
}
