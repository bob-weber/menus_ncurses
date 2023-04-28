/**********************************************************************************************************************
 @file:         menus.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Defines menus used in the system.
 **********************************************************************************************************************/
#include "menus.h"
#include "menuDefs/main_status.h"

#include "utilities.h"

#include <stddef.h>

using namespace Menu;

#define MENU_STACK_SIZE 12

// Menu stack declaration
static const menu_t *menuStack[MENU_STACK_SIZE];
static unsigned int nextAvailableStackEntry = 0;
static const menu_t *pCurrentMenu = NULL;

void Menu::Init()
{
  pCurrentMenu = &menu_main_status;
}

const menu_t *Menu::GetCurrent()
{
  return pCurrentMenu;
}

bool Menu::Push(const menu_t *menu)
{
  bool Success = false;

  if (nextAvailableStackEntry < MENU_STACK_SIZE)
  { // We have room
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
