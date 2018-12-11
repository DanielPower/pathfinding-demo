#include "gui.h"

Gui::Gui()
	: map(Image::load("map.bmp"))
{
	// Create window
	window.create(sf::VideoMode(1280, 720), "COMP 3200");

	// Setup vector of pathfinders
	pathfinders = {
		std::make_shared<BFS>(map),
		std::make_shared<AStar>(map)
	};

	// Initialize currentPathfinder as instance of BFS
	currentPathfinder = pathfinders[gui_BFS];

	// DEBUG - set start/end until implemented in gui
	auto start = map.get(5, 5);
	auto end = map.get(9, 9);
	currentPathfinder->setGoal(start, end);
	currentPathfinder->step();

	// Create blank images
	map_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	path_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));

	// Fill map_image with data from map
	for (uint x = 0; x < map.width; x++)
	{
		for (uint y = 0; y < map.height; y++)
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

	// Create blank path sprite
	path_texture.loadFromImage(path_image);
	path_sprite.setTexture(path_texture);

	// Set initial view
	view.reset(sf::FloatRect(0.f, 0.f, map.width, map.height));
	view.setViewport(sf::FloatRect(0.f, 0.f, map.width / 1280.f, map.height / 720.f));
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
			ImGui::SFML::ProcessEvent(event);
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
				zoom = zoom * (1 + delta);
				view.zoom(1 + delta);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case(sf::Keyboard::Space): { pathfindingStep(); break; }
				case(sf::Keyboard::Escape): { window.close(); break; }
				default: { break; }
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			view.move(-deltaMouseX * zoom, -deltaMouseY * zoom);
		}

		// Update ImGui
		ImGui::SFML::Update(window, deltaClock.restart());

		// Setup ImGui Window
		ImGui::Begin("Hello World!");
		ImGui::Button("Look at this button");
		ImGui::End();

		return true;
	}
	return false;
}

void Gui::render()
{
	// Rendering
	window.setView(view);
	window.clear(sf::Color::White);

	// Draw map and highlight open/closed nodes
	window.draw(map_sprite);
	window.draw(open_sprite);
	window.draw(closed_sprite);
	window.draw(path_sprite);

	// Draw grid lines
	if (zoom < 0.2f)
	{
		sf::Vector2f size = view.getSize();
		sf::Vector2f position = view.getCenter();
		float left = position.x - size.x / 2.f;
		float top = position.y - size.y / 2.f;

		// Vertical lines
		for (uint x = 0; x <= floor(size.x / zoom); x++)
		{
			sf::Vertex x_line[] =
			{
				sf::Vertex(sf::Vector2f((int)left + (int)x - 1, top)),
				sf::Vertex(sf::Vector2f((int)left + (int)x - 1, top + size.y))
			};

			window.draw(x_line, 2, sf::Lines);
		}

		// Horizontal lines
		for (uint y = 0; y <= floor(size.y / zoom); y++)
		{
			sf::Vertex y_line[] =
			{
				sf::Vertex(sf::Vector2f(left, (int)top + (int)y - 1)),
				sf::Vertex(sf::Vector2f(left + size.x, (int)top + (int)y - 1))
			};

			window.draw(y_line, 2, sf::Lines);
		}
	}

	ImGui::SFML::Render(window);

	window.display();
}


void Gui::pathfindingStep()
{
	// because pathfinding steps often do nothing (ie returning early because the expanded node was in the closed list)
	// we only draw once we have something new to draw
	auto closedSize = currentPathfinder->getClosedList().size();
	auto newClosedSize = closedSize;
	while (currentPathfinder->status !=FINISHED && closedSize == newClosedSize)
	{
		currentPathfinder->step();
		newClosedSize = currentPathfinder->getClosedList().size();
	}

	// Clear open and closed images
	open_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));
	closed_image.create(map.width, map.height, sf::Color(0, 0, 0, 0));

	// Add yellow pixel to open_image for each open tile
	for (auto tile : currentPathfinder->getOpenList())
	{
		open_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(255, 0, 0));
	}

	// Add green pixel to closed_image for each closed tile
	for (auto tile : currentPathfinder->getClosedList())
	{
		closed_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(255, 255, 0));
	}

	//Add purple pixels to path if the pathfinding is finished
	//if (currentPathfinder->status == FINISHED)
	{
		for (auto tile : currentPathfinder->getPath())
		{
			closed_image.setPixel(tile->getX(map.width), tile->getY(map.width), sf::Color(255, 0, 255));
		}
	}

	open_texture.loadFromImage(open_image);
	open_sprite.setTexture(open_texture);

	closed_texture.loadFromImage(closed_image);
	closed_sprite.setTexture(closed_texture);

	path_texture.loadFromImage(path_image);
	path_sprite.setTexture(path_texture);

}

sf::RenderWindow& Gui::getWindow()
{
	return window;
}
