#include "World.h"

pa::World::World(int rows, int cols, Generator* generator) : grid(rows, cols), gridPos(0, 0)
{
	this->builder.setGenerator(generator);
}

sf::Vector2i pa::World::getGridPos() const
{
	return this->gridPos;
}

pa::GridManager& pa::World::getGridManager()
{
	return this->grid;
}

pa::WorldBuilder& pa::World::getWorldBuilder()
{
	return this->builder;
}
