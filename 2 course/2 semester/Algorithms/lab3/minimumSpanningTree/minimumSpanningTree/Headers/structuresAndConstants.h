#pragma once

#include <string>
#include <regex>

namespace constants
{
	// Checks user's input validness.
	const std::regex menuRegex("[1-4]");
	// [2; 10'001]
	const std::regex numberOfVerticesRegex("^[2-9]{1}$|^[1-9]{1}[0-9]{1,3}$|^1000[0-1]{1}$"); 	
	// [1; 10'000'000]
	const std::regex numberOfEdgesRegex("^[1-9]{1}[0-9]{0,6}$|^10000000$");
	// [1; 1'000'000]
	const std::regex heighestAndLowestPossibleWeightRegex("^[1-9]{1}[0-9]{0,5}$|^1000000$");

	// Dialogs with user.
	// What to input phrases
	const std::string menuPhrase = "1. Create graph\n2. Find MST\n3. Experiment\n4. Exit\n\n";
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
	FIND_MST,
	EXPERIMENT_WITH_CHANGING_NUMBER_OF_EDGES,
	EXIT
};

struct ElementOfAdjacencyList
{
	int name;
	int weight;
	ElementOfAdjacencyList *next;
};

struct Edges
{
	int firstVertex = 0;
	int secondVertex = 0;
	int weight = 0;
};


// User-specified parameters of graph.
struct GraphParameters
{
	int numberOfVertices = 0;
	long numberOfEdges = 0;

	int lowestPossibleWeight = constants::standardLowestWeight;
	int highestPossibleWeight = constants::standardHighestWeight;
	
	int startingVertex = 1;
};

struct Timings
{
	double timingOfAlgorithmA = 0.0;
	double timingOfAlgorithmB = 0.0;
};