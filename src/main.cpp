#include "common.hpp"
#include "gui.h"

Gui gui;

int main()
{
	ImGui::SFML::Init(gui.getWindow());
	// Update and render GUI
	bool isRunning = true;
	while (isRunning)
	{
		sf::Clock frameTime;
		while(frameTime.getElapsedTime().asSeconds() < 1/60.f)
		{
			isRunning = gui.update();
		}
		gui.render();
		frameTime.restart();
	}
	ImGui::SFML::Shutdown();
}
