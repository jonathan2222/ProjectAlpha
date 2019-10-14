#include "Chunk.h"

using namespace pa;

Chunk::Chunk(const sf::Vector2i& index) : index(index)
{
	this->cells = new BYTE[CHUNK_AREA];
}

Chunk::~Chunk()
{
	delete this->cells;
}

void Chunk::setData(int x, int y, BYTE data)
{
	int offset = y * CHUNK_SIZE + x;
	this->cells[offset] = data;
}

BYTE Chunk::getData(int x, int y) const
{
	int offset = y * CHUNK_SIZE + x;
	return this->cells[offset];
}

sf::Vector2i pa::Chunk::getIndex() const
{
	return this->index;
}
