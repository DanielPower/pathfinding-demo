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
			std::cout << tile.getHeight();
			if (tile.getHeight() < 0.3)
			{
				image.setPixel(x, y, sf::Color(0, 0, 128));
			} 
			else if (tile.getHeight() > 0.7)
			{
				image.setPixel(x, y, sf::Color(128, 128, 128));
			} 
			else
			{
				image.setPixel(x, y, sf::Color(0, 128, 0));
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