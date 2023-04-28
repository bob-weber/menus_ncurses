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
#include "weatherParameter.h"
#include "weatherStation.h"

#include <stdint.h>

namespace Menu
{

  // Possible button press actions
  typedef enum
  {
    ACTION_NONE = 0,
    ACTION_SELECT_NEXT_FIELD,
    ACTION_SELECT_PREVIOUS_FIELD,
    ACTION_POP_UP
  } buttonAction;

  // Types of menu field items. These can be handled differently.
  typedef enum
  {
    TYPE_STATIC_LABEL,
    TYPE_DYNAMIC_LABEL,
    TYPE_PARAM_STR,
    TYPE_GLYPH,
    TYPE_FUNCT_STR,
  } menuItem_t;

  // Fields needed for different field item types.
  typedef struct
  {
    const char *label;
    const Display::Alignment_t align;
  } staticLabel_t;

  typedef struct
  {
    const weather_ID_t id;
    const Display::Alignment_t align;
  } paramString_t;

  typedef struct
  {
    const char *(*func)(weather_ID_t);
    const Display::Alignment_t align;
  } funcString_t;

  typedef struct
  {
    const Display::Glyph_t id;
    const Display::Alignment_t align;
  } glyph_t;

  typedef struct
  {
    char *GetvariableFunc(uint16_t ID);
  } GetVarFunc_t;

  /* menu item parameters.
   * This consists of common attribues, and some specific to the field type.
   */
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
      funcString_t funcString;
      // dynamicLabel dynamicLabel;
    };
  } items_t;

  /* Menu definition
   * Each menu consists of a few attributes, plus several field items.
   */
  typedef struct
  {
    const char *title;
    const unsigned int numItems;
    const items_t *items;
  } menu_t;

  /**********************************************************************************************************************
   * @brief:      Initializes the menuing code.
   *********************************Weather*************************************************************************************/
  void Init(void);

  const menu_t *GetCurrent(void);

  /**********************************************************************************************************************
   * @brief:      Pushes the current menu onto a stack.
   *
   * @param menu: The menu to push
   * @return:     true if successful. false if the stack is full.
   *********************************Weather*************************************************************************************/
  bool Push(const menu_t *menu);

  /**********************************************************************************************************************
   * @brief:      Pops a menu from the menu stack, so we can "pop up" back the way we came down into the menus.
   *
   * @return:     Pointer to the popped menu. Null if the stack is empty.
   **********************************************************************************************************************/
  const menu_t *Pop(void);

}; // namespace

#endif
