#include <DisplayDriver/DisplayDriver.hpp>

#include <iostream>
#include <algorithm>

void
DisplayDriver::help()
{
	std::cout << "The approrpriate device (/dev/ttyUSBX) can be determined by running 'dmesg -w' before connecting the USB.\n"
	          << "The baudrate can be determine by running 'sudo stty -F /dev/ttyUSB0'.\n"
	          << "The program must be run with sudo privileges to connect to the /dev/ttyX device.\n"
	          << std::endl;
}

DisplayDriver::DisplayDriver(const std::string& device, int baudrate)
	: device(device), baudrate(baudrate), init_msg({ device, "Version " + std::string(DRIVER_VERSION) })
{

	// connect to display
	// use 'sudo stty -F /dev/ttyUSB0' to determine baudrate etc.
	int err_code = serial.openDevice(device.c_str(), baudrate);
	if (err_code != 1)
	{
		help();
		throw std::runtime_error("Could not connect to DisplayDriver at " + device + " (code: " + std::to_string(err_code) + ")");
	}
	else
		std::cout << "Successful connection to DisplayDriver!\n";
	
	// init display
	this->init();
}


DisplayDriver::~DisplayDriver()
{
	// close serial connection
	serial.closeDevice();
}

void
DisplayDriver::clear()
{
	sendCommand(COMMAND_CLEAR_DISPLAY());
}

void
DisplayDriver::print(const DisplayLines& text)
{	
	if (text.line_upper.length() > NUM_CHAR_PER_LINE or text.line_lower.length() > NUM_CHAR_PER_LINE)
		throw std::runtime_error("DisplayDriver: The NUM_CHAR_PER_LINE (" + std::to_string(NUM_CHAR_PER_LINE) + ") is exceeded in print().");

	auto cmd_upper = COMMAND_WRITE_LINE(CommandLine::UPPER, text.line_upper.data());
	auto cmd_lower = COMMAND_WRITE_LINE(CommandLine::LOWER, text.line_lower.data());

	sendCommand(cmd_upper);
	sendCommand(cmd_lower);

	this->text = text;
}

DisplayDriver::DisplayLines
DisplayDriver::read()
{
	return this->text;
}

void
DisplayDriver::init()
{
	// set display mode
	// std::cout << "DisplayDriver: Setting command type...\n";
	// sendCommand(COMMAND_TYPE_SELECT(CommandType::CD5220));

	// init display
	std::cout << "DisplayDriver: Initializing display...\n";
	sendCommand(COMMAND_INIT_DISPLAY());
	
	// print default message
	std::cout << "DisplayDriver: Printing default message...\n";
	print(init_msg);
}

void
DisplayDriver::reset()
{
	this->init();
}

std::array<char, 5>
DisplayDriver::COMMAND_TYPE_SELECT(CommandType type)
{
	return { 0x02, 0x05, 0x43, type, 0x03 };
}

std::array<char, 2>
DisplayDriver::COMMAND_INIT_DISPLAY()
{
	return { 0x1B, 0x40 };
}

std::array<char, 1>
DisplayDriver::COMMAND_CLEAR_DISPLAY()
{
	return { 0x0C };
}

std::array<char, 24>
DisplayDriver::COMMAND_WRITE_LINE(CommandLine line, const char text[20])
{
	std::array<char, 24> cmd;
	
	cmd.fill(' ');
	cmd[0] = 0x1B; cmd[1] = 0x51; cmd[2] = line; cmd[23] = 0x0D;

	const auto str = std::string(text);
	std::copy(str.begin(), str.end(), cmd.begin() + 3);

	return cmd;
}