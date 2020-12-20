#include <gpio/gpio.h>

// #include <stdio.h>
// #include <stdlib.h>

#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

gpio::gpio(int pin_number, gpio::dir dir)
{
	// https://www.ics.com/blog/gpio-programming-using-sysfs-interface
	// https://www.ics.com/blog/how-control-gpio-hardware-c-or-c

	// set internal values
	this->pin_number_          = pin_number;
	this->str_gpio_pin_number_ = std::to_string(pin_number);
	this->str_gpio_path_       = "/sys/class/gpio/gpio" + pin_number;
	this->str_gpio_value_      = str_gpio_path_ + "/value";
	this->str_gpio_dir_        = str_gpio_path_ + "/value";

	// check if pin is available (not already claimed)
	;

	// export the desired pin by writing to /sys/class/gpio/export
	// this->export_pin(pin_number_);

	// lock file
	;

	// set direction
	this->set_dir(dir);

	// open value file descriptor
	fd_value_ = open(str_gpio_value_.c_str(), O_WRONLY);

	if (fd_value_ == -1)
	{
		std::cerr << "Unable to open /sys/class/gpio/export" << std::endl;
		exit(1);
	}
}

gpio::~gpio()
{
	// unexport pin
	this->unexport_pin(str_gpio_pin_number_);

	// close all (implicit unlock) file descriptors
	close(fd_value_);
}

std::string
gpio::get_value()
{

}

void
gpio::set_value(const std::string& value)
{
	
}

gpio::dir
gpio::get_dir()
{
	return this->dir_;
}

void
gpio::set_dir(gpio::dir dir)
{
	std::string str_gpio_dir = str_gpio_path_ + "/direction";
	std::string str_dir      = (dir == gpio::dir::out) ? "out" : "in";

	// update internal dir
	this->dir_ = dir;

	// open dir GPIO file and write desired direction to it
	auto fd_dir = open(str_gpio_dir.c_str(), O_WRONLY);

	if (fd_dir == -1)
	{
		std::cerr << "Unable to open " << str_gpio_dir << std::endl;
		exit(1);
	}

	if (write(fd_dir, str_dir.c_str(), 3) != 3)
	{
		std::cerr << "Error writing to " << str_gpio_dir << std::endl;
		exit(1);
	}

	close(fd_dir);
}


void
gpio::export_pin(const std::string& pin_number)
{
	auto fd_export = open("/sys/class/gpio/export", O_WRONLY);

	if (fd_export == -1)
	{
		std::cerr << "Unable to open /sys/class/gpio/export" << std::endl;
		exit(1);
	}

	if (write(fd_export, pin_number_.c_str(), 2) != 2)
	{
		perror("Error writing to /sys/class/gpio/export");
		exit(1);
	}

	close(fd_export);
}

void
gpio::unexport_pin(const std::string& pin_number)
{
	auto fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);

	if (fd_unexport == -1)
	{
		std::cerr << "Unable to open /sys/class/gpio/unexport" << std::endl;
		exit(1);
	}

	if (write(fd_unexport, pin_number_.c_str(), 2) != 2)
	{
		perror("Error writing to /sys/class/gpio/unexport");
		exit(1);
	}

	close(fd_unexport);
}