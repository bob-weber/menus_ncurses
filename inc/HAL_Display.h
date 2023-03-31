/**********************************************************************************************************************
 @file:         HAL_Display.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        DProvides an abstraction layer for writing to the display.
 **********************************************************************************************************************/
#ifndef INC_HAL_DISPLAY_H
#define INC_HAL_DISPLAY_H

#include <stdint.h>
#include <ncurses.h>

namespace Display
{

typedef enum
{
	DISPLAY_OK = 0,
	DISPLAY_COORDINATES_OUT_OF_RANGE,
	DISPLAY_STRING_TRUNCATED,
} DisplayError_t;

/* Define how we want to align the characters.
 * Left: start printing at the X position, continuing to the right.
 * Right: Start printing left of the X position, with the text ending at X.
 * Center: Center on the display. Note that we could center within a range if we add a width field, but no neef for this yet.
 */
typedef enum
{
	FIELD_ALIGN_LEFT,
	FIELD_ALIGN_RIGHT,
	FIELD_ALIGN_CENTER
} Alignment_t;

typedef enum
{
	GLYPH_LEFT_ARROW = 0,
	GLYPH_RIGHT_ARROW,
	GLYPH_UP_ARROW,
	GLYPH_DOWN_ARROW,
	GLYPH_UP_DOWN_ARROW,
	GLYPH_DEGREE,
	GLYPH_MICRO,
	GLYPH_TOTAL
} Glyph_t;

// A list of attributes to apply to text.
typedef enum
{
    TEXT_ATTR_NONE = 0,
	TEXT_ATTR_INVERT,
	TEXT_ATTR_SUPERSCRIPT,
	TEXT_ATTR_SUBSCRIPT,
	TEXT_ATTR_TITLE_FONT,
	TEXT_ATTR_GLYPH,
} TextAttribute_t;

/**********************************************************************************************************************
 * @brief:		Initializes the display.
 **********************************************************************************************************************/
void *Init(void);

/**********************************************************************************************************************
 * @brief:		Closes the display.
 * 
 * @param pDisplay:		Pointer to the display to close.
 **********************************************************************************************************************/
void End(void *pDisplay);

/**********************************************************************************************************************
 * @brief:		Clears the display.
 **********************************************************************************************************************/
void Clear(void);

/**********************************************************************************************************************
 * @brief:		Manages writes to the display.
 * 
 * @param Row:					Display row we're writing to.
 * @param Column_pos_percent:	Horizontal position, as a percentage (0 to 99%)
 * @param Alignment				Text alighment on the columnn position, left, right or center.
 * @param Str					Text to write.
 * @param Attribute_bm:			Bitmask indicating attributes.
 *
 * @return:		The width of the written string, as a percentage of the display width.
 * 				This allows the caller to know how to concatenate strings.
 * 				Note that this is the width of the string only; it does not include the starting x position of the string.
 * 				0 if no string was written.
 *
 * @note:		None
 **********************************************************************************************************************/
uint8_t WriteString(uint8_t Row, uint8_t Column_pos_percent, Alignment_t Alignment, const char *Str,
		uint8_t Attribute_bm);

}	// namespace
#endif		// Prevent multiple includes
