/*
  Spoiler.h - Library for moving linear actuators for a spoiler
*/
#ifndef Spoiler_h
#define Spoiler_h

#include "Arduino.h"

class Spoiler
{
  public:
    int delayTime = 20000; // Tune this to increase precision and smoothness

    int POT_MIN = 200;
    int POT_MAX = 600;

    Spoiler(int forwardsPin, int backwardsPin, int resistorPin); // Constructor
    void init(); // Enable Spoiler Output pins
    void move(int carSpeed); // Move to optimal location, based on cars current speed
    int speedToAngle(int carSpeed);
    void setPosition(int motorAngle);
    int readResistor();

  private:
    int _forwardsPin;
    int _backwardsPin;
    int _resistor;
    int _resistorPin;
};

#endif
