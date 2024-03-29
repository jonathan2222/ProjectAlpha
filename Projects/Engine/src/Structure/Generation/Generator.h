#ifndef PA_GENERATOR_H
#define PA_GENERATOR_H

#include "../Chunk.h"
#include <vector>

namespace pa
{
	class Generator
	{
	public:
		virtual void generate(Chunk* chunk) = 0;
	};
}

#endif
