#include "World.h"

#include "../IO/Input.h"
#include <iostream>

pa::World::World(int rows, int cols, Generator* generator, const std::string& name)
	: grid(rows, cols), 
	gridPos(0, 0),
	worldCam(256.0f, 0.1f, sf::Vector2f(0.f, 0.f), sf::Vector2f(1920, 1080))
{
	this->builder.setGenerator(generator);
	this->loader.init(name);
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
		
		sf::Vector2i mousePos = Input::get().getMousePosition();
		sf::Vector2f globalMouse = this->worldCam.getGlobalMousePos();
		sf::Vector2i chunkIndex = this->grid.getChunkIndex(globalMouse);
		sf::Vector2i cellIndex = this->grid.getCellIndex(globalMouse);
	
		sf::Vector2i relVec = chunkIndex - this->grid.getChunkIndex(this->worldCam.getWorldPos());
		relVec.x += this->grid.getCols() / 2;
		relVec.y += this->grid.getRows() / 2;
		relVec.y = (this->grid.getRows() - relVec.y) - 1;
		
		this->grid.getChunk(relVec)->setData(cellIndex.x, cellIndex.y, 7);
		this->grid.getChunk(relVec)->setModified(true);
		this->grid.updateUVCoords(sf::Vector2u(relVec));

		std::cout << "x: " << globalMouse.x << " y: " << globalMouse.y <<
			" CellX: " << cellIndex.x << " CellY: " << cellIndex.y <<
			" ChubkX: " << relVec.x << " ChunkY: " << relVec.y << std::endl;
	}
}

void pa::World::saveChunks()
{
	bool hasSaved = false;

	std::vector<pa::Chunk*> chunks = grid.getChunks();
	const int cols = grid.getCols();
	const int rows = grid.getRows();
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			pa::Chunk* c = chunks[x + y * cols];
			int chunkX = gridPos.x + x - cols/2;
			int chunkY = gridPos.y + y - rows/2;

			// Save chunk if modifed.
			if (c->isModified())
			{
				c->setModified(false);
				this->loader.saveChunk(c, chunkX, chunkY);
				hasSaved = true;
			}
		}
	}

	// If one or more chunks was saved, save the lookup table again.
	if (hasSaved)
	{
		this->loader.saveLookupTable();
	}
}

void pa::World::loadChunks()
{
	std::vector<ChunkFileKey>::iterator it;

	std::vector<pa::Chunk*> chunks = grid.getChunks();
	const int cols = grid.getCols();
	const int rows = grid.getRows();
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			pa::Chunk* c = chunks[x + y * cols];
			int chunkX = gridPos.x + x - cols / 2;
			int chunkY = gridPos.y + y - rows / 2;

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
}

void pa::World::updateChunks()
{
	loadChunks();
	saveChunks();
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
