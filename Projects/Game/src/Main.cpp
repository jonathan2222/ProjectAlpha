#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>
#include <Engine/src/Utils/Timer.h>
#include <iostream>

#include "Engine/src/Structure/Camera.h"

#include "Engine/src/Structure/GridManager.h"
#include "Engine/src/Structure/Generation/WorldBuilder.h"
#include "Generation/MyGenerator.h"

#include <cmath>

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Display display{ 1920, 1080, "Hellow World!" };
	
	pa::Input::get().init(display);

	// Create camera
	pa::Camera cam(256.0f, 0.1f, sf::Vector2f(0.f, 0.f), sf::Vector2f(1920, 1080));

	sf::Texture atlas;

	if (!atlas.loadFromFile("res/tile_atlas.png")) {
		std::cout << "Failed to load texture!" << std::endl;
	}

	sf::RenderStates states;
	states.texture = &atlas;

	sf::Vector2i gridPos(0, 0);

	const int gridRows = 5;
	const int gridCols = 10;
	pa::GridManager grid(gridRows, gridCols);
	pa::WorldBuilder wb;
	MyGenerator generator;

	wb.setGenerator(&generator);
	std::vector<pa::Chunk*> chunks = grid.getChunks();
	// PUT THIS IN world builder
	for (int x = 0; x < gridCols; x++) {
		for (int y = 0; y < gridRows; y++) {
			pa::Chunk * c = chunks[x + y * gridCols];
			wb.generate(gridPos.x+x, gridPos.y+y, c);
			grid.updateUVCoords(sf::Vector2u(x, y));
		}
	}

	pa::Timer timer;
	while (display.isOpen())
	{
		pa::Input::get().update();
		
		// Camera movement
		cam.freeMove(timer.getDeltaTime());
		display.getWindow().setView(cam.getView());

		
			
		// Draw chunks
		grid.draw(display.getWindow(), states);

		display.swapBuffers();
		timer.update();
	}

	return 0;
}