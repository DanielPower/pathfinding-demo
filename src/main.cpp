#include "gui.h"

Gui gui;

int main() {
	gui.init();

	while (true) {
		gui.update();
	}
}