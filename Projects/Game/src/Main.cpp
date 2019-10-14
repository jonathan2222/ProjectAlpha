#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>
#include <Engine/src/Utils/Timer.h>
#include <Engine/src/Utils/Logger.h>
#include <iostream>

#include "Engine/src/Structure/Camera.h"

#include "Engine/src/Structure/GridHandler.h"
#include "Engine/src/Structure/GridRenderer.h"
#include "Engine/src/Structure/Generation/WorldBuilder.h"
#include "Generation/MyGenerator.h"

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	PA_LOG_INIT();
	Display display{ 600, 400, "Hellow World!" };
	
	pa::Input::get().init(display);

	// Create camera
	pa::Camera cam(256.0f, 0.1f, sf::Vector2f(0.f, 0.f));

	sf::Texture atlas;

	if (!atlas.loadFromFile("res/tile_atlas.png")) {
		PA_LOG_WARN("Failed to load texture!");
	}

	sf::RenderStates states;
	states.texture = &atlas;

	pa::GridHandler gh;
	
	pa::WorldBuilder wb;
	MyGenerator generator;
	wb.setGenerator(&generator);
	for(pa::Chunk* chunk : *gh.getAllChunks())
		wb.generate(chunk);

	pa::GridRenderer gr(gh.getAllChunks());

	pa::Timer timer;
	while (display.isOpen())
	{
		pa::Input::get().update();
		
		// Camera movement
		cam.freeMove(timer.getDeltaTime());
		display.getWindow().setView(cam.getView());

		// Draw chunks
		gr.draw(display.getWindow(), states);

		display.swapBuffers();
		timer.update();
	}

	return 0;
}