/**********************************************************************************************************************
 @file:         weatherParameter.cpp
 @author:       Robert Weber
 @copyright:    Released under the MIT license. see license.txt in the top project directory.
 @brief:        Provides changing weather status
 **********************************************************************************************************************/

#include "weatherParameter.h"

#include "utilities.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

const DataFormat_t _format[WEATHER_ID_TOTAL] = {
    DATA_FORMAT_FLOAT,  // WEATHER_ID_OUTSIDE_TEMPERATURE
    DATA_FORMAT_UINT8,  // WEATHER_ID_OUTSIDE_HUMIDITY
    DATA_FORMAT_UINT16, // WEATHER_ID_PRESSURE
    DATA_FORMAT_FLOAT,  // WEATHER_ID_DEW_POINT
    DATA_FORMAT_UINT8,  // WEATHER_ID_WIND_SPEED
    DATA_FORMAT_UINT16  // WEATHER_ID_WIND_DIRECTION (0-359 degrees)
};

WeatherParameter::WeatherParameter(weather_ID_t id, float _initial, float _min, float _max, float _step)
{
  ID = id;
  format = _format[id];
  current = _initial;
  min = _min;
  max = _max;
  step = _step;
  increasing = true;
}

void WeatherParameter::ApplyStep()
{
  switch (this->format)
  {
  case DATA_FORMAT_FLOAT:
    if (this->increasing)
    {
      this->current += this->step;
      if (this->current > this->max)
      {
        this->current = this->max;
        this->increasing = false;
      }
    }
    else
    {
      this->current -= this->step;
      if (this->current < this->min)
      {
        this->current = this->min;
        this->increasing = true;
      }
    }
    break;

  case DATA_FORMAT_CHAR:
  {
    char t_new = (char)this->current + (char)this->step;
    char t_max = (char)this->max;
    char t_min = (char)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_UINT8:
  {
    uint8_t t_new = (uint8_t)this->current + (uint8_t)this->step;
    uint8_t t_max = (uint8_t)this->max;
    uint8_t t_min = (uint8_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_INT8:
  {
    int8_t t_new = (int8_t)this->current + (int8_t)this->step;
    int8_t t_max = (int8_t)this->max;
    int8_t t_min = (int8_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_UINT16:
  {
    uint16_t t_new = (uint16_t)this->current + (uint16_t)this->step;
    uint16_t t_max = (uint16_t)this->max;
    uint16_t t_min = (uint16_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_INT16:
  {
    int16_t t_new = (int16_t)this->current + (int16_t)this->step;
    int16_t t_max = (int16_t)this->max;
    int16_t t_min = (int16_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_UINT32:
  {
    uint32_t t_new = (uint32_t)this->current + (uint32_t)this->step;
    uint32_t t_max = (uint32_t)this->max;
    uint32_t t_min = (uint32_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  case DATA_FORMAT_INT32:
  {
    int32_t t_new = (int32_t)this->current + (int32_t)this->step;
    int32_t t_max = (int32_t)this->max;
    int32_t t_min = (int32_t)this->min;
    if (this->increasing)
    {
      if (t_new > t_max)
      {
        t_new = t_max;
        this->increasing = false;
      }
      this->current = (float)t_new;
    }
    else
    {
      if (t_new < t_min)
      {
        t_new = t_min;
        this->increasing = true;
      }
    }
    this->current = (float)t_new;
    break;
  }

  default:
    // unhandled
    break;
  }
}

void WeatherParameter::CurrentValueStr(char *str, size_t length)
{
  if ((str != NULL) && (length > 0))
  {
    if (this->format == DATA_FORMAT_FLOAT)
    {
      snprintf(str, length, "%.1f", this->current);
    }
    else if ((this->format == DATA_FORMAT_CHAR) || (this->format == DATA_FORMAT_UINT8) ||
             (this->format == DATA_FORMAT_UINT16) || (this->format == DATA_FORMAT_UINT32))
    {
      snprintf(str, length, "%u", (uint32_t)this->current);
    }
    else if ((this->format == DATA_FORMAT_INT8) || (this->format == DATA_FORMAT_INT16) ||
             (this->format == DATA_FORMAT_UINT32))
    {
      snprintf(str, length, "%d", (int32_t)this->current);
    }
    // else, unhandled
  }
}
