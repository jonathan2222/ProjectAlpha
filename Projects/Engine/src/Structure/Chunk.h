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
			PA_BYTE data;
		};

	public:
		Chunk(const sf::Vector2i& index);
		~Chunk();

		void setData(int x, int y, PA_BYTE data);
		PA_BYTE getData(int x, int y) const;

		PA_BYTE* getAllData();
		void setAllData(PA_BYTE* data);

		bool isModified() const;
		void setModified(bool modified);

	private:
		PA_BYTE* cells;
		bool modified;

	};
}

#endif