/**********************************************************************************************************************
 @file:         weatherStation.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Provides changing weather status
 **********************************************************************************************************************/

#include "weatherStation.h"

#include "utilities.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace Weather
{
// A structure which contains the definitions for each weather station paramter.
typedef struct
{
    DataFormat_t format;
    void *current;
    void *max;
    void *min;
    void *step;
    bool increasing;
} Parameter_t;

// Declare and initialize settings for weather station parameters.
static Parameter_t WeatherParam[WEATHER_ID_TOTAL];
float OutTemp_current=33.3, OutTemp_max=95.0, OutTemp_min=15.5, OutTemp_step=0.4;
uint8_t OutHumidity_current=25, OutHumidity_max=99, OutHumidity_min=20, OutHumidity_step=1;

/**********************************************************************************************************************
 @brief:    Initializes weather station data.
 **********************************************************************************************************************/
void Init(void);

DataFormat_t paramFormat(weather_ID_t id)
{
    DataFormat_t format = DATA_FORMAT_NONE;
    if (id < WEATHER_ID_TOTAL)
    {
        format = WeatherParam[id].format;
    }
    return format;
}

void paramValue(weather_ID_t id, void *value)
{
    if (id < WEATHER_ID_TOTAL)
    {
        switch(WeatherParam[id].format)
        {
            case DATA_FORMAT_CHAR:
                *((char *)value) = *((char *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_UINT8:
                *((uint8_t *)value) = *((uint8_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_INT8:
                *((int8_t *)value) = *((int8_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_UINT16:
                *((uint16_t *)value) = *((uint16_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_INT16:
                *((int16_t *)value) = *((int16_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_UINT32:
                *((uint32_t *)value) = *((uint32_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_INT32:
                *((int32_t *)value) = *((int32_t *)WeatherParam[id].current);
                break;

            case DATA_FORMAT_FLOAT:
                *((float *)value) = *((float *)WeatherParam[id].current);
                break;

            default:
                break;
        }
    }
}

void Init(void)
{
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].current = &OutTemp_current;
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].max = &OutTemp_max;
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].min = &OutTemp_min;
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].step = &OutTemp_step;
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].format = DATA_FORMAT_FLOAT;
    WeatherParam[WEATHER_ID_OUTSIDE_TEMPERATURE].increasing = true;

    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].current = &OutHumidity_current;
    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].max = &OutHumidity_max;
    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].min = &OutHumidity_min;
    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].step = &OutHumidity_step;
    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].format = DATA_FORMAT_UINT8;
    WeatherParam[WEATHER_ID_OUTSIDE_HUMIDITY].increasing = true;
}

void Task()
{
    Init();

    while (1)
    {
        for (int i=WEATHER_ID_START; i<WEATHER_ID_TOTAL; i++)
        {
            Parameter_t *pParam = &WeatherParam[i];
            switch (pParam->format)
            {
                case DATA_FORMAT_UINT8:
                {
                    uint8_t *pCurrent = (uint8_t *)pParam->current;
                    uint8_t *pStep = (uint8_t *)pParam->step;
                    uint8_t *pMax = (uint8_t *)pParam->max;
                    uint8_t *pMin = (uint8_t *)pParam->min;
                    if (pParam->increasing)
                    {
                        *pCurrent += *pStep;
                        if ( *pCurrent > *pMax ) 
                        {
                            *pCurrent = *pMax;
                            pParam->increasing = false;
                        }
                    }
                    else
                    {
                        *pCurrent -= *pStep;
                        if ( *pCurrent < *pMin ) 
                        {
                            *pCurrent = *pMin;
                            pParam->increasing = true;
                        }

                    }
                     break;
               }

                case DATA_FORMAT_FLOAT:
                {
                    float *pCurrent = (float *)pParam->current;
                    float *pStep = (float *)pParam->step;
                    float *pMax = (float *)pParam->max;
                    float *pMin = (float *)pParam->min;
                    if (pParam->increasing)
                    {
                        *pCurrent += *pStep;
                        if ( *pCurrent > *pMax ) 
                        {
                            *pCurrent = *pMax;
                            pParam->increasing = false;
                        }
                    }
                    else
                    {
                        *pCurrent -= *pStep;
                        if ( *pCurrent < *pMin ) 
                        {
                            *pCurrent = *pMin;
                            pParam->increasing = true;
                        }

                    }
                     break;
                }

                default:
                    break;
            }
        }

        // delay for next update
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }   // task loop
}

}   // namespace