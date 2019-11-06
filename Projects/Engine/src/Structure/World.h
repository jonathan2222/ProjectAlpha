#ifndef PA_WORLD_H
#define PA_WORLD_H

#include "GridManager.h"
#include "Generation/WorldBuilder.h"
#include "Generation/Generator.h"

namespace pa
{
	class World
	{
	public:
		World(int rows, int cols, Generator* generator);

		sf::Vector2i getGridPos() const;
		GridManager& getGridManager();
		WorldBuilder& getWorldBuilder();

	private:
		GridManager grid;
		WorldBuilder builder;
		sf::Vector2i gridPos;
	};
}

#endif
