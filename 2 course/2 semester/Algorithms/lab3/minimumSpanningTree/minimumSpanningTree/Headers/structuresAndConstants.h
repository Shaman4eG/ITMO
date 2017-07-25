#pragma once

#include <string>
#include <regex>

namespace constants
{
	// Checks user's input validness.
	const std::regex menuRegex("[1-2]");
	// [2; 10'001]
	const std::regex numberOfVerticesRegex("^[2-9]{1}$|^[1-9]{1}[0-9]{1,3}$|^1000[0-1]{1}$"); 	
	// [1; 10'000'000]
	const std::regex numberOfEdgesRegex("^[1-9]{1}[0-9]{0,6}$|^10000000$");
	// [1; 1'000'000]
	const std::regex heighestAndLowestPossibleWeightRegex("^[1-9]{1}[0-9]{0,5}$|^1000000$");

	// Dialogs with user.
	// Errors
	const std::string graphNotCreatedError = "Graph was not created.";
	// What to input phrases
	const std::string menuPhrase = "1. Create graph\n2. Exit\n\n";
	const std::string numberOfVerticesPhrase = "Number of vertices [2; 10'001]: ";
	const std::string numberOfEdgesPhrase = "Number of edges [1; 10'000'000]: ";
	const std::string heighestPossibleWeightPhrase = "Heighest possible weight of graph's edge [1; 1'000'000]: ";
	const std::string lowestPossibleWeightPhrase = "Lowest possible weight of graph's edge [1; 1'000'000]: ";

	// Default min and max weights of graph's edges.
	const unsigned int standardLowestWeight = 1;
	const unsigned int standardHighestWeight = 1000000;

	const int numberOfTestsInExperiment = 100;

	const int maxNumberOfEdges = 10'000'000;
}

enum MenuItems
{
	CREATE_GRAPH = 1,
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
};

struct Timings
{
	double timingOfAlgorithmA = 0.0;
	double timingOfAlgorithmB = 0.0;
};