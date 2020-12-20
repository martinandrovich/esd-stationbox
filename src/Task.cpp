#include <Task/Task.hpp>

Task::Task(std::queue<Event>& events_out, std::mutex& mtx_events_out)
	: name("unnamed"), events_out(events_out), mtx_events_out(mtx_events_out)
{
	this->is_alive = false;
	this->is_muted = true;
}

Task::Task(const std::string& name, std::queue<Event>& events_out, std::mutex& mtx_events_out)
	: name(name), events_out(events_out), mtx_events_out(mtx_events_out)
{
	this->is_alive = false;
	this->is_muted = true;
}

Task::~Task()
{
	if (this->is_alive)
		this->kill();
}

bool
Task::start()
{
	// initialize
	if (not this->init())
	{
		std::cerr << "Could not initialize " << this->name << " task..." << std::endl;
		return false;
	}

	// start thread
	handle = std::thread([&]()
	{
		while(this->is_alive)
			this->run();
	});

	// enable task
	this->is_alive = true;
	this->is_muted = false;

	return true;
}

void
Task::kill(bool force)
{
	std::cout << "Killing " << this->name << " task..." << std::endl;

	if (force)
	{
		#ifndef _WIN32
		pthread_cancel(handle.native_handle());
		#endif
	}

	if (handle.joinable())
	{
		this->is_alive = false;
		handle.join();
		std::cout << this->name << " task was killed." << std::endl;
	}
}

void
Task::mute()
{
	this->is_muted = true;
}

void
Task::unmute()
{
	this->is_muted = false;
}

void
Task::sendEventToTask(const Event& e)
{
	std::lock_guard<std::mutex> lock(mtx_events_in);
	events_in.push(e);
}

void
Task::sendEventFromTask(const Event& e)
{
	if (not this->is_muted)
	{
		std::lock_guard<std::mutex> lock(mtx_events_out);
		this->events_out.push(e);
	}
}

std::shared_ptr<Event>
Task::readLatestEvent()
{
	return Task::getEventFromQueue(events_in, mtx_events_in);
}

std::shared_ptr<Event>
Task::getEventFromQueue(std::queue<Event>& events, std::mutex& mutex)
{
	// static public helper method
	std::lock_guard<std::mutex> lock(mutex);

	if (events.empty())
		return nullptr;

	else
	{
		auto event = std::make_shared<Event>(events.front());
		events.pop();
		return event;
	}
}