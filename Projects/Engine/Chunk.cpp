#include "Chunk.h"

using namespace pa;

Chunk::Chunk()
{
	this->cells = new BYTE[CHUNK_LEN_IN_CELLS];
}

Chunk::~Chunk()
{
	delete this->cells;
}

void Chunk::setIndex(int x, int y, BYTE index)
{
	int offset = y * CHUNK_LEN_IN_CELLS + x;
	this->cells[offset] = index;
}

BYTE Chunk::getIndex(int x, int y) const
{
	int offset = y * CHUNK_LEN_IN_CELLS + x;
	return this->cells[offset];
}
