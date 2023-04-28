/**********************************************************************************************************************
 @file:         weatherStation.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Provides changing weather status
 **********************************************************************************************************************/

#include "weatherStation.h"

#include "weatherParameter.h"
#include "utilities.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace Weather
{
WeatherParameter *param[WEATHER_ID_TOTAL];

/**********************************************************************************************************************
 @brief:    Initializes weather station data.
 **********************************************************************************************************************/
void Init(void);

void Init(void)
{
    param[WEATHER_ID_OUTSIDE_TEMPERATURE] = new WeatherParameter(WEATHER_ID_OUTSIDE_TEMPERATURE, 33.3, 15.5, 95.0, 0.4);
    param[WEATHER_ID_OUTSIDE_HUMIDITY] = new WeatherParameter(WEATHER_ID_OUTSIDE_HUMIDITY, 25, 20, 99, 1);
    param[WEATHER_ID_PRESSURE] = new WeatherParameter(WEATHER_ID_PRESSURE, 30.0, 12.0, 109.0, 2.0);
    param[WEATHER_ID_DEW_POINT] = new WeatherParameter(WEATHER_ID_DEW_POINT, 45.0, 42.0, 62.3, 0.3);
    param[WEATHER_ID_WIND_SPEED] = new WeatherParameter(WEATHER_ID_WIND_SPEED, 0.0, 0.0, 25.0, 1.0);
    param[WEATHER_ID_WIND_DIRECTION] = new WeatherParameter(WEATHER_ID_WIND_DIRECTION, 0.0, 0.0, 359.0, 1.0);
};

void Task()
{
    Init();

    while (1)
    {
        for (int i=WEATHER_ID_START; i<WEATHER_ID_TOTAL; i++)
        {
            param[i]->ApplyStep();
        }
        // delay for next update
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }   // task loop
}

void paramStr(weather_ID_t id, char *str, size_t length)
{
    if (id < WEATHER_ID_TOTAL)
    {
        param[id]->CurrentValueStr(str, length);
    }
}

const char *WindDirectionStr(weather_ID_t id)
{
    const char *pDirectionStr = NULL;
    const char *DirectionStr[] =
    {
        "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
        "S", "SSW","SW", "WSW", "W", "WNW", "NW", "NNW", "N"
    };

    WeatherParameter *pDirection = param[WEATHER_ID_WIND_DIRECTION];
    if ( (pDirection->current >= 0.0) && (pDirection->current < 360.0) )
    {
        const int numSectors = sizeof(DirectionStr)/sizeof(char *);
        /* Determine what directional sector our compass reading is in. 
         * Subtract 1/2 sector width from compass reading to center the "0" reading on north;
         */
        int sectorWidth = 360 / numSectors;
        int DirectionSector = pDirection->current / sectorWidth;

        pDirectionStr = DirectionStr[DirectionSector];

    }
    return pDirectionStr;
}

}   // namespace
