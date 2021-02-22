/*
TinyGPS - a small GPS library for Arduino providing basic NMEA parsing
Based on work by and "distance_to" and "course_to" courtesy of Maarten Lamers.
Suggestion to add satellites(), course_to(), and cardinal(), by Matt Monson.
Precision improvements suggested by Wayne Holder.
Copyright (C) 2008-2013 Mikal Hart
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License aint32 with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef TinyGPS_h
#define TinyGPS_h

int32 segundos_ABS = 0;

//#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"
//#else
//#include "WProgram.h"
//#endif

#include <stdlib.h>

#define _GPS_VERSION 13 // software version of this library
#define _GPS_MPH_PER_KNOT 1.15077945
#define _GPS_MPS_PER_KNOT 0.51444444
#define _GPS_KMPH_PER_KNOT 1.852
#define _GPS_MILES_PER_METER 0.00062137112
#define _GPS_KM_PER_METER 0.001
#define _GPS_NO_STATS//////////////////////////////////////////////7

//class TinyGPS
//{
//public:
  enum {
    GPS_INVALID_AGE = 0xFFFFFFFF,      GPS_INVALID_ANGLE = 999999999, 
    GPS_INVALID_ALTITUDE = 999999999,  GPS_INVALID_DATE = 0,
    GPS_INVALID_TIME = 0xFFFFFFFF,       GPS_INVALID_SPEED = 999999999, 
    GPS_INVALID_FIX_TIME = 0xFFFFFFFF, GPS_INVALID_SATELLITES = 0xFF,
    GPS_INVALID_HDOP = 0xFFFFFFFF
  };
  

//private:
  enum {_GPS_SENTENCE_GPGGA, _GPS_SENTENCE_GPRMC, _GPS_SENTENCE_OTHER};

  // properties
  unsigned int32 _time, _new_time;
  unsigned int32 _date, _new_date;
  int32 _latitude, _new_latitude;
  int32 _longitude, _new_longitude;
  int32 _altitude, _new_altitude;
  unsigned int32  _speed, _new_speed;
  unsigned int32  _course, _new_course;
  unsigned int32  _hdop, _new_hdop;
  int16 _numsats, _new_numsats;

  unsigned int32 _last_time_fix, _new_time_fix;
  unsigned int32 _last_position_fix, _new_position_fix;

  // parsing state variables
  byte _parity;
  boolean _is_checksum_term;
  char _term[15];
  byte _sentence_type;
  byte _term_number;
  byte _term_offset;
  boolean _gps_data_good;

  static const float GPS_INVALID_F_ANGLE = 1000.0;
  static const float GPS_INVALID_F_ALTITUDE = 1000000.0;
  static const float GPS_INVALID_F_SPEED = -1.0;
  //const 
//float TinyGPS::GPS_INVALID_F_ANGLE = 1000.0;
//const 
//float TinyGPS::GPS_INVALID_F_ALTITUDE = 1000000.0;
//const 
//float TinyGPS::GPS_INVALID_F_SPEED = -1.0;

  //TinyGPS();
  void tinyGPS_init();
  boolean encode(char c); // process one character received from GPS
  //TinyGPS &operator << (char c) {encode(c); return *this;}

  // lat/int32 in MILLIONTHs of a degree and age of fix in milliseconds
  // (note: versions 12 and earlier gave lat/int32 in 100,000ths of a degree.
  void get_position(int32 *latitude, int32 *longitude, unsigned int32 *fix_age = 0);

  // date as ddmmyy, time as hhmmsscc, and age in milliseconds
  void get_datetime(unsigned int32 *date, unsigned int32 *time, unsigned int32 *age = 0);

  // signed altitude in centimeters (from GPGGA sentence)
  inline int32 altitude() { return _altitude; }

  // course in last full GPRMC sentence in 100th of a degree
  inline unsigned int32 course() { return _course; }

  // speed in last full GPRMC sentence in 100ths of a knot
  inline unsigned int32 speed() { return _speed; }

  // satellites used in last full GPGGA sentence
  inline unsigned short satellites() { return _numsats; }

  // horizontal dilution of precision in 100ths
  inline unsigned int32 hdop() { return _hdop; }

  void f_get_position(float *latitude, float *longitude, unsigned int32 *fix_age = 0);
  void crack_datetime(int16 *year, byte *month, byte *day, 
    byte *hour, byte *minute, byte *second, byte *hundredths = 0, unsigned int32 *fix_age = 0);
  float f_altitude();
  float f_course();
  float f_speed_knots();
  float f_speed_mph();
  float f_speed_mps();
  float f_speed_kmph();

  static int16 library_version() { return _GPS_VERSION; }

  static float distance_between (float lat1, float long1, float lat2, float long2);
  static float course_to (float lat1, float long1, float lat2, float long2);
  static const char *cardinal(float course);

#ifndef _GPS_NO_STATS
  void stats(unsigned int32 *chars, unsigned short *good_sentences, unsigned short *failed_cs);
#endif


#ifndef _GPS_NO_STATS
  // statistics
  unsigned int32 _encoded_characters;
  unsigned short _good_sentences;
  unsigned short _failed_checksum;
  unsigned short _passed_checksum;
#endif

  // internal utilities
  int16 from_hex(char a);
  unsigned int32 parse_decimal();
  unsigned int32 parse_degrees();
  boolean term_complete();
  boolean gpsisdigit(char c) { return c >= '0' && c <= '9'; }
  int32 gpsatol(char *str);
  int16 gpsstrcmp(char *str1, char *str2);
  
//};

//!#if !defined(ARDUINO) 
//!// Arduino 0012 workaround
//!#undef int
//!#undef char
//!#undef long
//!#undef byte
//!#undef float
//!#undef abs
//!#undef round 
//!#endif
//!
//!#endif


//#include <tinyGPS.c>


//#define _GPRMC_TERM   "GPRMC"
char _GPRMC_TERM[] =   "GPRMC";
//#define _GPGGA_TERM   "GPGGA"
char _GPGGA_TERM[] = "GPGGA";

int32 millis(){return segundos_ABS*1000;}

#define COMBINE(sentence_type, term_number) (((unsigned)(sentence_type) << 5) | term_number)


void get_position(int32 *latitude, int32 *longitude, unsigned int32 *fix_age)
{
  if (latitude) *latitude = _latitude;
  if (longitude) *longitude = _longitude;
  if (fix_age) *fix_age = _last_position_fix == GPS_INVALID_FIX_TIME ? 
   GPS_INVALID_AGE : millis() - _last_position_fix;
}

void f_get_position(float *latitude, float *longitude, unsigned int32 *fix_age)
{
  int32 lat, lon;
  get_position(&lat, &lon, fix_age);
  *latitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lat / 1000000.0);
  *longitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lon / 1000000.0);

}

int16 gpsstrcmp( char *str1,  char *str2)
{
  while (*str1 && *str1 == *str2)
    ++str1, ++str2;
  return *str1;
}

int16 from_hex(char a)
{
  if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  else if (a >= 'a' && a <= 'f')
    return a - 'a' + 10;
  else
    return a - '0';
}

// Parse a string in the form ddmm.mmmmmmm...
unsigned int32 parse_degrees()
{
  char *p;
  unsigned int32 left_of_decimal = gpsatol(_term);
  unsigned int32 hundred1000ths_of_minute = (left_of_decimal % 100UL) * 100000UL;
  for (p=_term; gpsisdigit(*p); ++p);
  if (*p == '.')
  {
    unsigned int32 mult = 10000;
    while (gpsisdigit(*++p))
    {
      hundred1000ths_of_minute += mult * (*p - '0');
      mult /= 10;
    }
  }
  return (left_of_decimal / 100) * 1000000 + (hundred1000ths_of_minute + 3) / 6;
}


unsigned int32 parse_decimal()
{
  char *p = _term;
  boolean isneg = *p == '-';
  if (isneg) ++p;
  unsigned int32 ret = 100UL * gpsatol(p);
  while (gpsisdigit(*p)) ++p;
  if (*p == '.')
  {
    if (gpsisdigit(p[1]))
    {
      ret += 10 * (p[1] - '0');
      if (gpsisdigit(p[2]))
        ret += p[2] - '0';
    }
  }
  return isneg ? -ret : ret;
}

int32 gpsatol( char *str)
{

  int32 ret = 0;
  //putchar('<',USER);
  while (gpsisdigit(*str)){
  //putchar(*str,USER);
    ret = 10 * ret + *str++ - '0';
  }
  //putchar('\n',USER);
  //fprintf(USER," ! %ld \n",ret);
  return ret;
}

//TinyGPS::TinyGPS()
void tinyGPS_init(){
_time = (GPS_INVALID_TIME);
_date=(GPS_INVALID_DATE);
_latitude=(GPS_INVALID_ANGLE);
_longitude=(GPS_INVALID_ANGLE);
_altitude=(GPS_INVALID_ALTITUDE);
_speed=(GPS_INVALID_SPEED);
_course=(GPS_INVALID_ANGLE);
_hdop=(GPS_INVALID_HDOP);
_numsats=(GPS_INVALID_SATELLITES);
_last_time_fix=(GPS_INVALID_FIX_TIME);
_last_position_fix=(GPS_INVALID_FIX_TIME);
_parity=(0);
_is_checksum_term=(false);
_sentence_type=(_GPS_SENTENCE_OTHER);
_term_number=(0);
_term_offset=(0);
_gps_data_good=(false);
#ifndef _GPS_NO_STATS
_encoded_characters=(0);
_good_sentences=(0);
_failed_checksum=(0);
#endif
_term[0] = '\0';
}

boolean encode(char c)
{
  boolean valid_sentence = false;

#ifndef _GPS_NO_STATS
  ++_encoded_characters;
#endif
  switch(c)
  {
  case ',': // term terminators
    _parity ^= c;
  case '\r':
  case '\n':
  case '*':
    if (_term_offset < sizeof(_term))
    {
      _term[_term_offset] = 0;
      valid_sentence = term_complete();
    }
    ++_term_number;
    _term_offset = 0;
    _is_checksum_term = c == '*';
    return valid_sentence;

  case '$': // sentence begin
    _term_number = _term_offset = 0;
    _parity = 0;
    _sentence_type = _GPS_SENTENCE_OTHER;
    _is_checksum_term = false;
    _gps_data_good = false;
    return valid_sentence;
  }

  // ordinary characters
  if (_term_offset < sizeof(_term) - 1)
    _term[_term_offset++] = c;
  if (!_is_checksum_term)
    _parity ^= c;

  return valid_sentence;
}

// Processes a just-completed term
// Returns true if new sentence has just passed checksum test and is validated
//bool TinyGPS::
boolean term_complete()
{
  if (_is_checksum_term)
  {
    byte checksum = 16 * from_hex(_term[0]) + from_hex(_term[1]);
    if (checksum == _parity)
    {
      if (_gps_data_good)
      {
#ifndef _GPS_NO_STATS
        ++_good_sentences;
#endif
        _last_time_fix = _new_time_fix;
        _last_position_fix = _new_position_fix;

        switch(_sentence_type)
        {
        case _GPS_SENTENCE_GPRMC:
          _time      = _new_time;
          _date      = _new_date;
          _latitude  = _new_latitude;
          _longitude = _new_longitude;
          _speed     = _new_speed;
          _course    = _new_course;
          break;
        case _GPS_SENTENCE_GPGGA:
          _altitude  = _new_altitude;
          _time      = _new_time;
          _latitude  = _new_latitude;
          _longitude = _new_longitude;
          _numsats   = _new_numsats;
          _hdop      = _new_hdop;
          break;
        }
        return true;
      }
    }

#ifndef _GPS_NO_STATS
    else
      ++_failed_checksum;
#endif
    return false;
  }

  // the first term determines the sentence type
  if (_term_number == 0)
  {
    if (!gpsstrcmp(_term, _GPRMC_TERM))
      _sentence_type = _GPS_SENTENCE_GPRMC;
    else{ 
      if (!gpsstrcmp(_term, _GPGGA_TERM)){      _sentence_type = _GPS_SENTENCE_GPGGA;}
      else{      _sentence_type = _GPS_SENTENCE_OTHER;}
    }
    return false;
  }

  if (_sentence_type != _GPS_SENTENCE_OTHER && _term[0])
    switch(COMBINE(_sentence_type, _term_number))
  {
    case COMBINE(_GPS_SENTENCE_GPRMC, 1): // Time in both sentences
    case COMBINE(_GPS_SENTENCE_GPGGA, 1):
      _new_time = parse_decimal();
      _new_time_fix = millis();
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 2): // GPRMC validity
      _gps_data_good = _term[0] == 'A';
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 3): // Latitude
    case COMBINE(_GPS_SENTENCE_GPGGA, 2):
      _new_latitude = parse_degrees();
      _new_position_fix = millis();
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 4): // N/S
    case COMBINE(_GPS_SENTENCE_GPGGA, 3):
      if (_term[0] == 'S')
        _new_latitude = -_new_latitude;
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 5): // Longitude
    case COMBINE(_GPS_SENTENCE_GPGGA, 4):
      _new_longitude = parse_degrees();
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 6): // E/W
    case COMBINE(_GPS_SENTENCE_GPGGA, 5):
      if (_term[0] == 'W')
        _new_longitude = -_new_longitude;
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 7): // Speed (GPRMC)
      _new_speed = parse_decimal();
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 8): // Course (GPRMC)
      _new_course = parse_decimal();
      break;
    case COMBINE(_GPS_SENTENCE_GPRMC, 9): // Date (GPRMC)
      _new_date = gpsatol(_term);
      break;
    case COMBINE(_GPS_SENTENCE_GPGGA, 6): // Fix data (GPGGA)
      _gps_data_good = _term[0] > '0';
      break;
    case COMBINE(_GPS_SENTENCE_GPGGA, 7): // Satellites used (GPGGA)
      _new_numsats = (unsigned char)atoi(_term);
      break;
    case COMBINE(_GPS_SENTENCE_GPGGA, 8): // HDOP
      _new_hdop = parse_decimal();
      break;
    case COMBINE(_GPS_SENTENCE_GPGGA, 9): // Altitude (GPGGA)
      _new_altitude = parse_decimal();
      break;
  }

  return false;
}




