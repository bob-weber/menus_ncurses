/**********************************************************************************************************************
 @file:         main.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        main function, which inits the display, parses defined menus and dsiplays them, and
                handles key presses.
 **********************************************************************************************************************/
#include "HAL_Display.h"
#include "keypad.h"
#include "menus.h"
#include "utilities.h"
#include "weatherStation.h"

#include <ncurses.h>
#include <stddef.h>
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#define MAX_DISPLAY_STR_LENGTH      20

extern const Menu::menu_t MainMenu;
//test
using namespace std;

/* Prototypes
 */

int main(void)
{
    // Launch a separate thread to manage weather station
    thread weather_thread(Weather::Task);

	void *pDisplay = NULL;
	initscr();			/* Start curses mode 		  */
	cbreak();				// process each key press w/o waiting for enter
	noecho();
	start_color();
    Key::Init();

	// Advance the cursos down a few lines so our menu window doesn't get overwritten.
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");

	//printw("first");	// added for relative positioning
	refresh();				//  need to draw the root window
										//  without this, apparently the children never draw
	pDisplay = Display::Init();
	if (pDisplay != NULL)
	{
        const Menu::menu_t *pMenu = &MainMenu;
        unsigned int selectedItem = 0;
        char displayStr[MAX_DISPLAY_STR_LENGTH];

        while (pMenu != NULL)
        {
            if (pMenu->title != NULL)
            {
                Display::Clear();
                Display::WriteString(0, 50, Display::FIELD_ALIGN_CENTER, pMenu->title,
                    BITMASK_FROM_VAL(Display::TEXT_ATTR_TITLE_FONT));
            }

            unsigned int totalItems = pMenu->numItems;    //(pMenu->item)/sizeof(item_t);
            for (unsigned int i=0; i<totalItems; i++)
            {
                const Menu::items_t *pItem = &(pMenu->items[i]);
                if (pItem != NULL)
                {
                    uint16_t itemAtrributes = pItem->attributes;
                    if ( (pMenu->type == Menu::MENU_TYPE_SELECTOR) &&
                        (i==selectedItem) )
                    {
                        itemAtrributes |= BITMASK_FROM_VAL(Display::TEXT_ATTR_INVERT);
                    }

                    switch (pItem->type)
                    {
                        case Menu::TYPE_STATIC_LABEL:
                            Display::WriteString(pItem->rowNum, pItem->columnPercent,
                                pItem->staticLabel.align,
                                pItem->staticLabel.label, itemAtrributes);
                            break;
                        
                        case Menu::TYPE_PARAM_STR:
                        {
                            // Define the variables we might use to save our paramter value.
                            uint32_t unsignedValue;
                            int32_t signedValue;
                            float floatValue;
            
                            DataFormat_t format = Weather::paramFormat(pItem->paramString.id);
                            if ((format == DATA_FORMAT_CHAR)   || (format == DATA_FORMAT_UINT8) ||
                                (format == DATA_FORMAT_UINT16) || (format == DATA_FORMAT_UINT32))
                            {
                                Weather::paramValue(pItem->paramString.id, (void *)&unsignedValue);
                                Menu::ParamToString(format, (void *)&unsignedValue, displayStr, MAX_DISPLAY_STR_LENGTH);
                            }
                            else if ((format == DATA_FORMAT_INT8) || (format == DATA_FORMAT_INT16) ||
                                     (format == DATA_FORMAT_INT32))
                            {
                                Weather::paramValue(pItem->paramString.id, (void *)&signedValue);
                                Menu::ParamToString(format, (void *)&signedValue, displayStr, MAX_DISPLAY_STR_LENGTH);
                            }
                            else if (format == DATA_FORMAT_FLOAT)
                            {
                                Weather::paramValue(pItem->paramString.id, (void *)&floatValue);
                                Menu::ParamToString(format, (void *)&floatValue, displayStr, MAX_DISPLAY_STR_LENGTH);
                            }
                            Display::WriteString(pItem->rowNum, pItem->columnPercent,
                                pItem->paramString.align,
                                displayStr, itemAtrributes);
                            break;
                        }

                        case Menu::TYPE_GLYPH:
                            displayStr[0] = pItem->glyph.id;
                            SetBit(&itemAtrributes, Display::TEXT_ATTR_GLYPH);
                            Display::WriteString(pItem->rowNum, pItem->columnPercent,
                                pItem->glyph.align,
                                displayStr, itemAtrributes);
                            break;

                        default:
                            break;
                    }
                }
            }
            
            Key::Keypress_t keypress = Key::Press();
            switch(keypress)
            {
                case Key::KEYPRESS_DOWN:
                    if (pMenu->type == Menu::MENU_TYPE_SELECTOR)
                    {
                        selectedItem = INCREMENT_WITH_ROLLOVER(selectedItem, totalItems-1);
                    }
                    break;
                    
                case Key::KEYPRESS_UP:
                    if (pMenu->type == Menu::MENU_TYPE_SELECTOR)
                    {
                        selectedItem = DECREMENT_WITH_ROLLOVER(selectedItem, totalItems-1);
                    }
                    break;
                    
                case Key::KEYPRESS_ENTER:
                    if (pMenu->type == Menu::MENU_TYPE_SELECTOR)
                    {
                        if (pMenu->items[selectedItem].enter != NULL)
                        {
                            // Use 2-step casting to work around invalid conversion error.
                            void *pEnter = (void *)pMenu->items[selectedItem].enter;
                            if (pEnter != NULL)
                            {   // Push the current menu and switch to the new one.
                                Menu::Push(pMenu);
                                pMenu = (const Menu::menu_t *)pEnter;
                                selectedItem = 0;
                            }
                        }
                    }
                    break;

                case Key::KEYPRESS_BACK:
                    if (pMenu->type == Menu::MENU_TYPE_SELECTOR)
                    {   // Pop up a menu
                        const Menu::menu_t *pNewMenu = Menu::Pop();
                        if (pNewMenu != NULL)
                        {
                            pMenu = pNewMenu;
                        }
                    }
                    break;

                case Key::KEYPRESS_QUIT:
                    // User wants to quit. Clear our dipslayed menu.
                    pMenu = NULL;
                    break;
                    
                default:    // ignore
                    break;
                    
            }            
            usleep(100E3);
        }
    }
    
	Display::End(pDisplay);
	endwin();
    weather_thread.detach();
  
	return EXIT_SUCCESS;
}

        #if 0
		Display_WriteString(0, 50, FIELD_ALIGN_CENTER, "Title", BITMASK_FROM_VAL(TEXT_ATTR_TITLE_FONT));
		Display_WriteString(1, 50, FIELD_ALIGN_CENTER, "123456789012345678901234567890", TEXT_ATTR_NONE);
		Display_WriteString(2, 99, FIELD_ALIGN_RIGHT, "Invert", BITMASK_FROM_VAL(TEXT_ATTR_INVERT));
		uint8_t length = Display_WriteString(3, 30, FIELD_ALIGN_LEFT, "Temperature", TEXT_ATTR_NONE);
		//printf("length %d, 1\n", length);
		uint8_t start = 30+length;
		//printf("start %d, 1\n", start);
		length = Display_WriteString(3, start, FIELD_ALIGN_LEFT, "2", BITMASK_FROM_VAL(TEXT_ATTR_SUPERSCRIPT));
		start += length;
		//printf("start %d, 2\n", start);
		length = Display_WriteString(3, start, FIELD_ALIGN_LEFT, "m", BITMASK_FROM_VAL(TEXT_ATTR_SUBSCRIPT));
		start += length;
		//printf("start %d, 3\n", start);

		GlyphT Glyph = GLYPH_LEFT_ARROW;
		Display_WriteString(4, 10, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
		Glyph = GLYPH_RIGHT_ARROW;
		Display_WriteString(4, 20, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
		Glyph = GLYPH_UP_ARROW;
		Display_WriteString(4, 30, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
		Glyph = GLYPH_DOWN_ARROW;
		Display_WriteString(4, 40, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
		Glyph = GLYPH_DEGREE;
		Display_WriteString(4, 50, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
		Glyph = GLYPH_MICRO;
		Display_WriteString(4, 60, FIELD_ALIGN_LEFT, (const char *)&Glyph, BITMASK_FROM_VAL(TEXT_ATTR_GLYPH));
        #endif
