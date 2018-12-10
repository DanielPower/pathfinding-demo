#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "map.h"
#include "image.h"
#include "bfs.h"
#include "astar.h"

enum Pathfinders {
	gui_BFS,
	gui_AStar
};

class Gui
{
private:
	std::vector<std::shared_ptr<Pathfinding>> pathfinders;
	std::shared_ptr<Pathfinding> bfs;
	std::shared_ptr<Pathfinding> astar;
	std::shared_ptr<Pathfinding> currentPathfinder;

	sf::RenderWindow window;
	sf::View view;

	sf::Sprite map_sprite;
	sf::Image map_image;
	sf::Texture map_texture;

	sf::Sprite open_sprite;
	sf::Image open_image;
	sf::Texture open_texture;

	sf::Sprite closed_sprite;
	sf::Image closed_image;
	sf::Texture closed_texture;

	Map map;

	float zoom;
	int prevMouseX;
	int prevMouseY;
	int deltaMouseX;
	int deltaMouseY;

public:
	Gui();
	bool update();
	void render();
	void pathfindingStep();
};

#endif
