#include "GridHandler.h"

#include <math.h>

using namespace pa;

GridHandler::GridHandler()
	: chunkRows(GRID_SIZE)
	, chunkCols(GRID_SIZE)
{
	//// Allocate instances
	//Chunk* ptr = new Chunk[chunkRows * chunkCols];

	// Assign instances to pointers
	this->chunks.resize((size_t)chunkRows * chunkCols);
	for (int i = 0; i < chunkRows * chunkCols; i++)
		this->chunks[i] = new Chunk({i% GRID_SIZE, i/GRID_SIZE});

	int a = this->chunks[this->chunks.size() - 1]->getData(0, 0);

}

GridHandler::~GridHandler()
{
	for (Chunk* c : this->chunks) {
		delete c;
	}
}

Chunk * GridHandler::getChunk(int x, int y)
{
	const int GRID_BORDER = (GRID_SIZE / 2) * CHUNK_SIZE;
	int xOffset = (x + GRID_BORDER) / CHUNK_SIZE;
	int yOffset = (y + GRID_BORDER) / CHUNK_SIZE;

	return this->chunks[xOffset + yOffset * GRID_SIZE];
}

const std::vector<Chunk*>* GridHandler::getAllChunks() const
{
	return &this->chunks;
}
