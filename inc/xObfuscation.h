//
// skulk@ioc.ninja
//
#pragma once



#include <stdint.h>
#include <Windows.h>

#include "xRandom.h"



#define X_OBFUSCATION_KEY_MODULO X_RANDOM_NUMBER(1, 0x0f)



template <uint32_t... _Pack> struct xObfuscationIndexList
{
};



template <typename xObfuscationIndexList, const uint32_t _Right> struct xObfuscationAppend;

template <uint32_t... _Left, uint32_t _Right> struct xObfuscationAppend<xObfuscationIndexList<_Left...>, _Right>
{
	typedef xObfuscationIndexList<_Left..., _Right> Result;
};



template <uint32_t _Value> struct xObfuscationConstructIndexList
{
	typedef typename xObfuscationAppend<typename xObfuscationConstructIndexList<_Value - 1>::Result, _Value - 1>::Result Result;
};



template <> struct xObfuscationConstructIndexList<0>
{
	typedef xObfuscationIndexList<> Result;
};



const uint8_t X_OBFUSCATION_KEY = static_cast<const uint8_t>(X_RANDOM_NUMBER(0, 0xff));



constexpr uint8_t xObfuscationObfuscateUint8(const uint8_t buffer, const uint32_t index)
{
	return (uint8_t) (buffer ^ (X_OBFUSCATION_KEY + index + (X_OBFUSCATION_KEY % (index > 0 ? index : X_OBFUSCATION_KEY_MODULO))));
}



constexpr uint16_t xObfuscationObfuscateUint16(const uint16_t buffer, const uint32_t index)
{
	return MAKEWORD(xObfuscationObfuscateUint8(LOBYTE(buffer), index), xObfuscationObfuscateUint8(HIBYTE(buffer), index));
}



template <typename _Type> constexpr _Type xObfuscationObfuscateBuffer(_Type buffer, const uint32_t index)
{
	return (sizeof(_Type) == sizeof(uint8_t)) ? (_Type) xObfuscationObfuscateUint8((uint8_t) buffer, index) : (_Type) xObfuscationObfuscateUint16((uint16_t) buffer, index);
}



template <typename _Type, typename xObfuscationIndexList> class xObfuscationObfuscatedBuffer;

template <typename _Type, uint32_t... index> class xObfuscationObfuscatedBuffer<_Type, xObfuscationIndexList<index...> >
{
private:
	_Type value[sizeof...(index) + 1];

public:
	constexpr xObfuscationObfuscatedBuffer(const _Type* const buffer) : value {xObfuscationObfuscateBuffer(buffer[index], index)...} 
	{
	}

	const _Type* Decrypt()
	{
		for (uint32_t i = 0; i < sizeof...(index); i++)
		{
			value[i] = xObfuscationObfuscateBuffer(value[i], i);
		}

		value[sizeof...(index)] = '\0';

		return value;
	}

	const _Type* Get()
	{
		return value;
	}
};

#define X_OBFUSCATED_STRING_A(__String) (xObfuscationObfuscatedBuffer<char, xObfuscationConstructIndexList<sizeof(__String) - 1>::Result>(__String).Decrypt())

#define X_OBFUSCATED_STRING_W(__String) (xObfuscationObfuscatedBuffer<wchar_t, xObfuscationConstructIndexList<sizeof(__String) - 1>::Result>(__String).Decrypt())



template<typename _Function> class xObfuscationObfuscatedAddress
{
public:
	xObfuscationObfuscatedAddress() : m_callee(0), m_offset(0)
	{
	}

	constexpr xObfuscationObfuscatedAddress(_Function f, const uint32_t offset) : m_callee{(intptr_t) f + (offset % 2 == 0 ? (intptr_t) offset : (intptr_t) (offset * -1))}, m_offset{(offset % 2 == 0 ? offset : (offset * -1))}
	{
	}

	constexpr _Function Callee() const
	{
		return reinterpret_cast<_Function>(m_callee - m_offset);
	}

private:
	intptr_t m_callee;
	uint32_t m_offset;
};

template<typename _Function> constexpr xObfuscationObfuscatedAddress<_Function> xObfuscationCreateObfuscatedAddress(_Function f, const uint32_t offset) {return xObfuscationObfuscatedAddress<_Function>(f, offset); }

#define X_OBFUSCATED_ADDRESS(__Address) xObfuscationCreateObfuscatedAddress(__Address, X_RANDOM_NUMBER(0x00ff, 0xffff))



typedef enum _xObfuscationEntropy
{
	xObfuscationEntropyDefault		= 0x01,
	xObfuscationEntropyReduce		= 0x02,
	xObfuscationEntropyReduceMore	= 0x03
} xObfuscationEntropy;

bool xObfuscationObfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* plain, const uint32_t plainSize, uint8_t** obfuscated, uint32_t* obfuscatedSize, const xObfuscationEntropy entropy);

bool xObfuscationDeobfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* obfuscated, const uint32_t obfuscatedSize, uint8_t** plain, uint32_t* plainSize, const xObfuscationEntropy entropy);

bool xObfuscationObfuscateXor(const uint8_t key, const uint8_t* plain, const uint32_t plainSize, uint8_t** obfuscated);

bool xObfuscationDeobfuscateXor(const uint8_t key, const uint8_t* obfuscated, const uint32_t obfuscatedSize, uint8_t** plain);
