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

typedef enum
{
    WEATHER_ID_START = 0,
    WEATHER_ID_OUTSIDE_TEMPERATURE = WEATHER_ID_START,
    WEATHER_ID_OUTSIDE_HUMIDITY,
    WEATHER_ID_TOTAL
} weather_ID_t;

void *Parameter(weather_ID_t weather_ID, void *Parameter);

DataFormat_t paramFormat(weather_ID_t id);
void paramValue(weather_ID_t id, void *value);

/**********************************************************************************************************************
 @brief:    Task which runs in it's own thread to update simulated weather station data.
 **********************************************************************************************************************/
void Task(void);

}   // namespace
#endif		// Prevent multiple includes
