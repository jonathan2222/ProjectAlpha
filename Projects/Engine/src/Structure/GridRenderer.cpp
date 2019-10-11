#include "GridRenderer.h"

#include "Chunk.h"
#include "GridHandler.h"

using namespace pa;

GridRenderer::GridRenderer(const std::vector<Chunk*>* chunks)
	: chunks(chunks),
	quads(sf::Quads, this->chunks->size() * CHUNK_AREA * 4)
{

	int vIndex = 0;
	int chunkCount = 0;
	BYTE cellIndex = 0;

	float centreToBorder = (CHUNK_SIZE / 2) * CELL_SIZE;
	const sf::Vector2f centreOffset = sf::Vector2f(-centreToBorder, -centreToBorder);
	sf::Vector2f globalOffset = centreOffset;

	for (const Chunk* c : *this->chunks) {
		cellIndex = c->getIndex(0, 0);

		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				

				sf::Vector2f quadOffset = sf::Vector2f(CELL_SIZE * x, CELL_SIZE * y);
				this->quads[vIndex + 0].position = sf::Vector2f(0.f, CELL_SIZE)			+ globalOffset + quadOffset;
				this->quads[vIndex + 1].position = sf::Vector2f(0.f, 0.f)				+ globalOffset + quadOffset;
				this->quads[vIndex + 2].position = sf::Vector2f(CELL_SIZE, 0.f)			+ globalOffset + quadOffset;
				this->quads[vIndex + 3].position = sf::Vector2f(CELL_SIZE, CELL_SIZE)	+ globalOffset + quadOffset;

				this->quads[vIndex + 0].texCoords = sf::Vector2f(0.f, 0.f);
				this->quads[vIndex + 1].texCoords = sf::Vector2f(CELL_SIZE, 0.f);
				this->quads[vIndex + 2].texCoords = sf::Vector2f(CELL_SIZE, CELL_SIZE);
				this->quads[vIndex + 3].texCoords = sf::Vector2f(0.f, CELL_SIZE);

				vIndex += 4;
			}
		}
		globalOffset.x += CHUNK_SIZE * CELL_SIZE;

		if (chunkCount % GRID_SIZE) {
			globalOffset.y += CHUNK_SIZE * CELL_SIZE;
			globalOffset.x = centreOffset.x;
		}

		chunkCount++;
	}

}

GridRenderer::~GridRenderer()
{
}

void pa::GridRenderer::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	win.draw(this->quads, state);
}
