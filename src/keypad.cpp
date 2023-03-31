/**********************************************************************************************************************
 @file:         keypad.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        API for using the keypad.
 **********************************************************************************************************************/

#include "keypad.h"

#include <ncurses.h>

void Key::Init(void)
{
    keypad(stdscr, TRUE);
}

Key::Keypress_t Key::Press()
{
    Key::Keypress_t keypress = Key::KEYPRESS_NONE;
    timeout(100);
    int input = getch();
    if (input != 0)
    {
        switch (input)
        {
            case KEY_RIGHT:
                keypress = Key::KEYPRESS_RIGHT;
                break;
            
            case KEY_LEFT:
                keypress = Key::KEYPRESS_LEFT;
                break;
            
            case KEY_UP:
                keypress = Key::KEYPRESS_UP;
                break;
            
            case KEY_DOWN:
                keypress = Key::KEYPRESS_DOWN;
                break;
            
            case 10: //KEY_ENTER:
                keypress = Key::KEYPRESS_ENTER;
                break;
                
            case KEY_BACKSPACE:
                keypress = Key::KEYPRESS_BACK;
                break;
                
            case 'q':
                keypress = Key::KEYPRESS_QUIT;
                break;
                
            default:
                break;
        }
    }
    return keypress;
}
