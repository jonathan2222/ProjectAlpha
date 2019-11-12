#include "WorldLoader.h"

#include <fstream>

pa::WorldLoader::WorldLoader(const std::string& worldName) : worldName(worldName)
{
}

void pa::WorldLoader::loadLookupTable()
{
	// Open file for input.
	std::ifstream file(this->worldName + ".lut", std::ios::binary);
	if (file.is_open())
	{
		this->lookup.clear();

		// Get number of chunks in file.
		int numChunks = 0;
		file.read((char*)(&numChunks), sizeof(numChunks));

		// Load each chunk.
		for (int i = 0; i < numChunks; i++)
		{
			ChunkFileKey key;
			file.read((char*)(&key), sizeof(key));
			this->lookup.push_back(key);
		}

		file.close();
	}
}

void pa::WorldLoader::saveLookupTable()
{
	// Open file for output.
	std::ofstream file(this->worldName + ".lut", std::ios::binary);
	if (file.is_open())
	{
		// Write number of chunks to file.
		int numChunks = this->lookup.size();
		file.write((char*)(&numChunks), sizeof(numChunks));

		// Write each chunk to file.
		for (ChunkFileKey& key : this->lookup)
		{
			file.write((char*)(&key), sizeof(key));
		}

		file.close();
	}
}

void pa::WorldLoader::updateChunk(Chunk* chunk, int x, int y)
{
	// Open file for input.
	std::ifstream file(this->worldName + ".chd", std::ios::binary);

	if (file.is_open())
	{
		// TODO: This is bad to use!
		char data[CHUNK_AREA];

		if (this->lookup.empty() == false)
		{
			auto& it = find(x, y);
			if (it != this->lookup.end())
			{
				// Load from chunk pos
				ChunkFileKey& key = *it;
				long pos = key.offset;
				file.seekg(pos);
			}
			else
			{
				// Chunk not found!
				file.close();
				return;
			}

		}

		// Load from disk
		file.read(data, CHUNK_AREA);

		decode(data, chunk);
		file.close();
	}
}

void pa::WorldLoader::saveChunk(Chunk* chunk, int x, int y)
{
	// Open file for output.
	std::ofstream file(this->worldName + ".chd", std::ios::binary);

	if (file.is_open())
	{
		if (this->lookup.empty() == false)
		{
			auto& it = find(x, y);
			if (it != this->lookup.end())
			{
				// Insert at chunk pos
				ChunkFileKey& key = *it;
				long pos = key.offset;
				file.seekp(pos);
			}
			else
			{
				// Append to end of file.
				ChunkFileKey& key = this->lookup.back();
				ChunkFileKey newKey;
				newKey.x = x;
				newKey.y = y;
				newKey.offset = key.offset + key.size;
				newKey.size = sizeof(BYTE) * CHUNK_AREA;
				this->lookup.push_back(newKey);
				file.seekp(newKey.offset);
			}
		}
		else 
		{
			// Append first key to file.
			ChunkFileKey newKey;
			newKey.x = x;
			newKey.y = y;
			newKey.offset = 0;
			newKey.size = sizeof(BYTE) * CHUNK_AREA;
			this->lookup.push_back(newKey);
		}

		// Save to disk
		auto& p = encode(chunk);
		file.write(p.first, p.second);

		file.close();
	}
}

void pa::WorldLoader::defragment()
{
}

std::pair<char*, int> pa::WorldLoader::encode(Chunk* chunk)
{
	return std::pair<char*, int>(chunk->getAllData(), sizeof(BYTE) * CHUNK_AREA);
}

void pa::WorldLoader::decode(char* data, Chunk* chunk)
{
	chunk->setAllData(data);
}

std::vector<pa::ChunkFileKey>::iterator pa::WorldLoader::find(int x, int y)
{
	for (std::vector<pa::ChunkFileKey>::iterator& it = this->lookup.begin(); it != this->lookup.end(); it++)
	{
		ChunkFileKey& key = *it;
		if (key.x == x && key.y == y)
			return it;
	}
	return this->lookup.end();
}
