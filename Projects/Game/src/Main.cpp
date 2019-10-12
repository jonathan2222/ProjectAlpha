#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>
#include <iostream>


#include "Engine/src/Structure/GridHandler.h"
#include "Engine/src/Structure/GridRenderer.h"

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Display display{ 600, 400, "Hellow World!" };
	
	pa::Input::get().init(display);

	sf::Texture atlas;

	if (!atlas.loadFromFile("res/tile_atlas.png")) {
		std::cout << "Failed to load texture!" << std::endl;
	}
	sf::View view;
	view.zoom(2.0f);
	sf::RenderStates states;
	states.texture = &atlas;

	pa::GridHandler gh;
	
	pa::GridRenderer gr(gh.getAllChunks());

	while (display.isOpen())
	{
		pa::Input::get().update();
		
		display.getWindow().setView(view);
		gr.draw(display.getWindow(), states);

		display.swapBuffers();
	}

	return 0;
}