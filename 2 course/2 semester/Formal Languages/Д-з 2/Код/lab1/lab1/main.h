#pragma once

#include <vector>

struct State	
{
	int state;
	std::vector<int> newState;
	std::vector<char> transitionSymbols;
};

namespace constants
{
	const int numberOfStates = 6;
	const int validState = 5;
}
