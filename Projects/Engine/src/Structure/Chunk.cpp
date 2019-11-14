#include "Chunk.h"

using namespace pa;

Chunk::Chunk(const sf::Vector2i& index) : modified(false)
{
	this->cells = new PA_BYTE[CHUNK_AREA];
}

Chunk::~Chunk()
{
	delete this->cells;
}

void Chunk::setData(int x, int y, PA_BYTE data)
{
	int offset = y * CHUNK_SIZE + x;
	this->cells[offset] = data;
}

PA_BYTE Chunk::getData(int x, int y) const
{
	int offset = y * CHUNK_SIZE + x;
	return this->cells[offset];
}

PA_BYTE* pa::Chunk::getAllData()
{
	return this->cells;
}

void pa::Chunk::setAllData(PA_BYTE* data)
{
	for (int i = 0; i < CHUNK_AREA; i++)
	{
		this->cells[i] = data[i];
	}
}

bool pa::Chunk::isModified() const
{
	return this->modified;
}

void pa::Chunk::setModified(bool modified)
{
	this->modified = modified;
}
