#ifndef PA_WORLD_BUILDER_H
#define PA_WORLD_BUILDER_H

#include "Generator.h"

namespace pa
{
	class WorldBuilder
	{
	public:
		WorldBuilder();
		virtual ~WorldBuilder();

		void setGenerator(Generator* generator);
		void generate(Chunk* chunk);

	private:
		Generator* generator;
	};
}

#endif
