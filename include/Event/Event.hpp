#pragma once

#include <memory>
#include <ciso646>

class Event
{
	
public:
	
	// https://stackoverflow.com/questions/29491771/template-method-in-uml
	// https://www.nextptr.com/tutorial/ta1227747841/the-stdshared_ptrvoid-as-arbitrary-userdata-pointer

	int id;
	std::shared_ptr<void> data;

	Event() = delete;
	
	template<typename T = void*>
	Event(int id, const T& data = nullptr) : id(id) { this->data = std::make_shared<T>(T(data)); };

	template<typename T>
	auto getData() { return *std::static_pointer_cast<T>(this->data); }
	
	operator int() const { return id; }
	
	template<typename T>
	friend T&
	operator << (T& target, Event& event) { return target = event.getData<T>(); }

};