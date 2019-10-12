#include "Chunk.h"

using namespace pa;

Chunk::Chunk()
{
	this->cells = new BYTE[CHUNK_SIZE];
}

Chunk::~Chunk()
{
	delete this->cells;
}

void Chunk::setIndex(int x, int y, BYTE index)
{
	int offset = y * CHUNK_SIZE + x;
	this->cells[offset] = index;
}

BYTE Chunk::getIndex(int x, int y) const
{
	int offset = y * CHUNK_SIZE + x;
	return this->cells[offset];
}
