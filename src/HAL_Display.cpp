/**********************************************************************************************************************
 @file:         HAL_Display.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Provide access to the physical display via a generalized HAL.
 **********************************************************************************************************************/
#include "HAL_Display.h"
#include "utilities.h"

#include <string.h>

#include <ncurses.h>

// Define display parameters
namespace Display
{
	typedef struct
	{
		const unsigned int NUM_COLUMNS;
		const unsigned int NUM_ROWS;

		/* Our display width in chars is set to mimic the OLED.
		* However, our horizontal position is defined as a %, not as a character offset.
		* When calculating the character offset, we can get round-off errors that can result in characters
		* overlapping. Hence, we choose a width of 25 characters, which is close to our display width, but
		* evenly allows 4%/character.
		*/
		const unsigned int WIDTH_CHARS;

		// pointer to the window to which we'll write.
		WINDOW *pWindow;
	} OLED_Params_t;
	static OLED_Params_t OLED_Params = { 30, 5, 25, NULL };
};

void *Display::Init()
{
	void *pDisplay = NULL;
	// make display 2 characters larger in width and height. This is for the border.
	Display::OLED_Params.pWindow = newwin(Display::OLED_Params.NUM_ROWS + 2, Display::OLED_Params.WIDTH_CHARS + 2,
		0, Display::OLED_Params.NUM_COLUMNS);
	box(Display::OLED_Params.pWindow, 0, 0);
	wrefresh(Display::OLED_Params.pWindow);
	pDisplay = (void *)Display::OLED_Params.pWindow;
	return pDisplay;
}

void Display::End(void *pDisplay)
{
	delwin((WINDOW *)pDisplay);
}

void Display::Clear()
{
    wclear(Display::OLED_Params.pWindow);    
}

uint8_t Display::WriteString(uint8_t Row, uint8_t Column_pos_percent, Alignment_t Alignment,
	const char *Str, uint8_t Attribute_bm)
{
	uint8_t TextWidth_percent = 0;

    if ((Row < Display::OLED_Params.WIDTH_CHARS) &&
	    (Column_pos_percent < 100) &&
		(Str != NULL))
    {
		// use ncurses library
        char *DisplayStr = (char *)Str;
		if (Display::OLED_Params.pWindow != NULL)
		{
			int16_t StartingHorizontalPosition_chars = 0;
			uint16_t TextWidth_chars = 0;

			if (IsBitSet(Attribute_bm, Display::TEXT_ATTR_GLYPH))
			{
                // A glyph is a single character
				TextWidth_chars = 1;
			}
			else
			{	// Not a glyph; a string
				TextWidth_chars = strlen(Str);
				if (IsBitSet(Attribute_bm, Display::TEXT_ATTR_TITLE_FONT))
				{
					wattron(Display::OLED_Params.pWindow, A_BOLD);
				}
				// else, list font. Do not bold.
			}

			// Calculate the horizontal position character, rounding by 1/2 a character width.
			int16_t StartingHorizontalPosition =
				(int16_t)( ( ((float)Column_pos_percent/100.0) *
				            Display::OLED_Params.WIDTH_CHARS) + 0.5);
			//printf("Startchar %d\n", StartingHorizontalPosition);
			switch (Alignment)
			{
				case Display::FIELD_ALIGN_LEFT:
					StartingHorizontalPosition_chars = StartingHorizontalPosition;
					break;

				case Display::FIELD_ALIGN_CENTER:
					StartingHorizontalPosition_chars = StartingHorizontalPosition - (TextWidth_chars / 2);
					break;

				default:
					// Right justify
					StartingHorizontalPosition_chars = StartingHorizontalPosition - TextWidth_chars;
					break;
			}
			//printf("W %d, LP %d\n", TextWidth_chars, StartingHorizontalPosition_chars);

			if (StartingHorizontalPosition_chars < 0)
			{	// Characters to the left of the edge of our display.
				// We'll chop off the characters to the left of the display, and adjust the width accordingly.
				uint16_t NumCharsToChop = -StartingHorizontalPosition_chars;
				DisplayStr = (char *)(&Str[NumCharsToChop]);
				//printf("Chop %d\n", NumCharsToChop);
				TextWidth_chars -= NumCharsToChop;
				StartingHorizontalPosition_chars = 0;
			}
			unsigned int HorizontalPosition_RightChar = StartingHorizontalPosition_chars + TextWidth_chars;
			if (HorizontalPosition_RightChar > Display::OLED_Params.WIDTH_CHARS)
			{	// Characters go beyond the right side of the display.
				// Chop off the extra characters, and adjust the text width.
				unsigned int NumCharsToChop = HorizontalPosition_RightChar - Display::OLED_Params.WIDTH_CHARS;
				TextWidth_chars -= NumCharsToChop;
			}

			// Calculate text width as a percentage of the display.
			TextWidth_percent = (100.0 / (float)Display::OLED_Params.WIDTH_CHARS) * TextWidth_chars;

			if (IsBitSet(Attribute_bm, Display::TEXT_ATTR_INVERT))
			{
				wattron(Display::OLED_Params.pWindow, A_REVERSE);
			}
			if (IsBitSet(Attribute_bm, TEXT_ATTR_SUPERSCRIPT) || IsBitSet(Attribute_bm,
				Display::TEXT_ATTR_SUBSCRIPT))
			{
				wattron(Display::OLED_Params.pWindow, A_ITALIC);
			}

			//printf("H %d\n", StartingHorizontalPosition_chars);TEXT_ATTR_GLYPH
			wmove(Display::OLED_Params.pWindow, Row + 1, StartingHorizontalPosition_chars + 1);
			if (IsBitSet(Attribute_bm, Display::TEXT_ATTR_GLYPH))
			{
				Glyph_t Glyph = (Glyph_t)(*Str);
				switch (Glyph)
				{
					case GLYPH_LEFT_ARROW:
						waddch(Display::OLED_Params.pWindow, ACS_LARROW);
						break;

					case GLYPH_RIGHT_ARROW:
						waddch(Display::OLED_Params.pWindow, ACS_RARROW);
						break;

					case GLYPH_UP_ARROW:
						waddch(Display::OLED_Params.pWindow, ACS_UARROW);
						break;

					case GLYPH_DOWN_ARROW:
						waddch(Display::OLED_Params.pWindow, ACS_DARROW);
						break;

					case GLYPH_UP_DOWN_ARROW:
						waddch(Display::OLED_Params.pWindow, ACS_DIAMOND);
						break;

					case GLYPH_DEGREE:
						waddch(Display::OLED_Params.pWindow, ACS_DEGREE);
						break;

					case GLYPH_MICRO:
						waddch(Display::OLED_Params.pWindow, 'u');
						break;

					default:
						// Not handled.
						break;
				}
				// Write a glyph
			}
			else
			{	// String
				waddnstr(Display::OLED_Params.pWindow, DisplayStr, TextWidth_chars);
			}
			wrefresh(Display::OLED_Params.pWindow);
			wattrset(Display::OLED_Params.pWindow, A_NORMAL);  // clear special attributes
			//wattroff(Display::OLED_Params.pWindow, A_REVERSE | A_BLINK);
			curs_set(0);
		}
		// else, we don't have a valid display yet
	}
	// else invalid parameters
	
	return TextWidth_percent;
}
