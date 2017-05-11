/*
  Spoiler.h - Library for moving linear actuators for a spoiler
*/
#ifndef Spoiler_h
#define Spoiler_h

#include "Arduino.h"

class Spoiler
{
  public:
    int delayTime = 5000; // Tune this to increase preciness and smoothness
    int potMin = 600;
    int potMax = 600;

    int POT_MIN = 200;
    int POT_MAX = 600;

    Spoiler(int forwardsPin, int backwardsPin, int resistorPin); // Constructor
    void init(); // Enable Spoiler Output pins
    void move(int carSpeed); // Move to optimal location, based on cars current speed
    int speedToAngle(int carSpeed);
    void setPosition(int motorAngle);
    int readResistor();
    int resistorMap(int resistor);

  private:
    int _forwardsPin;
    int _backwardsPin;
    int _resistor;
    int _lastRead;
    int _resistorPin;
};

#endif
