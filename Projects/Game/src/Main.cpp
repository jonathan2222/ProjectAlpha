#ifdef PA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <Engine/src/Display.h>
#include <Engine/src/IO/Input.h>

#include <iostream>

int main(int argc, char* argv[])
{
#ifdef PA_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Display display{ 600, 400, "Hellow World!" };
	
	pa::Input::get().init(display);

	while (display.isOpen())
	{
		pa::Input::get().update();
		
		glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.0f, 0.5f);
		glEnd();
		
		display.swapBuffers();
	}

	return 0;
}