#ifndef PA_WORLD_H
#define PA_WORLD_H

#include "GridManager.h"
#include "Generation/WorldBuilder.h"
#include "Generation/Generator.h"
#include "../Serialization/WorldLoader.h"

#include "Camera.h"

namespace pa
{
	class World
	{
	public:
		World(int rows, int cols, Generator* generator, const std::string& name);
		
		void draw(sf::RenderWindow& win, const sf::RenderStates& state);
		void update(const float& dt);

		void updateChunks();

		sf::Vector2i getGridPos() const;
		void offsetGridPos(sf::Vector2i offset);

		Camera& getCamera();

		GridManager& getGridManager();
		WorldBuilder& getWorldBuilder();

	private:
		Camera worldCam;

		GridManager grid;
		WorldBuilder builder;
		WorldLoader loader;
		sf::Vector2i gridPos;
	};
}

#endif
