#include "World.h"

pa::World::World(int rows, int cols, Generator* generator, const std::string& name) : grid(rows, cols), gridPos(0, 0)
{
	this->builder.setGenerator(generator);
	this->loader.init(name);
}

void pa::World::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	// Draw chunks
	grid.draw(win, state);
}

void pa::World::updateChunks()
{
	std::vector<ChunkFileKey>::iterator it;

	bool hasSaved = false;

	std::vector<pa::Chunk*> chunks = grid.getChunks();
	const int cols = grid.getCols();
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < grid.getRows(); y++) {
			pa::Chunk* c = chunks[x + y*cols];
			int chunkX = gridPos.x + x;
			int chunkY = gridPos.y + y;

			// Save chunk if modifed.
			if (c->isModified())
			{
				c->setModified(false);
				this->loader.saveChunk(c, chunkX, chunkY);
				hasSaved = true;
			}

			// If chunk was not found on disk, generate a new one.
			it = this->loader.find(chunkX, chunkY);
			if (it == this->loader.listEnd())
			{
				this->builder.generate(chunkX, chunkY, c);
			}
			else
			{
				// Load the chunk from disk.
				this->loader.updateChunk(c, chunkX, chunkY);
			}
			
			grid.updateUVCoords(sf::Vector2u(x, y));
		}
	}

	// If one or more chunks was saved, save the lookup table again.
	if (hasSaved)
	{
		this->loader.saveLookupTable();
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
