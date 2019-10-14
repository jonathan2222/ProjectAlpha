#include "WorldBuilder.h"

pa::WorldBuilder::WorldBuilder() : generator(nullptr)
{
}

pa::WorldBuilder::~WorldBuilder()
{
}

void pa::WorldBuilder::setGenerator(Generator* generator)
{
	this->generator = generator;
}

void pa::WorldBuilder::generate(int Xindex, int Yindex, Chunk* chunk)
{
	this->generator->generate(Xindex, Yindex, chunk);
}
