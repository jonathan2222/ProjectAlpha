#include "GridManager.h"

#include "Chunk.h"

using namespace pa;

GridManager::GridManager(int rows, int cols)
	: 
	rows(rows),
	cols(cols),
	showChunkGrid(true),
	quads(sf::Quads, rows * cols * CHUNK_AREA * 4),
	debugLines(nullptr)
{
	this->chunks.resize((size_t)this->rows * this->cols);
	for (int i = 0; i < this->rows * this->cols; i++)
		this->chunks[i] = new Chunk({ i%cols, i / rows });

	this->generateQuads();
	if (showChunkGrid)
		this->generateDebugLines(sf::Color::Blue);
}

GridManager::~GridManager()
{
	for (Chunk* c : this->chunks) {
		delete c;
	}

	delete this->debugLines;
}

std::vector<Chunk*>& pa::GridManager::getChunks()
{
	return this->chunks;
}

void pa::GridManager::updateUVCoords(const sf::Vector2u chunkIndex)
{
	if (chunkIndex.x < this->cols && chunkIndex.y < this->cols) {

		Chunk* chunk = this->chunks[chunkIndex.x + chunkIndex.y * this->cols];

		int vIndex = (chunkIndex.x + chunkIndex.y * this->cols) * CHUNK_AREA * 4;
		const float tileSize = 16.f;
		const int textureSize = 256;

		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				BYTE cellData = chunk->getData(x, y);

				sf::Vector2f uvOffset((float)((cellData*(int)tileSize) % textureSize), (float)((int)(cellData * (int)tileSize) / textureSize));
				this->quads[vIndex + 0].texCoords = uvOffset + sf::Vector2f(0.f, 0.f);
				this->quads[vIndex + 1].texCoords = uvOffset + sf::Vector2f(tileSize, 0.f);
				this->quads[vIndex + 2].texCoords = uvOffset + sf::Vector2f(tileSize, tileSize);
				this->quads[vIndex + 3].texCoords = uvOffset + sf::Vector2f(0.f, tileSize);

				vIndex += 4;
			}
		}
	}
}

void pa::GridManager::draw(sf::RenderWindow& win, const sf::RenderStates& state)
{
	win.draw(this->quads, state);
	if(this->showChunkGrid)
		win.draw(*this->debugLines);
}

void pa::GridManager::generateQuads()
{
	int vIndex = 0;
	int chunkCount = 1;

	const float gridRowsPixel = this->rows * CHUNK_SIZE * CELL_SIZE;
	const float gridColsPixel = this->cols * CHUNK_SIZE * CELL_SIZE;
	const sf::Vector2f centreOffset = sf::Vector2f(-gridColsPixel, -gridRowsPixel) * 0.5f;
	sf::Vector2f globalOffset = centreOffset;

	const float tileSize = 16.f;
	const int textureSize = 256;

	for (const Chunk* c : this->chunks) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				sf::Vector2f quadOffset = sf::Vector2f((float)CELL_SIZE * x, (float)CELL_SIZE * y);
				this->quads[vIndex + 0].position = sf::Vector2f(0.f, CELL_SIZE) + globalOffset + quadOffset;
				this->quads[vIndex + 1].position = sf::Vector2f(0.f, 0.f) + globalOffset + quadOffset;
				this->quads[vIndex + 2].position = sf::Vector2f(CELL_SIZE, 0.f) + globalOffset + quadOffset;
				this->quads[vIndex + 3].position = sf::Vector2f(CELL_SIZE, CELL_SIZE) + globalOffset + quadOffset;

				BYTE cellData = 0;
				sf::Vector2f uvOffset((float)((cellData*(int)tileSize)% textureSize), (float)((int)(cellData * (int)tileSize) / textureSize));
				this->quads[vIndex + 0].texCoords = uvOffset + sf::Vector2f(0.f, 0.f);
				this->quads[vIndex + 1].texCoords = uvOffset + sf::Vector2f(tileSize, 0.f);
				this->quads[vIndex + 2].texCoords = uvOffset + sf::Vector2f(tileSize, tileSize);
				this->quads[vIndex + 3].texCoords = uvOffset + sf::Vector2f(0.f, tileSize);

				vIndex += 4;
			}
		}
		globalOffset.x += CHUNK_SIZE * CELL_SIZE;

		if ((chunkCount % this->cols) == 0) {
			globalOffset.y += CHUNK_SIZE * CELL_SIZE;
			globalOffset.x = centreOffset.x;
		}

		chunkCount++;
	}
}

void pa::GridManager::generateDebugLines(const sf::Color& color)
{
	if (this->debugLines)
		return;

	this->debugLines = new sf::VertexArray(sf::Lines, ((this->rows - 1) * 2 + (this->cols - 1) * 2 + 8));

	int vIndex = 0;
	int chunkCount = 1;
	BYTE cellIndex = 0;

	const float gridRowsPixel = this->rows * CHUNK_SIZE * CELL_SIZE;
	const float gridColsPixel = this->cols * CHUNK_SIZE * CELL_SIZE;
	const sf::Vector2f centreOffset = sf::Vector2f(-gridColsPixel, -gridRowsPixel) * 0.5f;
	sf::Vector2f globalOffset = centreOffset;

	// Create border lines
	(*this->debugLines)[0].position = centreOffset;
	(*this->debugLines)[1].position = centreOffset + sf::Vector2f(gridColsPixel, 0.f);
	(*this->debugLines)[2].position = centreOffset + sf::Vector2f(gridColsPixel, 0.f);
	(*this->debugLines)[3].position = centreOffset + sf::Vector2f(gridColsPixel, gridRowsPixel);
	(*this->debugLines)[4].position = centreOffset + sf::Vector2f(gridColsPixel, gridRowsPixel);
	(*this->debugLines)[5].position = centreOffset + sf::Vector2f(0.f, gridRowsPixel);
	(*this->debugLines)[6].position = centreOffset + sf::Vector2f(0.f, gridRowsPixel);
	(*this->debugLines)[7].position = centreOffset;

	vIndex = 8;

	const int chunkLenPixel = CHUNK_SIZE * CELL_SIZE;
	for (int offset = 1; offset < this->cols; offset++) {
		// Vertical Lines
		(*this->debugLines)[vIndex + 0].position = centreOffset + sf::Vector2f((float)offset * chunkLenPixel, 0.f);
		(*this->debugLines)[vIndex + 1].position = centreOffset + sf::Vector2f((float)offset * chunkLenPixel, (float)gridRowsPixel);

		vIndex += 2;
	}

	for (int offset = 1; offset < this->rows; offset++) {
		// Horizontal lines
		(*this->debugLines)[vIndex + 0].position = centreOffset + sf::Vector2f(0.f, (float)offset * chunkLenPixel);
		(*this->debugLines)[vIndex + 1].position = centreOffset + sf::Vector2f((float)gridColsPixel, (float)offset * chunkLenPixel);

		vIndex += 2;
	}

	// Apply color
	size_t vCount = this->debugLines->getVertexCount();
	for (int i = 0; i < vCount; i++)
		(*this->debugLines)[i].color = color;
}
