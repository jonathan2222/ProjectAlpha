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

void pa::WorldBuilder::generate(std::vector<Chunk*>& chunks)
{
	this->generator->generate(chunks);
}
