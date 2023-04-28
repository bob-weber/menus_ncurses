/**********************************************************************************************************************
 @file:         weatherStation.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:
 **********************************************************************************************************************/
#ifndef INC_WEATHER_STATION_H
#define INC_WEATHER_STATION_H

#include "weatherParameter.h"
#include "utilities.h"

namespace Weather
{

  /**********************************************************************************************************************
   @brief:    Converts the specified ID's value to a string.
   @param:    id, the parameter to use.
   @param:    str, the detination to which we'll write the string.
   @param:    length, the maximum number of characters to write.
   @return:   Pointer to the string value, or NULL if the specified parameter is invalid.
   **********************************************************************************************************************/
  void paramStr(weather_ID_t id, char *str, size_t length);

  /**********************************************************************************************************************
   @brief:    Converts the specified ID's value to a direction.
              The input parameter is a 0 to 359 degree value. 0 is centered on North.
   @param:    id, the parameter to convert.
   @return:   Pointer to the string value, or NULL if the specified parameter is invalid.
   **********************************************************************************************************************/
  const char *WindDirectionStr(weather_ID_t id);

  /**********************************************************************************************************************
   @brief:    Task which runs in it's own thread to update simulated weather station data.
   **********************************************************************************************************************/
  void Task(void);

} // namespace
#endif // Prevent multiple includes
