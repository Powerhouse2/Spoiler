#include "Arduino.h"
#include "Spoiler.h"

/**
 * ------------------
 * Global Methods
 * ------------------
 *
 * These methods can be overwritten
 */


/**
 * Calculate the optimal motor-angle from the optimal arm-angle
 * @param  armAngle the optimal arm-angle
 * @return       integer representing the optimal motor-angle
 */
int calculateMotorAngle(int armAngle)
{
	return 1;
}

/**
 * ------------------
 * Class Methods
 * ------------------
 *
 * These methods belong to the class
 */

/**
 * Constructor
 */
Spoiler::Spoiler(int forwardsPin, int backwardsPin, int resistorPin)
{
	_forwardsPin = forwardsPin;
	_backwardsPin = backwardsPin;
	_resistorPin = resistorPin;
}

/**
 * Enable the Output pins for the Spoiler Actuator
 */
void Spoiler::init()
{
	pinMode(_forwardsPin, OUTPUT);
	pinMode(_backwardsPin, OUTPUT);
	pinMode(_resistorPin, INPUT);

	int precision = ((delayTime / 1000) * 20);

	potMin = POT_MIN + precision;
	potMax = POT_MAX - precision;
}

/**
 * Calculate optimal motor-angle and propagate Spoiler movement
 *
 * @param carSpeed the Cars current speed
 */
void Spoiler::move(int carSpeed)
{
	// Get the optimal motor-angle based on
	// the cars current speed
	int angle = Spoiler::speedToAngle(carSpeed);
	Serial.print("Angle: ");
	Serial.println(angle);

	// Set the new Position
	Spoiler::setPosition(angle);
}

/**
 * Convert the cars current speed, to the optimal
 * Spoiler position
 *
 * @param  carSpeed the Cars current speed
 * @return       integer representing the optimal motor-angle
 */
int Spoiler::speedToAngle(int carSpeed)
{
	int armAngle = carSpeed / 150 * ( 1.55 * carSpeed );

	return ::calculateMotorAngle(armAngle);
}


/**
 * Set the position of the Spoiler
 * @param motorAngle The optimal motor-angle
 */
void Spoiler::setPosition(int motorAngle)
{

	if(motorAngle > Spoiler::readResistor()){
		/** Move Backwards  */

		digitalWrite(_backwardsPin, HIGH);
		while(motorAngle > Spoiler::readResistor()){
			if(Spoiler::readResistor() > (potMax - 3)) {
				// Add a small buffer to allow the actuator to stop
				break;
			}

			delayMicroseconds(delayTime);
		}
		digitalWrite(_backwardsPin, LOW);

	} else if(motorAngle < Spoiler::readResistor()) {
		/** Move Forwards */

		digitalWrite(_forwardsPin, HIGH);
		while(motorAngle < Spoiler::readResistor()){
			if(Spoiler::readResistor() < (potMin + 3)) {
				// Add a small buffer to allow the actuator to stop
				break;
			}

			delayMicroseconds(delayTime);
		}
		digitalWrite(_forwardsPin, LOW);

	}
}

/**
 * Read the Potmeter resistance
 * @return analog value
 */
int Spoiler::readResistor()
{
	return analogRead(_resistorPin);
}

int Spoiler::resistorMap(int resistor){
	return resistor;
}
