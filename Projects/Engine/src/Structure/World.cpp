#include "World.h"

#include "../IO/Input.h"
#include <iostream>

pa::World::World(int rows, int cols, Generator* generator) 
	: grid(rows, cols), 
	gridPos(0, 0),
	worldCam(256.0f, 0.1f, sf::Vector2f(0.f, 0.f), sf::Vector2f(1920, 1080))
{
	this->builder.setGenerator(generator);
}

void pa::World::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	win.setView(this->worldCam.getView());
	// Draw chunks
	grid.draw(win, state);
}

void pa::World::update(const float& dt)
{
	// Camera movement
	this->worldCam.freeMove(dt);

	if (Input::get().isMB(Input::Pressed, Input::MB::Left)) {
		
		sf::Vector2f mousePos = this->worldCam.getMouseGlobalPos();

		sf::Vector2i gridIndex = this->grid.getChunkIndex(mousePos);
		sf::Vector2i cellIndex = this->grid.getCellIndex(mousePos);

		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << 
			" CellX: " << cellIndex.x << " CellY: " << cellIndex.y <<
			" GridX: " << gridIndex.x << " GridY: " << gridIndex.y << std::endl;
	}
}

void pa::World::updateChunks()
{
	std::vector<pa::Chunk*> chunks = grid.getChunks();
	const int cols = grid.getCols();
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < grid.getRows(); y++) {
			pa::Chunk* c = chunks[x + y*cols];
			this->builder.generate(gridPos.x + x, gridPos.y + y, c);
			grid.updateUVCoords(sf::Vector2u(x, y));
		}
	}
}

sf::Vector2i pa::World::getGridPos() const
{
	return this->gridPos;
}

void pa::World::offsetGridPos(sf::Vector2i offset)
{
	this->gridPos += offset;
}

pa::Camera& pa::World::getCamera()
{
	return this->worldCam;
}

pa::GridManager& pa::World::getGridManager()
{
	return this->grid;
}

pa::WorldBuilder& pa::World::getWorldBuilder()
{
	return this->builder;
}
