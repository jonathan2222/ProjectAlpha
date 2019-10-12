#ifndef PA_MY_GENERATOR_H
#define PA_MY_GENERATOR_H

#include "Engine/src/Structure/Generation/Generator.h"

class MyGenerator : public pa::Generator
{
public:
	void generate(pa::Chunk* chunk) override;

private:
	BYTE getEnvironmentData(int y);
};

#endif
