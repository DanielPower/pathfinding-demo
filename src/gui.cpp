#include "gui.h"

void Gui::init()
{
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
	Map map = image::load("map.bmp");
	view.reset(sf::FloatRect(0.f, 0.f, map.width, map.height));
	view.setViewport(sf::FloatRect(0.f, 0.f, map.width/1280.f, map.height/720.f));
	zoom = 1;

	image.create(map.width, map.height, sf::Color::Black);
	for (uint x=0; x<map.width; x++)
	{
		for (uint y=0; y<map.height; y++)
		{
			Tile tile = *map.get(x, y);
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
		deltaMouseX = 0;
		deltaMouseY = 0;

		// Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseMoved)
			{
				uint mouseX = event.mouseMove.x;
				uint mouseY = event.mouseMove.y;

				deltaMouseX = mouseX - prevMouseX;
				deltaMouseY = mouseY - prevMouseY;

				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				float delta = 0.1*-event.mouseWheelScroll.delta;
				zoom = zoom * (1+delta);
				view.zoom(1+delta);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			view.move(-deltaMouseX*zoom, -deltaMouseY*zoom);
		}

		return true;
	}
	return false;
}

void Gui::render()
{
	// Rendering
	window.setView(view);
	window.clear(sf::Color::White);
	window.draw(sprite);
	window.display();
}
