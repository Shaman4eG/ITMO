#include "main.h"

// TODO: Tasks 2-4

int main()
{
	// Keeps user-specified parameters for graph creation.
	GraphParameters graphParameters;

	// Pointers to lists of adjacent vertices.
	std::vector<ElementOfAdjacencyList*> ADJ;
	// Represents final shortest distance from vertex 's' to vertex 'name[i]'.
	std::vector<unsigned long long> dist;
	// Keeps penultimate vertex in finished path from 's' to 'name[i]'.
	std::vector<unsigned long> up;
	
	// Prevents usage of path finding function (ldgDijkstraDHeap), until graph was created.
	bool graphWasCreated = false;
	// Used as flag of exit, if user chooses corresponding menu item.
	bool exit = false;

	MenuItems menuItem = EXIT;
	Timings timings;

	while (!exit)
	{
		system("cls");
		menuItem = getMenuItem();
		doChosenAction(menuItem, &exit, &graphWasCreated, ADJ, &graphParameters, dist, up, &timings);
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
					GraphParameters *graphParameters, std::vector<unsigned long long> &dist, std::vector<unsigned long> &up,
					Timings *timings)
{
	switch (menuItem)
	{
	case CREATE_GRAPH:
		*graphParameters = getGraphParameters();
		formGraph(graphWasCreated, ADJ, graphParameters);
		std::cout << constants::graphCreationSuccess << std::endl;
		break;

	case FIND_SHORTEST_PATHS:
		if (*graphWasCreated)
		{
			ldgDijkstraDHeap(ADJ, dist, up, graphParameters);
			std::cout << constants::pathFindingSuccess << std::endl;
		}
		else std::cout << constants::graphNotCreatedError << std::endl;
		break;

	case ALGORITHMS_COMPARISON:
		if (*graphWasCreated) algorithmsComparison(ADJ, dist, up, graphParameters, timings);
		else std::cout << constants::graphNotCreatedError << std::endl;
		break;

	case EXPERIMENT_WITH_CHANGING_NUMBER_OF_EDGES:
		experimentWithChangingNumberOfEdges(ADJ, dist, up);
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
	graphParameters.numberOfVertices = 10'001;
	graphParameters.numberOfEdges = 1'000'000;
	graphParameters.lowestPossibleWeight = 1;
	graphParameters.highestPossibleWeight = 1'000'000;
	graphParameters.d = 4;

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
			std::cout << constants::invalidWeightLimitsInputError << std::endl;
			system("PAUSE");
		}
		else validInput = true; 
	}

	// Input d of d-heap.
	graphParameterInput = checkInputValidness(constants::dOfDHeapPhrase, constants::dOfDHeapRegex);
	graphParameters.d = std::stoi(graphParameterInput);
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
			std::cout << constants::invalidInputError << std::endl << std::endl;
			continue;
		}
		else return input;
	}
}

// Prevents existens of vertices without adjacency.
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters)
{
	long upperLimit = graphParameters->numberOfVertices * (graphParameters->numberOfVertices - 1);
	long lowerLimit = graphParameters->numberOfVertices - 1;

	if ((graphParameters->numberOfEdges < lowerLimit) ||
		(graphParameters->numberOfEdges > upperLimit))
	{
		std::cout << "Number of edges, when there are " << graphParameters->numberOfVertices << " vertices, should be within [" << 
					  lowerLimit << "; " << upperLimit << "]" << std::endl << std::endl;
		system("PAUSE");
		return false;
	}
	else return true;
}

// Comparing two algorithms, savng their timings.
void algorithmsComparison(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long long> &dist,
	std::vector<unsigned long> &up, GraphParameters *graphParameters, Timings *timings)
{
	clock_t start;
	clock_t stop;
	start = clock();
	ldgDijkstraDHeap(ADJ, dist, up, graphParameters);
	stop = clock();
	timings->timingOfAlgorithmA = ((double)(stop - start) / CLK_TCK);

	(graphParameters->d)++;

	start = clock();
	ldgDijkstraDHeap(ADJ, dist, up, graphParameters);
	stop = clock();
	timings->timingOfAlgorithmB = ((double)(stop - start) / CLK_TCK);
	std::cout << "Algorithm A timing: " << timings->timingOfAlgorithmA << " seconds" << std::endl <<
				 "Algorithm B timing: " << timings->timingOfAlgorithmB << " seconds" <<std::endl;

	(graphParameters->d)--;
}

// Experiment 3.3
// 100 runs through graph with different number of edges.
// Saves data into excel file.
void experimentWithChangingNumberOfEdges(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long long> &dist,
	std::vector<unsigned long> &up)
{
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 10'001;
	graphParameters.numberOfEdges = 1'000'000;
	graphParameters.lowestPossibleWeight = 1;
	graphParameters.highestPossibleWeight = 1'000'000;
	graphParameters.d = 4;

	// TODO: SEND RESULTS TO EXCEL FILE
	for (long m = 100'000; m <= 10'000'000; m += 100'000)
	{
		ldgDijkstraDHeap(ADJ, dist, up, &graphParameters);
	}
}