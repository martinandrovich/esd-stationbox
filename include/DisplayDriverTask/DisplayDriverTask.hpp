#pragma once

#include <string>
#include <queue>
#include <mutex>

#include <Task/Task.hpp>
#include <DisplayDriver/DisplayDriver.hpp>

class DisplayDriverTask final : public Task
{

public: // members

	static constexpr auto PREFIX = 691;
	static constexpr auto FREQ   = 100; // [Hz]

	enum EVENT
	{
		PRINT = PREFIX + 0,
		CLEAR = PREFIX + 1,
		READ  = PREFIX + 2,
	};

public: // methods

	using Task::Task;
	DisplayDriverTask() = delete;
	~DisplayDriverTask() {};

	DisplayDriverTask(
		std::queue<Event>& events_out,
		std::mutex& mtx_events_out,
		const std::string& device,
		int baudrate
	);

	DisplayDriverTask(
		const std::string& name,
		std::queue<Event>& events_out,
		std::mutex& mtx_events_out,
		const std::string& device,
		int baudrate
	);

	void
	clear();

	void
	print(const DisplayDriver::DisplayLines& text);
	
protected: //methods

	virtual bool
	init() override;

	virtual void
	run() override;

private: // members

	DisplayDriver disp;

};