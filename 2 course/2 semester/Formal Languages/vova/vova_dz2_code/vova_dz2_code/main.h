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
	const int numberOfStates = 5;
	const int validState = 4;
}
