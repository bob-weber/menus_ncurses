/**********************************************************************************************************************
 @file:         menus.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus used in the system.
 *********************************************************************************************************************/
#include "menu_defs.h"

#include "menus.h"
#include "menuDefs/main_status.h"
#include "HAL_Display.h"
#include "utilities.h"
#include "weatherStation.h"

/** Define menus \
 */
#include "HAL_Display.h"
#include "utilities.h"

using namespace Menu;

const items_t Submenu1_items[] = {
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = {.label = "Submenu 1-1"},
    },
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = {.label = "Submenu 1-2"},
    },
};

const menu_t Submenu1 = {
    .title = "Submenu 1",
    .numItems = 2,
    .items = &Submenu1_items[0],
};

const items_t Submenu2_items[] = {
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 1,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = {.label = "Submenu 2-1"},
    },
    {
        .type = TYPE_STATIC_LABEL,
        .rowNum = 2,
        .columnPercent = 1,
        .attributes = BITMASK_FROM_VAL(Display::TEXT_ATTR_NONE),
        .staticLabel = {.label = "Submenu 2-2"},
    },
};

const menu_t Submenu2 = {
    .title = "Submenu 2",
    .numItems = 2,
    .items = &Submenu2_items[0],
};
