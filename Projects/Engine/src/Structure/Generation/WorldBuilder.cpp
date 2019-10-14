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

void pa::WorldBuilder::generate(Chunk* chunk)
{
	this->generator->generate(chunk);
}
