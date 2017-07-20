#include "main.h"

// TODO: GraphParameters
// TODO: Tasks 2-4

int main()
{
	// Keeps user-specified parameters for graph creation.
	GraphParameters graphParameters;

	// Pointers to lists of adjacent vertices.
	std::vector<ElementOfAdjacencyList*> ADJ;
	// Represents final shortest distance from vertex 's' to vertex 'name[i]'.
	std::vector<unsigned long> dist;
	// Keeps penultimate vertex in finished path from 's' to 'name[i]'.
	std::vector<unsigned long> up;
	
	// Prevents usage of path finding function (ldgDijkstraDHeap), until graph was created.
	bool graphWasCreated = false;
	// Used as flag of exit, if user chooses corresponding menu item.
	bool exit = false;

	MenuItems menuItem = EXIT;

	while (!exit)
	{
		showMenu();
		menuItem = getAndCheckMenuItem();
		doChosenAction(menuItem, &exit, &graphWasCreated, ADJ, &graphParameters, dist, up);
		if (!exit) system("PAUSE");
	}

	return 0;
}

void showMenu()
{
	system("cls");
	std::cout << "1. Create graph\n2. Find shortest paths\n3. Exit\n\n";
}

MenuItems getAndCheckMenuItem()
{
	std::string menuItemPrekeeper = "";
	MenuItems menuItem = EXIT;
	std::regex menuItemChecker(constants::menuRegex);

	while (true)
	{
		getline(std::cin, menuItemPrekeeper);
		bool validInput = std::regex_match(menuItemPrekeeper, menuItemChecker);

		if (!validInput)
		{
			std::cout << ("Invalid input.\n\n");
			continue;
		}
		else
		{
			menuItem = MenuItems(menuItemPrekeeper[0] - '0');
			return menuItem;
		}
	}
}

void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
					GraphParameters *graphParameters, std::vector<unsigned long> &dist, std::vector<unsigned long> &up)
{
	switch (menuItem)
	{
	case CREATE_GRAPH:
		*graphParameters = getGraphParameters();
		formGraph(graphWasCreated, ADJ, graphParameters);
		std::cout << "Graph successfully created!" << std::endl;
		break;

	case FIND_SHORTEST_PATHS:
		if (*graphWasCreated)
		{
			ldgDijkstraDHeap(ADJ, dist, up, graphParameters); 
			std::cout << "Shortest paths found." << std::endl;
		}
		else std::cout << "Graph was not created." << std::endl;
		break;

	case EXIT:
		*exit = true;
		break;
	}
}

// Getting user-specified parameters of graph.
// TODO: Make user input instead of hard set and make checkers!
GraphParameters getGraphParameters()
{
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 6;
	graphParameters.numberOfEdges = 15;
	graphParameters.highestPossibleWeight = 10;
	graphParameters.d = 4;

	return graphParameters;
}



