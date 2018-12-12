#include "gui.h"

Gui::Gui()
: map(MapLoader::fromText("default.txt"))
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
	auto start = map.get(62, 3);
	auto end = map.get(60, 47);
	currentPathfinder->setGoal(start, end);

	// Create blank images
	map_image.create(map.getWidth(), map.getHeight(), sf::Color(0, 0, 0, 0));
	overlay_image.create(map.getWidth(), map.getHeight(), sf::Color(0, 0, 0, 0));

	// Fill map_image with data from map
	for (uint x = 0; x < map.getWidth(); x++)
	{
		for (uint y = 0; y < map.getHeight(); y++)
		{
			Tile tile = *map.get(x, y);
			if (tile.getSector() == 2)
			{
				map_image.setPixel(x, y, sf::Color(0, 66, 255));
			}
			else if (tile.getSector() == 1)
			{
				map_image.setPixel(x, y, sf::Color(0, 255, 0));
			}
			else if (tile.getSector() == 0)
			{
				map_image.setPixel(x, y, sf::Color(88, 88, 88));
			}
		}
	}

	// Create map sprite
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);

	// Create blank open sprite
	overlay_texture.loadFromImage(overlay_image);
	overlay_sprite.setTexture(overlay_texture);

	// Set initial view
	view.reset(sf::FloatRect(0.f, 0.f, 1280, 720));
	view.zoom(0.1);
	view.setCenter(map.getWidth()/2, map.getHeight()/2);
	zoom = 0.1;

	// Reset path time
	pathTime = 0;
}

bool Gui::update()
{
	if (window.isOpen())
	{
		deltaMouseX = 0;
		deltaMouseY = 0;

		mousePos = (sf::Vector2u)window.mapPixelToCoords(sf::Mouse::getPosition(window));

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
				case(sf::Keyboard::Escape): { window.close(); break; }
				default: { break; }
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mousePos.x <= map.getWidth() && mousePos.y <= map.getHeight())
					{
						if (mouseMode == gui_SelectOrigin)
						{
							selectedTile = mousePos;
							hasSelection = true;
							mouseMode = gui_SelectDestination;
						}
						else if (mouseMode == gui_SelectDestination)
						{
							currentPathfinder->setGoal(map.get(selectedTile.x, selectedTile.y), map.get(mousePos.x, mousePos.y));
							pathTime = 0;
							mouseMode = gui_Camera;
							hasSelection = false;
						}
					}
				}
			}
		}

		if (!ImGui::GetIO().WantCaptureMouse && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			view.move(-deltaMouseX * zoom, -deltaMouseY * zoom);
		}

		if (continuousStep)
		{
			pathfindingStep();
		}

		return true;
	}
	return false;
}

void Gui::render()
{
	// Clear open and closed images
	overlay_image.create(map.getWidth(), map.getHeight(), sf::Color(0, 0, 0, 0));

	// Add yellow pixel to overlay_image for each open tile
	for (auto tile : currentPathfinder->getOpenList())
	{
		overlay_image.setPixel(tile->getX(map.getWidth()), tile->getY(map.getWidth()), sf::Color(255, 255, 0));
	}

	// Add red pixel to closed_image for each closed tile
	for (auto tile : currentPathfinder->getClosedList())
	{
		overlay_image.setPixel(tile->getX(map.getWidth()), tile->getY(map.getWidth()), sf::Color(255, 0, 0));
	}

	// Add purple pixels to path if the pathfinding is finished
	if (currentPathfinder->getStatus() == FINISHED)
	{
		for (auto tile : currentPathfinder->getPath())
		{
			overlay_image.setPixel(tile->getX(map.getWidth()), tile->getY(map.getWidth()), sf::Color(255, 0, 255));
		}
	}

	// Draw selected tile as white
	if (hasSelection)
	{
		overlay_image.setPixel(selectedTile.x, selectedTile.y, sf::Color::White);
	}

	// Draw hovered tile as white
	if (mousePos.x < map.getWidth() && mousePos.y < map.getHeight())
	{
		overlay_image.setPixel(mousePos.x, mousePos.y, sf::Color::White);
	}

	overlay_texture.loadFromImage(overlay_image);
	overlay_sprite.setTexture(overlay_texture);

	// Update ImGui
	ImGui::SFML::Update(window, deltaClock.restart());

	// Setup ImGui Window
	ImGui::Begin("Hello World!");

	// Display amount of time running current path
	ImGui::Text("Path Time: %f ms", pathTime/1000);

	// Checkbox to continuously run pathfinding
	ImGui::Checkbox("Run", &continuousStep);

	// Button to run a single step of pathfinding
	ImGui::SameLine();
	if (ImGui::Button("Step"))
	{
		pathfindingStep();
	}

	// Button to restart current path
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		resetPathfinder();
	}

	// Button to set new path
	ImGui::SameLine();
	if (ImGui::Button("Set Path"))
	{
		mouseMode = gui_SelectOrigin;
	}

	// Checkbox to enable/disable the grid
	ImGui::Checkbox("Show Grid", &showGrid);

	// Container for open/closed lists
	ImGui::Checkbox("Show Open/Closed Lists", &showLists);

	if (showLists)
	{
		ImGui::BeginChild("List View");
		ImGui::Columns(2, NULL, false);
		ImGui::Text("Open Nodes");
		for (auto tile : currentPathfinder->getOpenList())
		{
			ImGui::Text("x=%d, y=%d", tile->getX(map.getWidth()), tile->getY(map.getWidth()));
		}
		ImGui::NextColumn();
		ImGui::Text("Closed Nodes");
		for (auto tile : currentPathfinder->getClosedList())
		{
			ImGui::Text("x=%d, y=%d", tile->getX(map.getWidth()), tile->getY(map.getWidth()));
		}
		ImGui::EndChild();
	}
	ImGui::End();

	// Rendering
	window.setView(view);
	window.clear(sf::Color::White);

	// Draw map and highlight open/closed nodes
	window.draw(map_sprite);
	window.draw(overlay_sprite);

	// Draw grid lines
	if (showGrid)
	{
		// Vertical lines
		for (uint x = 0; x <= map.getWidth(); x++)
		{
			sf::Vertex x_line[] =
			{
				sf::Vertex(sf::Vector2f(x, 0), sf::Color::Black),
				sf::Vertex(sf::Vector2f(x, map.getHeight()), sf::Color::Black)
			};

			window.draw(x_line, 2, sf::Lines);
		}

		// Horizontal lines
		for (uint y = 0; y <= map.getHeight(); y++)
		{
			sf::Vertex y_line[] =
			{
				sf::Vertex(sf::Vector2f(0, y), sf::Color::Black),
				sf::Vertex(sf::Vector2f(map.getWidth(), y), sf::Color::Black)
			};

			window.draw(y_line, 2, sf::Lines);
		}
	}

	ImGui::SFML::Render(window);

	window.display();
}


void Gui::pathfindingStep()
{
	if (currentPathfinder->getStatus() == IN_PROGRESS)
	{
		stepClock.restart();
		currentPathfinder->step();
		pathTime += stepClock.getElapsedTime().asMicroseconds();
	}
}

void Gui::resetPathfinder()
{
	pathTime = 0;
	uint origin = currentPathfinder->getOrigin();
	uint destination = currentPathfinder->getDestination();

	currentPathfinder->setGoal(map.get(origin), map.get(destination));
}

sf::RenderWindow& Gui::getWindow()
{
	return window;
}
