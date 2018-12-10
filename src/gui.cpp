#include "gui.h"

Gui::Gui()
{
	// Create window
	window.create(sf::VideoMode(1280, 720), "COMP 3200");

	// Create map from file
	Map map = Image::load("map.bmp");

	// Setup vector of pathfinders
	pathfinders = {
		std::make_shared<BFS>(map),
		std::make_shared<AStar>(map)
	};

	// Initialize currentPathfinder as instance of BFS
	currentPathfinder = pathfinders[gui_BFS];

	// DEBUG - set start/end until implemented in gui
	auto start = map.get(5, 5);
	auto end = map.get(25, 25);
	currentPathfinder->setGoal(start, end);
	currentPathfinder->step();

	// Create blank images
	map_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));

	// Fill map_image with data from map
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

	// Create map sprite
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);

	// Create blank open sprite
	open_texture.loadFromImage(open_image);
	open_sprite.setTexture(open_texture);

	// Create blank closed sprite
	closed_texture.loadFromImage(closed_image);
	closed_sprite.setTexture(closed_texture);

	// Set initial view
	view.reset(sf::FloatRect(0.f, 0.f, map.width, map.height));
	view.setViewport(sf::FloatRect(0.f, 0.f, map.width/1280.f, map.height/720.f));
	zoom = 1;
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
					case(sf::Keyboard::Space): { pathfindingStep(); break; }
					case(sf::Keyboard::Escape): { window.close(); break; }
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
	// FIXME - Crashes here, even though currentPathfinder->step() works fine if run in Gui::Gui()
	currentPathfinder->step();

	// Clear open and closed images
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));

	std::cout << currentPathfinder->getOpenList().size() << std::endl;

	// Add yellow pixel to open_image for each open tile
	for (auto tile : currentPathfinder->getOpenList())
	{
		std::cout << "tile " << tile->getX(map.width) << " " << tile->getY(map.width) << std::endl;
		open_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(255, 0, 0));
	}

	// Add green pixel to closed_image for each closed tile
	for (auto tile : currentPathfinder->getClosedList())
	{
		closed_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(0, 255, 255));
	}
}
