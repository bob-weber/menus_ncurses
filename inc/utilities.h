#ifndef INC_UTLITIES_H
#define INC_UTLITIES_H

#include <stdint.h>

#define HIGH_BYTE_OF_WORD(x)		((uint8_t)((x >> 8) & 0x00FF))
#define LOW_BYTE_OF_WORD(x)			((uint8_t)(x & 0x00FF))
#define GET_BYTE(Value, Byte)		((uint8_t)((Value >> (8 * Byte)) & 0xFF))

#define BITMASK_FROM_VAL(x)									(1 << (x))
#define SetBit_L4(pTarget, BitOffset)				((*pTarget) |= BITMASK_FROM_VAL(BitOffset))
#define ClearBit_L4(pTarget, BitOffset)			((*pTarget) &= ~BITMASK_FROM_VAL(BitOffset))
#define ToggleBit_L4(pTarget, BitOffset)		((*pTarget) ^= BITMASK_FROM_VAL(BitOffset))
#define IsBitSet(Target, BitOffset)			((Target & BITMASK_FROM_VAL(BitOffset)) != 0)
#define IsBitClear_L4(Target, BitOffset)		((Target & BITMASK_FROM_VAL(BitOffset)) == 0)

// Increment a value up to a maximum amount, then roll back to 0.
#define INCREMENT_WITH_ROLLOVER(x, MAX)		((x >= MAX) ? 0 : x+1)
#define DECREMENT_WITH_ROLLOVER(x, MAX)		((x <= 0) ? MAX : x-1)

// A subtract, absolute macro
#define ABS_SUBTRACT(a, b)	(((a) >= (b)) ? ((a) - (b)) : ((b) - (a)))

// ABS macro
#define ABS(x)		((x < 0) ? (-x) : x)
#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif


// Defines a data format type
typedef enum
{
    DATA_FORMAT_NONE = 0,
    DATA_FORMAT_CHAR,
    DATA_FORMAT_UINT8,
    DATA_FORMAT_INT8,
    DATA_FORMAT_UINT16,
    DATA_FORMAT_INT16,
    DATA_FORMAT_UINT32,
    DATA_FORMAT_INT32,
    DATA_FORMAT_FLOAT
} DataFormat_t;

#endif
