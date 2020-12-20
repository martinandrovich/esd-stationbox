#include <iostream>
#include <string>
#include <mutex>

#include <DisplayDriver/DisplayDriver.hpp>

int
main(int argc, char const *argv[])
{
	// TEST: DisplayDrive
	
	DisplayDriver disp("/dev/ttyUSB0", 9600);
	
	std::cout << "Press [ENTER] for test message..."; std::cin.ignore();
	disp.print({"Hello", "world!"});
	
	std::cout << "Press [ENTER] to clear display..."; std::cin.ignore();
	disp.clear();
	
	std::cout << "Press [ENTER] for bad message..."; std::cin.ignore();
	disp.print({"Helloooooooooooooooooooooooooo", "world!"});

	return 0;
}
