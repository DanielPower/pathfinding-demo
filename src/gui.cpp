#include "gui.h"

void Gui::init()
{
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
	Map map = image::load("map.bmp");

	image.create(map.width, map.height, sf::Color::Black);
	for (uint x=0; x<map.width; x++)
	{
		for (uint y=0; y<map.height; y++)
		{
			Tile tile = map.get(x, y);
			if (tile.getSector() == 0)
			{
				image.setPixel(x, y, sf::Color(tile.getHeight()*255, tile.getHeight()*255, tile.getHeight()*255));
			} 
			else if (tile.getSector() == 1)
			{
				image.setPixel(x, y, sf::Color(tile.getHeight()*255, tile.getHeight()*255, tile.getHeight()*255));
			} 
			else
			{
				image.setPixel(x, y, sf::Color(tile.getHeight()*255, tile.getHeight()*255, tile.getHeight()*255));
			}
		}
	}
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

bool Gui::update()
{
	if (window.isOpen())
	{
		// Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		return true;
	}
	
	return false;
}

void Gui::render()
{
	// Rendering
	window.clear(sf::Color::White);
	window.draw(sprite);
	window.display();
}