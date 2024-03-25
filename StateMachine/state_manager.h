#pragma once
#include "State.h"
#include <unordered_map>

// Class to represent a transition between states
class Transition
{

public:

    std::string fromState; // Name of the state transitioning from
    Event eventId;         // Event triggering the transition
    std::string toState;   // Name of the state transitioning to

    // Constructor to initialize a transition with fromState, eventId, and toState
    Transition(const std::string& f, Event e, const std::string& t) {
        fromState = f;
        eventId = e;
        toState = t;
    }

    // Copy constructor
    Transition(const Transition& copy) {
        *this = copy;
    }

    // Assignment operator overload
    Transition& operator= (const Transition& copy) {
        if (this != &copy) {
            fromState = copy.fromState;
            eventId = copy.eventId;
            toState = copy.toState;
        }

        return *this;
    }

};

// Class to manage states and transitions
class StateManager
{

public:

    // Constructor
    StateManager();

    // Virtual function to find a state by name
    virtual State* findState(const std::string& name) {
        for (auto it : states) {
            if (it->name == name) {
                return it;
            }
        }
        return nullptr; // Return nullptr if state is not found
    }

    // Virtual function to set the current state
    virtual void setCurrentState(State* state);

    // Virtual function to add a transition
    virtual void addTransition(const Transition& transition);

    // Function to handle an event
    virtual void handleEvent(Event eventId);

    // Function to display all transitions for each state
    void showTransitions() {
        for (auto t : states) {
            t->showTransition();
        }
    }

private:

    State* currentState; // Pointer to the current state
    std::list<State*> states; // List of all states managed by the StateManager
};
