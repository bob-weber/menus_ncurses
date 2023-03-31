/**********************************************************************************************************************
 @file:         keypad.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Handles keypad input.
 **********************************************************************************************************************/
#ifndef INC_KEYPAD_H
#define INC_KEYPAD_H

namespace Key {

// Valid key presses
typedef enum
{
    KEYPRESS_NONE = 0,
    KEYPRESS_LEFT,
    KEYPRESS_RIGHT,
    KEYPRESS_UP,
    KEYPRESS_DOWN,
    KEYPRESS_ENTER,
    KEYPRESS_BACK,
    KEYPRESS_QUIT
} Keypress_t;

/**********************************************************************************************************************
 @brief:    Initialize our keypad.
 **********************************************************************************************************************/
void Init(void);

/**********************************************************************************************************************
 @brief:    Write a string to the display
 
 @return:   A keypress if one occurred, or KEYPRESS_NONE.

 @note:     Because this function is not in its own task and uses an input function from ncurses, it's not able to
            time keypresses or do anything other than return if a keypress of interest occured.
 **********************************************************************************************************************/
Keypress_t Press(void);

}   // namespace
#endif		// Prevent multiple includes
