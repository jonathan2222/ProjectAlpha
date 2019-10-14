#ifndef PA_CHUNK_H
#define PA_CHUNK_H

#include "../Types.h"
#include "SFML/System/Vector2.hpp"

namespace pa {
	#define CHUNK_SIZE 16
	#define CELL_SIZE 32
	#define CHUNK_AREA CHUNK_SIZE * CHUNK_SIZE

	class Chunk
	{
		struct Cell {
			BYTE data;
		};

	public:
		Chunk(const sf::Vector2i& index);
		~Chunk();

		void setData(int x, int y, BYTE data);
		BYTE getData(int x, int y) const;

	private:
		BYTE* cells;

	};
}

#endif