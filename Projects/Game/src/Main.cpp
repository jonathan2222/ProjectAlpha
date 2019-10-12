#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>
#include <iostream>

#include "Engine/src/Structure/Camera.h"

#include "Engine/src/Structure/GridHandler.h"
#include "Engine/src/Structure/GridRenderer.h"

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Display display{ 600, 400, "Hellow World!" };
	
	pa::Input::get().init(display);

	// Create camera
	pa::Camera cam(0.25f, 0.1f, sf::Vector2f(0.f, 0.f));

	sf::Texture atlas;

	if (!atlas.loadFromFile("res/tile_atlas.png")) {
		std::cout << "Failed to load texture!" << std::endl;
	}

	sf::RenderStates states;
	states.texture = &atlas;

	pa::GridHandler gh;
	
	pa::GridRenderer gr(gh.getAllChunks());

	while (display.isOpen())
	{
		pa::Input::get().update();
		
		// Camera movement
		cam.freeMove(1.0f);
		display.getWindow().setView(cam.getView());

		// Draw chunks
		gr.draw(display.getWindow(), states);

		display.swapBuffers();
	}

	return 0;
}