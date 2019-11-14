#ifndef PA_MY_GENERATOR_H
#define PA_MY_GENERATOR_H

#include "Engine/src/Structure/Generation/Generator.h"

class MyGenerator : public pa::Generator
{
public:
	void generate(int Xindex, int Yindex, pa::Chunk* chunk) override;

private:
	PA_BYTE getEnvironmentData(int y);
};

#endif
