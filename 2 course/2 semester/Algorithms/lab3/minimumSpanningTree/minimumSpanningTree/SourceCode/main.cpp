#include "../Headers/main.h"

int main()
{
	// Keeps user-specified parameters for graph creation.
	GraphParameters graphParameters;

	// Pointers to lists of adjacent vertices.
	std::vector<ElementOfAdjacencyList*> ADJ;
	// Keeps edges of MST.
	std::vector<Edges> MST;

	// Prevents usage of functions until graph was created.
	bool graphWasCreated = false;
	// Used as flag of exit, if user chooses corresponding menu item.
	bool exit = false;

	MenuItems menuItem = EXIT;

	while (!exit)
	{
		system("cls");
		menuItem = getMenuItem();
		doChosenAction(menuItem, &exit, &graphWasCreated, ADJ, &graphParameters, MST);
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
	GraphParameters *graphParameters, std::vector<Edges> &MST)
{
	switch (menuItem)
	{
	case CREATE_GRAPH:
		*graphParameters = getGraphParameters();
		formGraph(graphWasCreated, ADJ, graphParameters);
		std::cout << "Graph successfully created!" << std::endl;
		break;

	case FIND_MST:
		if (*graphWasCreated)
		{
			Timings timings;
			findMST(ADJ, graphParameters, MST, &timings);
			std::cout << "Minumum spanning tree found."<< std::endl;
			std::cout << "Boruvka's algorithm timing: " << timings.timingOfAlgorithmA << " seconds" << std::endl <<
						 "Kruskal's algorithm timing: " << timings.timingOfAlgorithmB << " seconds" << std::endl;
			// Should be set to false, because graph is broken after Kruskal's algorithm.
			*graphWasCreated = false;
		}
		else std::cout << "Graph was not created." << std::endl;
		break;

	case EXPERIMENT_WITH_CHANGING_NUMBER_OF_EDGES:
	{
		bool success = experiment(ADJ, MST, graphWasCreated);
		if (success) std::cout << "Experiment was successful. Results are in file." << std::endl;
		break;
	}

	case EXIT:
		*exit = true;
		break;
	}
}

// Experiment 3.3
// 100 runs through graph with different number of edges.
// Saves data into excel file.
bool experiment(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<Edges> &MST, bool *graphWasCreated)
{
	// Assigning graph parameters and forming graph.
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 11;//10'001;
	graphParameters.lowestPossibleWeight = 1;
	graphParameters.highestPossibleWeight = 10;// 1'000'000;

	// Preparing file for results.
	std::ofstream timingsExcelFile;
	timingsExcelFile.open("timings.csv");

	if (!timingsExcelFile)
	{
		std::cerr << "Unable to open file." << std::endl;
		return false;
	}

	// Running algorithms.
	std::vector<double> timingsOfA(constants::numberOfTestsInExperiment);
	std::vector<double> timingsOfB(constants::numberOfTestsInExperiment);
	std::vector<long> numberOfEdges(constants::numberOfTestsInExperiment);

	Timings timings;
	doExperiment(ADJ, MST, timingsOfA, timingsOfB, &graphParameters, graphWasCreated, &timings, numberOfEdges);


	// Putting results in file.
	// ';' is a delimeter to put data in next cell.
	for (int i = 0; i < timingsOfA.size(); i++)
	{
		timingsExcelFile << numberOfEdges[i] << ";";
		timingsExcelFile << timingsOfA[i] << ";";
		timingsExcelFile << timingsOfB[i] << std::endl;
	}

	return true;
}

// Running both algorithms.
void doExperiment(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<Edges> &MST, std::vector<double> &timingsOfA,
	std::vector<double> &timingsOfB, GraphParameters *graphParameters, bool *graphWasCreated, Timings *timings,
	std::vector<long> &numberOfEdges)
{
	int indexOfNextFreeSlot = 0;
	for (long m = 100'000; m <= 10'000'000; m += 100'000)
	{
		graphParameters->numberOfEdges = m;
		formGraph(graphWasCreated, ADJ, graphParameters);

		findMST(ADJ, graphParameters, MST, timings);
		timingsOfA[indexOfNextFreeSlot] = timings->timingOfAlgorithmA;
		timingsOfB[indexOfNextFreeSlot] = timings->timingOfAlgorithmB;
		numberOfEdges[indexOfNextFreeSlot++] = m;
	}
}

// Getting user-specified parameters of graph.
GraphParameters getGraphParameters()
{
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 7;
	graphParameters.numberOfEdges = 12;
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
	// Some of arithmetic progression: ((a1 + (n - 1)) / 2) * (n - 1), where n is number of vertices.
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





