/**********************************************************************************************************************
 @file:         menus.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus used in the system.
 *********************************************************************************************************************/
#include "menu_defs.h"

#include "menus.h"
#include "HAL_Display.h"
#include "utilities.h"
#include "weatherStation.h"

/** Define menus \
 */
#include "HAL_Display.h"
#include "utilities.h"

using namespace Menu;

const items_t MainMenu_items[] =
{
    // Title
   {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 0,
        .columnPercent = 50,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_TITLE_FONT),
        .enter = NULL,
        .staticLabel = {
            .label = "Weather Station",
            .align = Display::FIELD_ALIGN_CENTER,
        },
    },

    // Outside temperature
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {
            .label = "Outside Temp:",
            .align = Display::FIELD_ALIGN_LEFT
        },
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 1,
        .columnPercent = 88,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {
            .id = Weather::WEATHER_ID_OUTSIDE_TEMPERATURE,
            .align = Display::FIELD_ALIGN_RIGHT
        },
    },
    {
        .type = Menu::TYPE_GLYPH,
        .rowNum = 1,
        .columnPercent = 90,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .glyph = {
            .id = Display::GLYPH_DEGREE,
            .align = Display::FIELD_ALIGN_LEFT
        },
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 95,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {
            .label = "F",
            .align = Display::FIELD_ALIGN_LEFT
        },
    },

    // Outside humidity
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {
            .label = "Outside Humidity:",
            .align = Display::FIELD_ALIGN_LEFT
        },
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 2,
        .columnPercent = 88,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {
            .id = Weather::WEATHER_ID_OUTSIDE_HUMIDITY,
            .align = Display::FIELD_ALIGN_RIGHT
        },
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 90,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {
            .label = "%",
            .align = Display::FIELD_ALIGN_LEFT
        },
    },
    
    // Submenu
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 3,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = (const void *)&Submenu2,
        .staticLabel = { .label = "Submenu 2" },
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 4,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = { .label = "Submenu 3" },
    },

};

const menu_t MainMenu =
{
    .title = "Main Menu",
    .type = MENU_TYPE_SELECTOR,
    .numItems = sizeof(MainMenu_items) / sizeof(items_t),
    .items = &MainMenu_items[0],
};

const items_t Submenu1_items[] =
{
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = { .label = "Submenu 1-1" },
    },
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = { .label = "Submenu 1-2" },
    },
};

const menu_t Submenu1 =
{
    .title = "Submenu 1",
    .type = MENU_TYPE_SELECTOR,
    .numItems = 2,
    .items = &Submenu1_items[0],
};

const items_t Submenu2_items[] =
{
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = { .label = "Submenu 2-1" },
    },
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = { .label = "Submenu 2-2" },
    },
};

const menu_t Submenu2 =
{
    .title = "Submenu 2",
    .type = MENU_TYPE_SELECTOR,
    .numItems = 2,
    .items = &Submenu2_items[0],
};
