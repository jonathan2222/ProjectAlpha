#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>
#include <Engine/src/Utils/Timer.h>
#include <iostream>

#include "Engine/src/Structure/World.h"
#include "Engine/src/Structure/Rendering/Renderer.h"
#include "Generation/MyGenerator.h"

#include <cmath>

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Display& display = Display::get();
	display.init(1920, 1080, "Hellow World!");
	pa::Input::get().init(display);



	sf::Texture atlas;

	if (!atlas.loadFromFile("res/tile_atlas.png")) {
		std::cout << "Failed to load texture!" << std::endl;
	}

	sf::RenderStates states;
	states.texture = &atlas;

	sf::Vector2i gridPos(0, 0);

	const int gridRows = 5;
	const int gridCols = 9;

	MyGenerator generator;
	pa::World testWorld(gridRows, gridCols, &generator, "res/World/TestWorld");

	pa::Renderer renderer;

	testWorld.updateChunks();
	pa::Timer timer;

	while (display.isOpen())
	{
		pa::Input::get().update();

		// Check if world needs to load in new information. 
		renderer.renderWorld(testWorld);
		
		testWorld.update(timer.getDeltaTime());
		testWorld.draw(display.getWindow(), states);

		display.swapBuffers();
		timer.update();
	}

	return 0;
}