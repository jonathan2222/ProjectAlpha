#ifndef PA_CHUNK_H
#define PA_CHUNK_H

#include "../Types.h"

namespace pa {
	#define CHUNK_SIZE 16
	#define CELL_SIZE 16
	#define CHUNK_AREA CHUNK_SIZE * CHUNK_SIZE

	class Chunk
	{
		struct Cell {
			BYTE index;
		};

	public:
		Chunk();
		~Chunk();

		void setIndex(int x, int y, BYTE index);
		BYTE getIndex(int x, int y) const;

	private:
		BYTE* cells;

	};
}

#endif