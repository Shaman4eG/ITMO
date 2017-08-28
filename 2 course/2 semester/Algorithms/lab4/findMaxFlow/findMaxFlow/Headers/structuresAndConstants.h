#pragma once

#include <regex>

namespace constants
{
	// Checks user's input validness.
	const std::regex menuRegex("[1-3]");

	// Default min and max weights of graph's edges.
	const unsigned int standardLowestWeight = 1;
	const unsigned int standardHighestWeight = 10;
}

enum MenuItems
{
	CREATE_GRAPH = 1,
	FIND_MAX_FLOW,
	EXIT
};

enum Direction
{
	FORWARD,
	BACKWARD
};

enum VertexName
{
	NOT_A_VERTEX, // Used in path vertex for initialization.
	A,
	B,
	C,
	D,
	E,
	F
};

enum Visitation
{
	UNVISITED,
	VISITED
};

struct GraphParameters
{
	int numberOfVertices = 0;
	long numberOfEdges = 0;

	int lowestPossibleWeight = constants::standardLowestWeight;
	int highestPossibleWeight = constants::standardHighestWeight;
	
	int startingVertex = 1;
};

struct Edge
{
	VertexName vertex = NOT_A_VERTEX;
	int capacity = 0;
	int flow = 0;
};

struct ElementOfPath
{
	VertexName from = NOT_A_VERTEX;
	VertexName thisVertex = NOT_A_VERTEX;
	int capacity = 0;
};