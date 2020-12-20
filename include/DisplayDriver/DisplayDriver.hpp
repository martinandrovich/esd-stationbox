#pragma once

#include <string>
#include <array>

#include <serialib.h>

class DisplayDriver
{

public: // members

	// using DisplayLines = std::array<std::string, 2>;
	struct DisplayLines { std::string line_upper, line_lower; };
	
	static constexpr auto NUM_CHAR_PER_LINE = 20;
	static constexpr auto DRIVER_VERSION    = "1.0.5";
	
	const std::string  device;
	const int          baudrate;
	const DisplayLines init_msg;

public: // methods

	DisplayDriver() = delete;
	DisplayDriver(const std::string& device = "/dev/ttyUSB0", int baudrate = 9600);
	~DisplayDriver();
	
	void
	help();

	void
	clear();

	void
	print(const DisplayLines& text);

	DisplayLines
	read();

private: // members

	serialib serial;
	DisplayLines text;
	
	enum CommandType
	{
		ESC_POS = 0x31,
		CD5220  = 0x37,
	};
	
	enum CommandLine
	{
		UPPER = 0x41,
		LOWER = 0x42,
	};

private: // methods

	void
	init();

	void
	reset();

	template <typename ARRAY>
	void
	sendCommand(const ARRAY& cmd) { for (const auto& byte : cmd) { serial.writeChar(byte); }; }
	
	static std::array<char, 5>
	COMMAND_TYPE_SELECT(CommandType type);
	
	static std::array<char, 2>
	COMMAND_INIT_DISPLAY();
	
	static std::array<char, 1>
	COMMAND_CLEAR_DISPLAY();
	
	static std::array<char, 24>
	COMMAND_WRITE_LINE(CommandLine line, const char text[20]);

};