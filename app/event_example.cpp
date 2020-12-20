#include <iostream>
#include <array>
#include <string>

#include <Event/Event.hpp>

int
main(int argc, char const *argv[])
{
	// Event
	
	enum Events
	{ SOME_EVENT = 420 + 69, OTHER_EVENT = 123 + 456 , EMPTY_EVENT = 31415 };
	
	// test with std::string
	{
		auto event = Event(SOME_EVENT, std::string("Hello world!"));
		// auto event = Event(SOME_EVENT, "Hello world!"); // NOT OK
		auto data = event.getData<std::string>();
		std::cout << data << std::endl;
		
		// fancy operator (<<)
		std::string str;
		str << event;
		std::cout << str << std::endl;
		
		// check event id (also works for switches)
		if (event == SOME_EVENT)
			std::cout << "This event is indeed SOME_EVENT" << std::endl;
	}
	
	// test custom string std::string
	{
		struct Test
		{
			std::array<int, 2> stash = { 420, 69 };
			std::string hash = "420_69_yo";
		} my_struct;
		
		auto event = Event(SOME_EVENT, my_struct);
		auto data = event.getData<Test>();
		std::cout << data.hash << ": " << data.stash[1] << std::endl;	
	}
	
	// usage
	{
		// create data and event
		struct MsgType { int a; std::string text; };
		auto event = Event(SOME_EVENT, MsgType{ 1, "hello" } );
		// auto event = Event(EMPTY_EVENT); // event w/o data
		
		// switches
		switch (event)
		{
		
			case SOME_EVENT:
			{
				auto data = event.getData<MsgType>();
				std::cout << "a: " << data.a << ", text: " << data.text << std::endl;
				// break;
			}
				
			case OTHER_EVENT:
			{
				MsgType msg;
				msg << event;	
				std::cout << "a: " << msg.a << ", text: " << msg.text << std::endl;
				break;
			}
		}

	}
	
	// exit
	return 0;
}
