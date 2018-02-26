//
// skulk@ioc.ninja
//
#include "xRandom.h"

#include <stdlib.h>



uint32_t xRandomNumber(const uint32_t min, const uint32_t max)
{
	srand(X_RANDOM_NUMBER(0, 0xffff));

	return min + (rand() % ((uint32_t ) (max - min + 1)));
}