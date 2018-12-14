#ifndef GUI_H
#define GUI_H

#include "SFML/Graphics.hpp"
#include "common.hpp"
#include "map.h"
#include "mapLoader.h"
#include "bfs.h"
#include "astar.h"
#include "jps.h"
#include "imgui.h"
#include "imgui-SFML.h"

enum Pathfinders {
	gui_BFS,
	gui_AStar,
	gui_JPS
};

enum MouseMode {
	gui_Camera,
	gui_SelectOrigin,
	gui_SelectDestination
};

class Gui
{
private:
	std::vector<std::shared_ptr<Pathfinding>> pathfinders;
	std::shared_ptr<Pathfinding> bfs;
	std::shared_ptr<Pathfinding> astar;
	std::shared_ptr<Pathfinding> currentPathfinder;
	int selectedPathfinder;

	sf::RenderWindow window;
	sf::View view;
	float zoom;
	int prevMouseX;
	int prevMouseY;
	int deltaMouseX;
	int deltaMouseY;

	sf::Sprite map_sprite;
	sf::Image map_image;
	sf::Texture map_texture;

	sf::Sprite overlay_sprite;
	sf::Image overlay_image;
	sf::Texture overlay_texture;

	Map map;

	sf::Clock deltaClock;
	sf::Clock stepClock;
	float pathTime;
	bool continuousStep = false;
	bool showLists = false;
	bool showGrid = true;
	int mouseMode = 0;
	bool hasSelection;
	sf::Vector2i origin;
	sf::Vector2i destination;
	sf::Vector2u mousePos;

	void pathfindingStep();
	void resetPathfinder();

public:
	Gui();
	bool update();
	void render();
	sf::RenderWindow& getWindow();
};

#endif
