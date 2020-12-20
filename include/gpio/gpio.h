#pragma once

#include <string>

class gpio
{

public:

	enum dir
	{
		in,
		out
	};

	gpio(const std::string& pin_number, gpio::dir dir = gpio::dir::out);
	~gpio();

	std::string
	get_value();

	void
	set_value(const std::string& value);
	
	gpio::dir
	get_dir();
	
	void
	set_dir(gpio::dir dir);

private:

	// auto constexpr PIN_EXPORT_PATH   = "/sys/class/gpio/export";
	// auto constexpr PIN_UNEXPORT_PATH = "/sys/class/gpio/unexport";

	void
	is_available();

	void
	export_pin(const std::string& pin_number);

	void
	unexport_pin(const std::string& pin_number);

	int         pin_number_;
	int         fd_value_;
	gpio::dir   dir_;

	std::string str_gpio_pin_number_;
	std::string str_gpio_path_;
	std::string str_gpio_dir_;
	std::string str_gpio_value_;
};