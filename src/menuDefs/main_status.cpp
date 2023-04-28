/**********************************************************************************************************************
 @file:         main_status.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus used in the system.
 *********************************************************************************************************************/
#include "main_status.h"

#include "menus.h"
#include "HAL_Display.h"
#include "utilities.h"
#include "weatherStation.h"

/** Define menus \
 */
#include "HAL_Display.h"
#include "utilities.h"

using namespace Menu;

const items_t menu_main_status_items[] = {
    // Title
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 0,
        .columnPercent = 50,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_TITLE_FONT),
        .enter = NULL,
        .staticLabel = {.label = "Weather Station", .align = Display::FIELD_ALIGN_CENTER},
    },

    // Outside temperature
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "Out Temp:", .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 1,
        .columnPercent = 75,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {.id = WEATHER_ID_OUTSIDE_TEMPERATURE, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_GLYPH,
        .rowNum = 1,
        .columnPercent = 80,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .glyph = {.id = Display::GLYPH_DEGREE, .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 85,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "F", .align = Display::FIELD_ALIGN_LEFT},
    },

    // Outside humidity
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "Out Humidity:", .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 2,
        .columnPercent = 75,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {.id = WEATHER_ID_OUTSIDE_HUMIDITY, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 80,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "%", .align = Display::FIELD_ALIGN_LEFT},
    },

    // Barometric Pressure
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 3,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "Baro Press:", .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 3,
        .columnPercent = 75,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {.id = WEATHER_ID_PRESSURE, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 3,
        .columnPercent = 80,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "inHg", .align = Display::FIELD_ALIGN_LEFT},
    },

    // Dew Point
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 4,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "Dew Point:", .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 4,
        .columnPercent = 75,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {.id = WEATHER_ID_DEW_POINT, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_GLYPH,
        .rowNum = 4,
        .columnPercent = 80,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .glyph = {.id = Display::GLYPH_DEGREE, .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 4,
        .columnPercent = 85,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "F", .align = Display::FIELD_ALIGN_LEFT},
    },

    // Wind Speed, direction
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 5,
        .columnPercent = 0,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "Wind:", .align = Display::FIELD_ALIGN_LEFT},
    },
    {
        .type = Menu::TYPE_FUNCT_STR,
        .rowNum = 5,
        .columnPercent = 60,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .funcString = {.func = Weather::WindDirectionStr, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_PARAM_STR,
        .rowNum = 5,
        .columnPercent = 75,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .paramString = {.id = WEATHER_ID_WIND_SPEED, .align = Display::FIELD_ALIGN_RIGHT},
    },
    {
        .type = Menu::TYPE_STATIC_LABEL,
        .rowNum = 5,
        .columnPercent = 80,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .enter = NULL,
        .staticLabel = {.label = "mph", .align = Display::FIELD_ALIGN_LEFT},
    },
};

const menu_t menu_main_status = {
    .title = "Main Menu",
    .numItems = sizeof(menu_main_status_items) / sizeof(items_t),
    .items = &menu_main_status_items[0],
};
