/**********************************************************************************************************************
 @file:         weatherStation.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        
 **********************************************************************************************************************/
#ifndef INC_WEATHER_STATION_H
#define INC_WEATHER_STATION_H

#include "utilities.h"

namespace Weather {

// Identifiers for the weather station paramters
typedef enum
{
    WEATHER_ID_START = 0,
    WEATHER_ID_OUTSIDE_TEMPERATURE = WEATHER_ID_START,
    WEATHER_ID_OUTSIDE_HUMIDITY,
    WEATHER_ID_TOTAL
} weather_ID_t;

/**********************************************************************************************************************
 * @brief:  Returns the data format for the specified weather station parameter.
 *
 * @param id:       The weather station parameter
 **********************************************************************************************************************/
DataFormat_t paramFormat(weather_ID_t id);

/**********************************************************************************************************************
 * @brief:  Updates "value" with the current value for the specified parameter.
 * 
 * @param id:       The weather station parameter
 * @param value:    Updated with the current value.
 **********************************************************************************************************************/
void paramValue(weather_ID_t id, void *value);

/**********************************************************************************************************************
 @brief:    Task which runs in it's own thread to update simulated weather station data.
 **********************************************************************************************************************/
void Task(void);

}   // namespace
#endif		// Prevent multiple includes
