/**********************************************************************************************************************
 @file:         menus.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus used in the system.
 **********************************************************************************************************************/
#include "menus.h"
#include "utilities.h"

#include <stddef.h>

using namespace Menu;

#define MENU_STACK_SIZE     12


static const menu_t *menuStack[MENU_STACK_SIZE];
static unsigned int nextAvailableStackEntry= 0;

bool Menu::Push(const menu_t *menu)
{
    bool Success = false;

    if (nextAvailableStackEntry < MENU_STACK_SIZE)
    {   // We have room
        menuStack[nextAvailableStackEntry] = menu;
        nextAvailableStackEntry++;
        Success = true;
    }
    // else, stack is full;

    return Success;
}

const menu_t *Menu::Pop(void)
{
    const menu_t *pMenu = NULL;

    if (nextAvailableStackEntry > 0)
    {
        nextAvailableStackEntry--;
        pMenu = menuStack[nextAvailableStackEntry];
    }
    // else, stack is empty;

    return pMenu;
}

void Menu::ParamToString(DataFormat_t format, void* param, char *paramString, int maxLength)
{
    switch (format)
    {
        case DATA_FORMAT_CHAR:
            snprintf(paramString, maxLength, "%c", *((char *)param));
            break;

        case DATA_FORMAT_UINT8:
            snprintf(paramString, maxLength, "%u", *((uint8_t *)param));
            break;

        case DATA_FORMAT_UINT16:
            snprintf(paramString, maxLength, "%u", *((uint16_t *)param));
            break;

        case DATA_FORMAT_UINT32:
            snprintf(paramString, maxLength, "%u", *((uint32_t *)param));
            break;

        case DATA_FORMAT_INT8:
            snprintf(paramString, maxLength, "%d", *((int8_t *)param));
            break;

        case DATA_FORMAT_INT16:
            snprintf(paramString, maxLength, "%d", *((int16_t *)param));
            break;

        case DATA_FORMAT_INT32:
            snprintf(paramString, maxLength, "%d", *((int32_t *)param));
            break;

        case DATA_FORMAT_FLOAT:
            snprintf(paramString, maxLength, "%.1f", *((float *)param));
            break;

        default:
            break;

    }
}

