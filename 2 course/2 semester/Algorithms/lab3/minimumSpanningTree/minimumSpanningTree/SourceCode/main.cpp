#include "../Headers/main.h"

int main()
{
	// Keeps user-specified parameters for graph creation.
	GraphParameters graphParameters;

	// Pointers to lists of adjacent vertices.
	std::vector<ElementOfAdjacencyList*> ADJ;

	// Prevents usage of functions until graph was created.
	bool graphWasCreated = false;
	// Used as flag of exit, if user chooses corresponding menu item.
	bool exit = false;

	MenuItems menuItem = EXIT;

	while (!exit)
	{
		system("cls");
		menuItem = getMenuItem();
		doChosenAction(menuItem, &exit, &graphWasCreated, ADJ, &graphParameters);
		if (!exit) system("PAUSE");
	}

	return 0;
}

MenuItems getMenuItem()
{
	std::string menuItem = checkInputValidness(constants::menuPhrase, constants::menuRegex);
	return (MenuItems)std::stoi(menuItem);
}

void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters)
{
	switch (menuItem)
	{
	case CREATE_GRAPH:
		*graphParameters = getGraphParameters();
		formGraph(graphWasCreated, ADJ, graphParameters);
		std::cout << "Graph successfully created!" << std::endl;
		break;

	case EXIT:
		*exit = true;
		break;
	}
}

// Getting user-specified parameters of graph.
GraphParameters getGraphParameters()
{
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 5;
	graphParameters.numberOfEdges = 9;
	graphParameters.lowestPossibleWeight = 1;
	graphParameters.highestPossibleWeight = 10;

	/*
	std::string graphParameterInput = "";
	// Input number of vertices and edges.
	bool validInput = false;
	while (!validInput)
	{
		// Number of vertices.
		graphParameterInput = checkInputValidness(constants::numberOfVerticesPhrase, constants::numberOfVerticesRegex);
		graphParameters.numberOfVertices = std::stoi(graphParameterInput);
		// Number of edges.
		graphParameterInput = checkInputValidness(constants::numberOfEdgesPhrase, constants::numberOfEdgesRegex);
		graphParameters.numberOfEdges = std::stoi(graphParameterInput);

		validInput = checkOfMutualVerticesAndEdgesAppropriateness(&graphParameters);
	}

	// Input lowest and highest possible weights.
	validInput = false;
	while (!validInput)
	{
		// Heighest possible weight.
		graphParameterInput = checkInputValidness(constants::heighestPossibleWeightPhrase, constants::heighestAndLowestPossibleWeightRegex);
		graphParameters.highestPossibleWeight = std::stoi(graphParameterInput);
		// Lowest possible weight.
		graphParameterInput = checkInputValidness(constants::lowestPossibleWeightPhrase, constants::heighestAndLowestPossibleWeightRegex);
		graphParameters.lowestPossibleWeight = std::stoi(graphParameterInput);

		// Prevents lowest possible weight being higher than highest possible weight.
		if (graphParameters.lowestPossibleWeight > graphParameters.highestPossibleWeight)
		{
			std::cout << "Lowest possible weight can not be higher than heighest possible input." << std::endl;
			system("PAUSE");
		}
		else validInput = true;
	}
	*/

	return graphParameters;
}

// Gets user input and checks its validness. Returns only valid input.
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex)
{
	std::cout << whatToInputPhrase;
	std::string input = "";
	bool validInput = false;
	while (true)
	{
		getline(std::cin, input);
		validInput = std::regex_match(input, regex);

		if (!validInput)
		{
			std::cout << "Invalid input." << std::endl << std::endl;
			continue;
		}
		else return input;
	}
}

// Prevents existens of vertices without adjacency.
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters)
{
	// Some of arithmetic progression: ((a1 + (n - 1)) / 2) * (n - 1), where n is number of vertices
	long upperLimit = ((1 + graphParameters->numberOfVertices - 1) / 2) * (graphParameters->numberOfVertices - 1);

	long lowerLimit = graphParameters->numberOfVertices - 1;

	if ((graphParameters->numberOfEdges < lowerLimit) ||
		(graphParameters->numberOfEdges > upperLimit))
	{
		if (upperLimit > constants::maxNumberOfEdges) upperLimit = constants::maxNumberOfEdges;
		std::cout << "Number of edges, when there are " << graphParameters->numberOfVertices << " vertices, should be within [" <<
			lowerLimit << "; " << upperLimit << "]" << std::endl << std::endl;
		system("PAUSE");
		return false;
	}
	else return true;
}