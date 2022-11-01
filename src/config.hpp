#ifndef config_h
#define config_h
#include <pins_arduino.h>
//config.h

//heater
#define HEATER_PIN A2

#define RBO  ((uint8_t)0)
#define RTO  ((uint8_t)1)
#define RBM  ((uint8_t)2)
#define RTM  ((uint8_t)3)
#define RBI  ((uint8_t)4)
#define RTI  ((uint8_t)5)

#define LBI  ((uint8_t)6)
#define LTI  ((uint8_t)7)
#define LBM  ((uint8_t)8)
#define LTM  ((uint8_t)9)
#define LBO  ((uint8_t)10)
#define LTO  ((uint8_t)11)

#define RTT  ((uint8_t)12)
#define LTT  ((uint8_t)13)


#define UNDEFINED_BLDG ((uint8_t)32)

#define LASER ((uint8_t)0)
#define TRENCH ((uint8_t)1)
#define BALL ((uint8_t)2)
#define LIGHTONLY ((uint8_t)3)


#define YES ((uint8_t)1)
#define NO ((uint8_t)0)

#define NUM_BUILDINGS 18
#define NUM_SENSORS_TYPES 6

#endif