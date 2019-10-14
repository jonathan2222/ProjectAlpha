#include "MyGenerator.h"

#include <random>

void MyGenerator::generate(pa::Chunk* chunk)
{
	unsigned int seed = chunk->getIndex().x+ chunk->getIndex().y;
	std::srand(seed);
	
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			sf::Vector2i index = chunk->getIndex();
			BYTE data = getEnvironmentData(index.y*CHUNK_SIZE + y);
			chunk->setData(x, y, data);
		}
	}
}

BYTE MyGenerator::getEnvironmentData(int y)
{
	BYTE res = 6;
	int grass = 12;
	int dirt = 17;
	int dirtStone = 21;
	int stone = 29;
	int lavaStone = 34;
	int crystalLavaStone = 49;
	int crystal = 60;

	if (y > grass) res = 0;
	if (y > dirt) res = 1;
	if (y > dirtStone) res = (rand()%2) == 0 ? 1 : 4;
	if (y > stone) res = 4;
	if (y > lavaStone) res = (rand() % 2) == 0 ? 3 : 4;
	if (y > crystalLavaStone) res = (rand() % 2) == 0 ? 4 : ((rand() % 2) == 0 ? 3 : 2);
	if (y > crystal) res = 2;
	return res;
}
