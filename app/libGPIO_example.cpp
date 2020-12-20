#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <tuple>

#include "libGPIO/GPIO.hpp"

int main()
{

	std::cout << "starting program..." << std::endl;

// -------------------------------------------------------------------------------------
// 1. Activate GPIO pin (similar to: echo 902 > /sys/class/gpio/export)

	GPIO led_pin;			// calls the empty constructor
	led_pin.setPinNumber(984);

	GPIO button_pin("988");		// calls the constructor taking a string argument

	led_pin.exportPin();
	button_pin.exportPin();

// -------------------------------------------------------------------------------------
// 2. Set directions (similar to: echo "out" > /sys/class/gpio/gpio886/direction)

	led_pin.setPinDirection("out");
	button_pin.setPinDirection("in");

// -------------------------------------------------------------------------------------
// 3. Read the button state (similar to: cat /sys/class/gpio/gpio902/value)

	std::string button_value;
	button_pin.getPinValue(button_value);

// -------------------------------------------------------------------------------------
// 4. Write to the LED (similar to: echo 1 > /sys/class/gpio/gpio886/value)

	led_pin.setPinValue("1");

// -------------------------------------------------------------------------------------
// 5. Link the button an LED

	// Loop forever
	while (true)
	{
		button_pin.getPinValue(button_value);
		led_pin.setPinValue(button_value);

		// Wait 10ms
		usleep(10000);
	}

	// auto [a, b] = std::make_tuple(1, 2.);

	return 0;

}
