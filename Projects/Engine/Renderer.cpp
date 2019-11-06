#include "Renderer.h"

#include "src/Structure/Camera.h"
#include "src/Structure/World.h"

//Temp to access chunk
#include "src/Structure/Chunk.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::renderWorld(World& world, Camera& cam)
{
	/*if (abs(cam.getCentre().x) > CHUNK_SIZE * CELL_SIZE) {
		cam.setCentre(sf::Vector2f(0.f, camPos.y));
		gridPos.x += int(abs(camPos.x) / camPos.x);

		std::vector<pa::Chunk*> chunks = grid.getChunks();
		for (int x = 0; x < gridCols; x++) {
			for (int y = 0; y < gridRows; y++) {
				pa::Chunk * c = chunks[x + y * gridCols];
				wb.generate(gridPos.x + x, gridPos.y + y, c);
				grid.updateUVCoords(sf::Vector2u(x, y));
			}
		}
	}
	if (abs(cam.getCentre().y) > CHUNK_SIZE * CELL_SIZE) {
		cam.setCentre(sf::Vector2f(camPos.x, 0.f));
		gridPos.y += int(abs(camPos.y) / camPos.y);

		std::vector<pa::Chunk*> chunks = grid.getChunks();
		for (int x = 0; x < gridCols; x++) {
			for (int y = 0; y < gridRows; y++) {
				pa::Chunk * c = chunks[x + y * gridCols];
				wb.generate(gridPos.x + x, gridPos.y + y, c);
				grid.updateUVCoords(sf::Vector2u(x, y));
			}
		}
	}*/
}
