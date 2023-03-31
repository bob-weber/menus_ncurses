/**********************************************************************************************************************
 @file:         menus.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus field types, and menus, used in the system.
 **********************************************************************************************************************/
#ifndef INC_MENUS_H
#define INC_MENUS_H

#include "HAL_Display.h"
#include "utilities.h"
#include "weatherStation.h"

#include <stdint.h>

namespace Menu {

// Possible button press actions
typedef enum
{
    ACTION_NONE = 0,
    ACTION_SELECT_NEXT_FIELD,
    ACTION_SELECT_PREVIOUS_FIELD,
    ACTION_POP_UP
} buttonAction;

// Purpose of the menu. Chanegs menu behaviour.
typedef enum
{
    MENU_TYPE_SELECTOR
} menuType_t;

// Types of menu field items
typedef enum
{
    TYPE_STATIC_LABEL,
    TYPE_DYNAMIC_LABEL,
    TYPE_PARAM_STR,
    TYPE_GLYPH,
} menuItem_t;

// Fields needed for static labels.
typedef struct
{
    const char *label;
    const Display::Alignment_t align;
 } staticLabel_t;

typedef struct
{
    const Weather::weather_ID_t id;
    const Display::Alignment_t align;
} paramString_t;

typedef struct
{
    const Display::Glyph_t id;
    const Display::Alignment_t align;
} glyph_t;

typedef struct
{
    char *GetvariableFunc(uint16_t ID);
} GetVarFunc_t;

// menu item parameters.
typedef struct
{
    const menuItem_t type;
    const uint8_t rowNum;
    const uint8_t columnPercent;
    const uint16_t attributes;
    const void *enter;
    union
    {
        staticLabel_t staticLabel;
        paramString_t paramString;
        glyph_t glyph;
       //dynamicLabel dynamicLabel;
    };
} items_t;

// Menu definitions

typedef struct
{
    const char *title;
    const menuType_t type;
    const unsigned int numItems;
    const items_t *items;
} menu_t;

bool Push(const menu_t *menu);
const menu_t *Pop(void);

void ParamToString(DataFormat_t format, void* param, char *paramString, int maxLength);

};  // namespace

#endif