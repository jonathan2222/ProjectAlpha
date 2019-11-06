#ifndef PA_WORLD_LOADER_H
#define PA_WORLD_LOADER_H

#include <string>
#include <vector>
#include "../Structure/Chunk.h"

namespace pa
{
	struct ChunkFileKey
	{
		int x, y;
		long offset;
		long size;
	};

	class WorldLoader
	{
	public:
		WorldLoader(const std::string& worldName);

		// (x, y, i, s)
		void loadLookupTable();
		void saveLookupTable();

		void updateChunk(Chunk* chunk, int x, int y);
		void saveChunk(Chunk* chunk, int x, int y);

		void defragment();
	private:
		std::pair<char*, int> encode(Chunk* chunk);
		void decode(char* data, Chunk* chunk);

		std::vector<ChunkFileKey>::iterator find(int x, int y);

		std::vector<ChunkFileKey> lookup;
		std::string worldName;
	};
}

#endif
