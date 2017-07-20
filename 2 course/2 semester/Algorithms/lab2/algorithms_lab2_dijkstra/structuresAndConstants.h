#pragma once

#include <string>

namespace constants
{
	// Value of D-Heap. 
	const int d = 2;

	// Checks that user chose valid menu item.
	const std::string menuRegex = "[1-3]";
	const std::string numberWithLessThan8DigitsRegex = "^\d{1,7}$";

	// Default min and max weights of graph's edges.
	const unsigned int standardLowestWeight = 1;
	const unsigned int standardHighestWeight = 1000000;

	// Prevents overflows.
	const unsigned int lowestWeightRestrictor = 0;
	const unsigned int highestWeightRestrictor = 1000000;
}

enum MenuItems
{
	CREATE_GRAPH = 1,
	FIND_SHORTEST_PATH,
	EXIT
};

struct ElementOfAdjacencyList
{
	unsigned int name;
	unsigned int weight;
	ElementOfAdjacencyList *next;
};


// User-specified parameters of graph.
struct GraphParameters
{
	unsigned int numberOfVertices = 0;
	unsigned long numberOfEdges = 0;

	unsigned int lowestPossibleWeight = constants::standardLowestWeight;
	unsigned int highestPossibleWeight = constants::standardHighestWeight;
	
	unsigned int startingVertex = 1;

	unsigned long longestPossibleDistance = numberOfVertices * (numberOfVertices - 1) * highestPossibleWeight;
};
