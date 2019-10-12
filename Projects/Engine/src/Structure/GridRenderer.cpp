#include "GridRenderer.h"

#include "Chunk.h"
#include "GridHandler.h"

using namespace pa;

GridRenderer::GridRenderer(const std::vector<Chunk*>* chunks)
	: chunks(chunks),
	showChunkGrid(true),
	quads(sf::Quads, this->chunks->size() * CHUNK_AREA * 4),
	debugLines(nullptr)
{
	this->generateQuads();
	if (showChunkGrid)
		this->generateDebugLines(sf::Color::Blue);
}

GridRenderer::~GridRenderer()
{
	delete this->debugLines;
}

void pa::GridRenderer::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	win.draw(this->quads, state);
	if(this->showChunkGrid)
		win.draw(*this->debugLines);
}

void pa::GridRenderer::generateQuads()
{
	int vIndex = 0;
	int chunkCount = 1;
	BYTE cellIndex = 0;

	float centreToBorder = 0; //(GRID_SIZE / 2) * CHUNK_SIZE * CELL_SIZE;
	const sf::Vector2f centreOffset = sf::Vector2f(-centreToBorder, -centreToBorder);
	sf::Vector2f globalOffset = centreOffset;

	for (const Chunk* c : *this->chunks) {
		cellIndex = c->getIndex(0, 0);

		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {


				sf::Vector2f quadOffset = sf::Vector2f(CELL_SIZE * x, CELL_SIZE * y);
				this->quads[vIndex + 0].position = sf::Vector2f(0.f, CELL_SIZE) + globalOffset + quadOffset;
				this->quads[vIndex + 1].position = sf::Vector2f(0.f, 0.f) + globalOffset + quadOffset;
				this->quads[vIndex + 2].position = sf::Vector2f(CELL_SIZE, 0.f) + globalOffset + quadOffset;
				this->quads[vIndex + 3].position = sf::Vector2f(CELL_SIZE, CELL_SIZE) + globalOffset + quadOffset;

				this->quads[vIndex + 0].texCoords = sf::Vector2f(0.f, 0.f);
				this->quads[vIndex + 1].texCoords = sf::Vector2f(CELL_SIZE, 0.f);
				this->quads[vIndex + 2].texCoords = sf::Vector2f(CELL_SIZE, CELL_SIZE);
				this->quads[vIndex + 3].texCoords = sf::Vector2f(0.f, CELL_SIZE);

				vIndex += 4;
			}
		}
		globalOffset.x += CHUNK_SIZE * CELL_SIZE;

		if ((chunkCount % GRID_SIZE) == 0) {
			globalOffset.y += CHUNK_SIZE * CELL_SIZE;
			globalOffset.x = centreOffset.x;
		}

		chunkCount++;
	}
}

void pa::GridRenderer::generateDebugLines(const sf::Color& color)
{
	if (this->debugLines)
		return;

	this->debugLines = new sf::VertexArray(sf::Lines, ((GRID_SIZE-1) * 2) * 2 + 8);

	int vIndex = 0;
	int chunkCount = 1;
	BYTE cellIndex = 0;

	float centreToBorder = 0; //(GRID_SIZE / 2) * CHUNK_SIZE * CELL_SIZE;
	const sf::Vector2f centreOffset = sf::Vector2f(-centreToBorder, -centreToBorder);
	sf::Vector2f globalOffset = centreOffset;


	// Create border lines
	const int gridLenPixel = GRID_SIZE * CHUNK_SIZE * CELL_SIZE;
	(*this->debugLines)[0].position = centreOffset;
	(*this->debugLines)[1].position = centreOffset + sf::Vector2f(gridLenPixel, 0.f);
	(*this->debugLines)[2].position = centreOffset + sf::Vector2f(gridLenPixel, 0.f);
	(*this->debugLines)[3].position = centreOffset + sf::Vector2f(gridLenPixel, gridLenPixel);
	(*this->debugLines)[4].position = centreOffset + sf::Vector2f(gridLenPixel, gridLenPixel);
	(*this->debugLines)[5].position = centreOffset + sf::Vector2f(0.f, gridLenPixel);
	(*this->debugLines)[6].position = centreOffset + sf::Vector2f(0.f, gridLenPixel);
	(*this->debugLines)[7].position = centreOffset;

	vIndex = 8;

	const int chunkLenPixel = CHUNK_SIZE * CELL_SIZE;
	for (int offset = 1; offset < GRID_SIZE; offset++) {
		// Vertical Lines
		(*this->debugLines)[vIndex + 0].position = centreOffset + sf::Vector2f(offset * chunkLenPixel, 0.f);
		(*this->debugLines)[vIndex + 1].position = centreOffset + sf::Vector2f(offset * chunkLenPixel, gridLenPixel);

		// Horizontal lines
		(*this->debugLines)[vIndex + 2].position = centreOffset + sf::Vector2f(0.f, offset * chunkLenPixel);
		(*this->debugLines)[vIndex + 3].position = centreOffset + sf::Vector2f(gridLenPixel, offset * chunkLenPixel);

		vIndex += 4;
	}

	// Apply color
	size_t vCount = this->debugLines->getVertexCount();
	for (int i = 0; i < vCount; i++)
		(*this->debugLines)[i].color = color;
}
