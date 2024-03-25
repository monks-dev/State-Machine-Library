#include "state_manager.h"

// Default constructor for StateManager
StateManager::StateManager()
{
    // Constructor body is empty as there are no specific initialization tasks
}

// Function to set the current state of the StateManager
void StateManager::setCurrentState(State* state)
{
    if (state == nullptr) // Check if the given state is nullptr
        return; // If so, return without making any changes

    if (state != currentState) { // Check if the new state is different from the current state
        if (currentState != nullptr && currentState->_onExit != nullptr)
            currentState->_onExit(); // Call the onExit function of the current state if it exists

        currentState = state; // Update the current state to the new state
        std::cout << currentState->name << std::endl; // Print the name of the new current state

        if (currentState != nullptr && currentState->_onEnter != nullptr)
            currentState->_onEnter(); // Call the onEnter function of the new current state if it exists
    }
}

// Function to add a transition to the StateManager
void StateManager::addTransition(const Transition& transition)
{
    auto s = findState(transition.fromState); // Find the state from which the transition originates
    if (s == nullptr) { // If the state doesn't exist, create a new state and add it to the list
        s = new State(transition.fromState);
        states.push_back(s);
    }
    s->addTransition(transition.eventId, transition.toState); // Add the transition to the found or newly created state
}

// Function to handle an event in the StateManager
void StateManager::handleEvent(Event eventId)
{
    if (currentState != nullptr) { // Check if there is a current state
        std::string result = currentState->handleEvent(eventId); // Handle the event in the current state and get the result
        setCurrentState(findState(result)); // Set the current state based on the result of handling the event
    }
}
