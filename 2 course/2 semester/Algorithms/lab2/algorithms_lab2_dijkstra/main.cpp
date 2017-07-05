#include "main.h"

// TODO: Make file input.

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
	std::cout << "1. Create graph\n2. Find shortest path\n3. Exit\n\n";
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
		std::cout << "Success!" << std::endl;
		break;

	case FIND_SHORTEST_PATH:
		findingShortestPath(graphWasCreated, up, dist, ADJ, graphParameters);
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
	graphParameters.numberOfVertices = 4;
	graphParameters.numberOfEdges = 11;

	return graphParameters;
}



void findingShortestPath(bool *graphWasCreated, std::vector<unsigned long> &dist, std::vector<unsigned long> &up,
						 std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters)
{
	if (!(*graphWasCreated))
	{
		std::cout << "Graph was not created.\n\n";
		return;
	}

	ldgDijkstraDHeap(ADJ, dist, up, graphParameters);
}

void ldgDijkstraDHeap(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long> &dist, 
					  std::vector<unsigned long> &up, GraphParameters *graphParameters)
{
	up.resize(graphParameters->numberOfVertices + 1);
	dist.resize(graphParameters->numberOfVertices + 1);

	// Array of vertices' names. Name of vertex equals its index.
	std::vector<unsigned int> name(graphParameters->numberOfVertices + 1);
	// Represents current estimation of distance from vertex 's' to vertex 'name[i]'.
	std::vector<unsigned long> key(graphParameters->numberOfVertices + 1);
	// Represents names' indices. Is supposed to be correct at that: index[name[i]] = i
	std::vector<unsigned int> index(graphParameters->numberOfVertices + 1);

	// Initializing data keepers.
	for (int i = 1; i <= graphParameters->numberOfVertices; i++)
	{
		up[i] = 0;
		dist[i] = ULLONG_MAX;
		index[i] = i;
		name[i] = i;
		key[i] = ULLONG_MAX;
	}

	key[graphParameters->startingVertex] = 0;
	int nq = graphParameters->numberOfVertices;
	PriorityQueue priorityQueue(index, name, key, nq, constants::d);
	unsigned int name1 = name[1];
	unsigned long key1 = key[1];

	while (nq > 0)
	{
		priorityQueue.getMin(index, name1, key1, name, key, &nq, constants::d);
		int i = name1;
		dist[i] = key1;
		ElementOfAdjacencyList *p = ADJ[i];
		while (p != NULL)
		{
			unsigned int j = p->name;
			unsigned int jq = index[j];
			if (dist[jq] == ULLONG_MAX)
			
				if (key[jq] > dist[i] + p->weight)
				{
					key[jq] = dist[i] + p->weight;
					priorityQueue.emerge(index, jq, name, key, nq, constants::d);
				}
			
			p = p->next;
		}
	}
}