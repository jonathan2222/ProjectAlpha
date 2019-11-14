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
		WorldLoader();

		void init(const std::string& worldName);

		void loadLookupTable();
		void saveLookupTable();

		void updateChunk(Chunk* chunk, int x, int y);
		void saveChunk(Chunk* chunk, int x, int y);

		std::vector<ChunkFileKey>::iterator find(int x, int y);
		std::vector<ChunkFileKey>::iterator listBegin();
		std::vector<ChunkFileKey>::iterator listEnd();

		void defragment();
	private:
		std::pair<char*, int> encode(Chunk* chunk);
		void decode(char* data, Chunk* chunk);

		std::vector<ChunkFileKey> lookup;
		std::string worldName;
	};
}

#endif
