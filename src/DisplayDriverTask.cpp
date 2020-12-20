#include <DisplayDriverTask/DisplayDriverTask.hpp>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

DisplayDriverTask::DisplayDriverTask(const std::string& name, std::queue<Event>& events_out, std::mutex& mtx_events_out, const std::string& device, int baudrate)
	: Task(name, events_out, mtx_events_out), disp(device, baudrate) {}
	
DisplayDriverTask::DisplayDriverTask(std::queue<Event>& events_out, std::mutex& mtx_events_out, const std::string& device, int baudrate)
	: Task(events_out, mtx_events_out), disp(device, baudrate) {}

bool
DisplayDriverTask::init()
{	
	// done
	return true;
}

void
DisplayDriverTask::run()
{
	// run at 100 Hz to not overload system
	std::this_thread::sleep_for(std::chrono::seconds(1/FREQ));
	
	// check for events
	auto event = this->readLatestEvent();
	if (not event)
		return;
		
	// handle incoming events
	switch (*event)
	{

		case EVENT::CLEAR:
		{
			disp.clear();
			break;
		}
			
		case EVENT::PRINT:
		{
			const auto text = event->getData<DisplayDriver::DisplayLines>();
			disp.print(text);
			break;
		}
		
		default:
			std::cerr << "Fault in DisplayDriverTask event loop; caught default case.\n";
	}
}

void
DisplayDriverTask::clear()
{
	this->sendEventToTask(Event(DisplayDriverTask::EVENT::CLEAR));
}

void
DisplayDriverTask::print(const DisplayDriver::DisplayLines& text)
{
	this->sendEventToTask(Event(DisplayDriverTask::EVENT::PRINT, text));
}