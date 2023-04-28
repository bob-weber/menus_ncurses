/**********************************************************************************************************************
 @file:         weatherParameter.h
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        
 **********************************************************************************************************************/
#ifndef INC_WEATHER_PARAMETER_H
#define INC_WEATHER_PARAMETER_H

#include "utilities.h"

#include <stddef.h>

// Identifiers for the weather station paramters
 typedef enum
{
    WEATHER_ID_START = 0,
    WEATHER_ID_OUTSIDE_TEMPERATURE = WEATHER_ID_START,
    WEATHER_ID_OUTSIDE_HUMIDITY,
    WEATHER_ID_PRESSURE,
    WEATHER_ID_DEW_POINT,
    WEATHER_ID_WIND_SPEED,
    WEATHER_ID_WIND_DIRECTION,
    WEATHER_ID_TOTAL
} weather_ID_t;

class WeatherParameter
{
public:
    // Parameter settings
    weather_ID_t ID;
    DataFormat_t format;
    float current, min, max, step;
    bool increasing;

    /*****************************************************************************************************************
    @brief:     Constructor for a weathe rparameter
    @param:     id, the parameter we're creating.
    @param:     initial, the intial value.
    @param:     min, minimum value for this parameter.
    @param:     max, maximum value for this parameter.
    @param:     step, the amount to increment or decrement this value.

    @note:      The parameter values are saved as floats, even if the desired format is something else, like uint16.
                This is to simplify the handling of various types.
    ******************************************************************************************************************/
    WeatherParameter(weather_ID_t id, float initial, float min, float max, float step);

    /*****************************************************************************************************************
    @brief:     To simulate changing weather parameters, this function applies a step. It increases until we're >
                the max value, then we decrement, until we're < the min value.
    ******************************************************************************************************************/
    void ApplyStep(void);

    /*****************************************************************************************************************
    @brief:     Converts the current value of this parameter to a string.
    @param:     str, the destination to which we'll write the string.
    @param:     length, maximum string length.
    ******************************************************************************************************************/
    void CurrentValueStr(char *str, size_t length);
};



#endif		// Prevent multiple includes
