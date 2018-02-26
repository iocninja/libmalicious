//
// skulk@ioc.ninja
//
#pragma once



#include <stdint.h>



template <uint32_t _Value> struct xRandom
{
	enum : uint32_t
	{
		value = _Value
	};
};



#define X_RANDOM_SEED \
( \
	(__TIME__[7] - '0') * 1 + \
	(__TIME__[6] - '0') * 10 + \
	(__TIME__[4] - '0') * 60 + \
	(__TIME__[3] - '0') * 600 + \
	(__TIME__[1] - '0') * 3600 + \
	(__TIME__[0] - '0') * 36000 \
)



constexpr uint32_t xRandomLinearCongruentGenerator(const uint32_t rounds)
{
	return 1500450271ull + 1660661ull * ((uint32_t) ((rounds > 0) ? xRandomLinearCongruentGenerator(rounds - 1) : X_RANDOM_SEED & 0xffffffff));
}



#define X_RANDOM_ROUNDS (0xc0 + (X_RANDOM_SEED & 0x0000000f))

#define X_RANDOM() xRandom<xRandomLinearCongruentGenerator(X_RANDOM_ROUNDS)>::value

#define X_RANDOM_NUMBER(min, max) (min + (X_RANDOM() % (max - min + 1)))



uint32_t xRandomNumber(const uint32_t min, const uint32_t max);
