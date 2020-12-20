#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <memory>
#include <ciso646>

#include <Event/Event.hpp>

class Task
{
private:

	std::thread handle;

	std::atomic<bool> is_alive;
	std::atomic<bool> is_muted;

	std::mutex mtx_events_in;
	std::queue<Event> events_in;

	std::mutex& mtx_events_out;
	std::queue<Event>& events_out;

public:

	const std::string name;

protected:

	virtual bool
	init() = 0;

	virtual void
	run() = 0;
	
	void
	sendEventFromTask(const Event& e);

	std::shared_ptr<Event>
	readLatestEvent();

public:

	Task() = delete;
	Task(const std::string& name, std::queue<Event>& events_out, std::mutex& mtx_events_out);
	Task(std::queue<Event>& events_out, std::mutex& mtx_events_out);
	virtual ~Task();

	bool
	start();

	void
	kill(bool force = false);

	void
	mute();

	void
	unmute();

	void
	sendEventToTask(const Event& e);

	static std::shared_ptr<Event>
	getEventFromQueue(std::queue<Event>& events, std::mutex& mutex);

};