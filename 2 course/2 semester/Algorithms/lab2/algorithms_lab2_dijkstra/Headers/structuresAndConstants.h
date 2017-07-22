#pragma once

#include <string>
#include <regex>

namespace constants
{
	// Checks user's input validness.
	const std::regex menuRegex("[1-5]");
	// [2; 10'001]
	const std::regex numberOfVerticesRegex("^[2-9]{1}$|^[1-9]{1}[0-9]{1,3}$|^1000[0-1]{1}$"); 	
	// [1; 10'000'000]
	const std::regex numberOfEdgesRegex("^[1-9]{1}[0-9]{0,6}$|^10000000$");
	// [1; 1'000'000]
	const std::regex heighestAndLowestPossibleWeightRegex("^[1-9]{1}[0-9]{0,5}$|^1000000$");
	const std::regex dOfDHeapRegex("^[2-9]$");

	// Dialogs with user.
	// Successes
	const std::string graphCreationSuccess = "Graph successfully created!";
	const std::string pathFindingSuccess = "Shortest paths found.";
	// Errors
	const std::string graphNotCreatedError = "Graph was not created.";
	const std::string invalidInputError = "Invalid input.";
	const std::string invalidWeightLimitsInputError = "Lowest possible weight can not be higher than heighest possible input.";
	// What to input phrases
	const std::string menuPhrase = "1. Create graph\n2. Find shortest paths\n3. Comparison of algorithms A and B.\n4. Experiment with changing number of edges.\n5. Exit\n\n";
	const std::string numberOfVerticesPhrase = "Number of vertices [2; 10'001]: ";
	const std::string numberOfEdgesPhrase = "Number of edges [1; 10'000'000]: ";
	const std::string heighestPossibleWeightPhrase = "Heighest possible weight of graph's edge [1; 1'000'000]: ";
	const std::string lowestPossibleWeightPhrase = "Lowest possible weight of graph's edge [1; 1'000'000]: ";
	const std::string dOfDHeapPhrase = "d of d-heap [2; 9]: ";

	// Default min and max weights of graph's edges.
	const unsigned int standardLowestWeight = 1;
	const unsigned int standardHighestWeight = 1000000;

	// Prevents overflows.
	const unsigned int lowestWeightRestrictor = 0;
	const unsigned int highestWeightRestrictor = 1000000;

	const int numberOfTestsInExperiment = 100;
}

enum MenuItems
{
	CREATE_GRAPH = 1,
	FIND_SHORTEST_PATHS,
	ALGORITHMS_COMPARISON,
	EXPERIMENT_WITH_CHANGING_NUMBER_OF_EDGES,
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

	// d of d-heap
	int d = 2;
};

struct Timings
{
	double timingOfAlgorithmA = 0.0;
	double timingOfAlgorithmB = 0.0;
};