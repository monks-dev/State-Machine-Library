#pragma once
#include <iostream>
#include <vector>
#include <functional>

/*

Date: 3/23/24
Author: MONKS

Header File: State
Defines the state class with 3 functions Enter, Update, Leave.

*/

// Enum to represent different events
enum Event
{
	POWER_ON,   // Event when power is turned on
	POWER_OFF,  // Event when power is turned off
	OK,         // Event for okay status
	ERR,        // Event for error status
	CASH_ACCEPT // Event when cash is accepted
};

// Class to represent a state in a state machine
class State
{

public:

	// The State Name
	std::string name; // Name of the state
	std::vector<std::pair<Event, std::string>> transitions; // Transitions from this state to other states

	// Callback functions for state behavior
	std::function<void()> _onEnter;   // Function to be called when entering this state
	std::function<void()> _onExit;    // Function to be called when exiting this state
	std::function<void()> _updateState; // Function to update the state

	// Constructor to initialize a state with a given name
	State(const std::string& n = "");

	// Copy constructor
	State(const State& copy);

	// Destructor
	virtual ~State();

	// Assignment operator overload
	State& operator= (const State& copy) {
		if (this != &copy) {
			name = copy.name;
		}
		return *this;
	}

	// Inequality operator overload
	bool operator!= (const State& a) {
		if (this != &a) {
			return (name != a.name);
		}
		return false;
	}

	// Function to set the onEnter behavior
	virtual void onEnter(std::function<void()> f) {}

	// Function to set the updateState behavior
	virtual void updateState(std::function<void()> f) {}

	// Function to set the onExit behavior
	virtual void onExit(std::function<void()> f) {}

	// Function to display the transitions from this state
	void showTransition() {
		for (auto t : transitions) {
			std::cout << name << ": " << t.first << ": " << t.second << std::endl;
		}
	}

	// Function to add a transition from this state to another state
	void addTransition(Event e, const std::string& nextStateName) {
		transitions.push_back(std::pair<Event, std::string>(e, nextStateName));
	}

	// Function to handle an event and transition to the corresponding state
	std::string handleEvent(Event e) {
		for (auto t : transitions) {
			if (t.first == e) {
				std::cout << "Transitioning to " << t.second << std::endl;
				return t.second;
			}
		}
		return "";
	}
};
