#include "State.h"

State::State(const std::string& n)
{
	name = n;
}

State::State(const State& copy)
{
	*this = copy;
}

State::~State()
{
}
