#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>

#include <Event/Event.hpp>
#include <DisplayDriverTask/DisplayDriverTask.hpp>

using namespace std::chrono_literals;

int
main(int argc, char const *argv[])
{	
	// TEST: DisplayDriverTask

	// main event queue
	std::mutex mtx_events;
	std::queue<Event> events;
	
	// instantiate task
	// DisplayDriverTask disp_task("customer-display", events, mtx_events); // default
	DisplayDriverTask disp_task("customer-display", events, mtx_events, "/dev/ttyUSB0", 9600);
	
	// start task
	if (not disp_task.start())
	{
		std::cerr << "Could not start the " << disp_task.name << " task." << std::endl;
		exit(-1);
	}
	
	// main loop
	for (size_t t = 1; true; ++t)
	{
		
		std::this_thread::sleep_for(1s);
		
		// send an event to task
		if (t % 10 == 0)
		{
			std::cout << "Sending event to clear screen...\n";
			disp_task.clear();
		}
		else
		if (t % 2 == 0)
		{
			std::cout << "Sending event fancy style...\n";
			disp_task.print({ "Count: " + std::to_string(t), "" });
		}
		else
		{
			std::cout << "Sending event manually...\n";
			auto text = DisplayDriver::DisplayLines{ "Count: " + std::to_string(t), "" };
			auto e = Event(DisplayDriverTask::EVENT::PRINT, text);
			disp_task.sendEventToTask(e);
		}

	} // for

	return 0;
}
