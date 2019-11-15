#include "Renderer.h"

#include "../Camera.h"
#include "../World.h"

pa::Renderer::Renderer()
{
}

pa::Renderer::~Renderer()
{
}

void pa::Renderer::renderWorld(World& world)
{
	Camera& cam = world.getCamera();
	sf::Vector2f camPos = cam.getCentre();
	if (abs(camPos.x) > CHUNK_SIZE* CELL_SIZE) {
		// Generate and/or load chunks from file
		world.saveChunks();

		cam.setCentre(sf::Vector2f(0.f, camPos.y));
		world.offsetGridPos(sf::Vector2i(int(abs(camPos.x) / camPos.x), 0));

		// Save modified chunks
		world.loadChunks();
	}
	if (abs(cam.getCentre().y) > CHUNK_SIZE* CELL_SIZE) {
		// Generate and/or load chunks from file
		world.saveChunks();

		cam.setCentre(sf::Vector2f(camPos.x, 0.f));
		world.offsetGridPos(sf::Vector2i(0, int(abs(camPos.y) / camPos.y)));

		// Save modified chunks
		world.loadChunks();
	}

}
