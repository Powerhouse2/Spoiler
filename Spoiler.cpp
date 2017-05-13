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
 * This function can be overwritten in the master-code
 * @param  armAngle the optimal arm-angle
 * @return       integer representing the optimal motor-angle
 */
int calculateMotorAngle(int armAngle)
{
	// Not implemented yet
	// Calculate optimal motor angle as a function of the spoiler angle
	return armAngle;
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

	// :: means global scope
	return ::calculateMotorAngle(armAngle);
}


/**
 * Set the position of the Spoiler
 * @param motorAngle The optimal motor-angle
 */
void Spoiler::setPosition(int motorAngle)
{
	// Motorangle is not implemented yet, it currently represents
	// The value that the potmeter needs to be at

	// Make sure we do not fry the H-bridge
	digitalWrite(_backwardsPin, LOW);
	digitalWrite(_forwardsPin, LOW);

	if(motorAngle > Spoiler::readResistor()){
		/** Move Backwards  */

		digitalWrite(_backwardsPin, HIGH);
		while(motorAngle > Spoiler::readResistor()){
			if(Spoiler::readResistor() > (POT_MAX - 5)) {
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
			if(Spoiler::readResistor() < (POT_MIN + 5)) {
				// Add a small buffer to allow the actuator to stop
				break;
			}

			delayMicroseconds(delayTime);
		}
		digitalWrite(_forwardsPin, LOW);
	}

	// Prevent intertia from short-circuting the board
	delay(100);
}

/**
 * Read the Potmeter resistance
 * @return analog value
 */
int Spoiler::readResistor()
{
	return analogRead(_resistorPin);
}
