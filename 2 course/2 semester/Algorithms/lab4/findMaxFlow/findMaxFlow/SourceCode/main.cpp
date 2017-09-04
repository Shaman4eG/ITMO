#include "../Headers/main.h"

int main()
{
	//srand(time(NULL));

	GraphParameters graphParameters = setGraphParameters();
	std::vector <std::vector <Edge> > listsOfEdges;

	bool exit = false;
	bool graphCreated = false;

	while (!exit)
	{
		system("cls");
		MenuItems menuItem = getMenuItem();
		doChosenAction(menuItem, &graphCreated, &exit, &graphParameters, listsOfEdges);
		if (!exit) system("PAUSE");
	}

	return 0;
}

GraphParameters setGraphParameters()
{
	GraphParameters graphParameters;
	graphParameters.numberOfVertices = 6;
	graphParameters.numberOfEdges = 17;

	return graphParameters;
}

MenuItems getMenuItem()
{
	std::cout << "1. Create graph\n2. Find max flow\n3. Exit\n\n";

	std::string input = "";

	bool validInput = false;
	while (true)
	{
		getline(std::cin, input);
		validInput = std::regex_match(input, constants::menuRegex);

		if (!validInput)
		{
			std::cout << "Invalid input." << std::endl << std::endl;
			continue;
		}
		else return (MenuItems)std::stoi(input);
	}

}


void doChosenAction(MenuItems menuItem, bool *graphCreated, bool *exit, GraphParameters *graphParameters,
	std::vector <std::vector <Edge> > &listsOfEdges)
{
	switch (menuItem)
	{
	case CREATE_GRAPH:
		createGraph(graphCreated, graphParameters, listsOfEdges);
		std::cout << "Graph successfully created!" << std::endl;
		break;

	case FIND_MAX_FLOW:
		findMaxFlowAndMinCutPreparation(graphCreated, graphParameters, listsOfEdges);
		break;

	case EXIT:
		*exit = true;
		break;
	}
}

void findMaxFlowAndMinCutPreparation(bool *graphCreated, GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges)
{
	if (*graphCreated)
	{
		int maxFlow = findMaxFlow(graphParameters, listsOfEdges);
		std::vector<ElementOfPath> combination;
		findMinCut(graphParameters, listsOfEdges, maxFlow, combination);
		std::cout << "\nMax flow = " << maxFlow << std::endl;
		std::cout << "Min cut:" << std::endl;
		for (int i = 0; i < combination.size(); i++)
		{
			std::cout << "\t" << convertVertexName(combination[i].from) << " --(" << combination[i].capacity << 
			")--> " << convertVertexName(combination[i].thisVertex) << std::endl;
		}
	}
	else std::cout << "Graph was not created." << std::endl;
}

char convertVertexName(VertexName currentVertex)
{
	switch (currentVertex)
	{
		case A: return 'A'; break;
		case B: return 'B'; break;
		case C: return 'C'; break;
		case D: return 'D'; break;
		case E: return 'E'; break;
		case F: return 'F'; break;
	}
}
