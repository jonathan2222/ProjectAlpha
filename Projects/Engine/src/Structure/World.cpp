#include "World.h"

pa::World::World(int rows, int cols, Generator* generator) : grid(rows, cols), gridPos(0, 0)
{
	this->builder.setGenerator(generator);
}

void pa::World::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	// Draw chunks
	grid.draw(win, state);
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

pa::GridManager& pa::World::getGridManager()
{
	return this->grid;
}

pa::WorldBuilder& pa::World::getWorldBuilder()
{
	return this->builder;
}
