#ifndef PA_GRID_HANDLER_H
#define PA_GRID_HANDLER_H

#include <vector>
#include "Chunk.h"

#define GRID_SIZE 4

namespace pa {

	class GridHandler
	{
	public:
		GridHandler();
		~GridHandler();

		Chunk* getChunk(int x, int y);
		const std::vector<Chunk*>* getAllChunks() const;

	private:
		const int chunkRows;
		const int chunkCols;

		std::vector<Chunk*> chunks;
	};
}
#endif