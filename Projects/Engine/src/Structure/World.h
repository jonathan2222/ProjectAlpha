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

		void draw(sf::RenderWindow& win, const sf::RenderStates& state);

		void updateChunks();

		sf::Vector2i getGridPos() const;
		void offsetGridPos(sf::Vector2i offset);
		GridManager& getGridManager();
		WorldBuilder& getWorldBuilder();

	private:
		GridManager grid;
		WorldBuilder builder;
		sf::Vector2i gridPos;
	};
}

#endif
