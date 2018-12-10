#include "gui.h"

Gui::Gui()
{
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
	Map map = Image::load("map.bmp");

	astar = std::make_shared<AStar>(map);
	bfs = std::make_shared<BFS>(map);
	pathfinders = {bfs, astar};

	view.reset(sf::FloatRect(0.f, 0.f, map.width, map.height));
	view.setViewport(sf::FloatRect(0.f, 0.f, map.width/1280.f, map.height/720.f));
	zoom = 1;

	map_image.create(map.width, map.height, sf::Color::Black);
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	for (uint x=0; x<map.width; x++)
	{
		for (uint y=0; y<map.height; y++)
		{
			Tile tile = *map.get(x, y);
			if (tile.getHeight() < 0.3)
			{
				map_image.setPixel(x, y, sf::Color(0, 0, 128));
			}
			else if (tile.getHeight() > 0.7)
			{
				map_image.setPixel(x, y, sf::Color(128, 128, 128));
			}
			else
			{
				map_image.setPixel(x, y, sf::Color(0, 128, 0));
			}
		}
	}
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);

	open_texture.loadFromImage(open_image);
	open_sprite.setTexture(open_texture);

	closed_texture.loadFromImage(closed_image);
	closed_sprite.setTexture(closed_texture);
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
			else if (event.type == sf::Event::MouseMoved)
			{
				uint mouseX = event.mouseMove.x;
				uint mouseY = event.mouseMove.y;

				deltaMouseX = mouseX - prevMouseX;
				deltaMouseY = mouseY - prevMouseY;

				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				float delta = 0.1*-event.mouseWheelScroll.delta;
				zoom = zoom * (1+delta);
				view.zoom(1+delta);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case(sf::Keyboard::Space): { break; }
					default: { break; }
				}
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
	window.draw(map_sprite);
	window.draw(open_sprite);
	window.draw(closed_sprite);
	window.display();
}

void Gui::pathfindingStep()
{
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));

	for (auto tile : pathfinders[gui_BFS]->getOpenList())
	{
		open_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(255, 0, 0));
	}

	for (auto tile : pathfinders[gui_BFS]->getClosedList())
	{
		closed_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(0, 255, 255));
	}
}
