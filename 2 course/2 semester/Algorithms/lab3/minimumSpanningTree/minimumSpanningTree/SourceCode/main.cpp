#include "../Headers/main.h"

int main()
{
	// Keeps user-specified parameters for graph creation.
	GraphParameters graphParameters;

	// Pointers to lists of adjacent vertices.
	std::vector<ElementOfAdjacencyList*> ADJ;
	// Pair firstVertexOfEdge[i], secondVertexOfEdge[i] keeps the i edge of MST.
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
			findMST(ADJ, graphParameters, MST);
			std::cout << "Minumum spanning tree found."<< std::endl;
		}
		else std::cout << "Graph was not created." << std::endl;
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




void findMST(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, std::vector<Edges> &MST)
{
	// Keeps vertices connected by edges of all subtrees.
	std::vector<std::vector<Edges> > edgesSubsets(graphParameters->numberOfVertices + 1, std::vector<Edges>());

	// Each element is a part of some subtree. -1 is a marker of removed tree.
	std::vector<std::vector<int> > listsOfComponents(graphParameters->numberOfVertices + 1, std::vector<int>());

	// Initializing first row with all vertices.
	for (int column = 1; column < listsOfComponents.size(); column++)
	{
		listsOfComponents[column].push_back(column);
	}

	// Continue executing algorithm until there are only 1 component left, which is MST.
	int numberOfComponents = graphParameters->numberOfVertices;

	// When entering 'findLowestWeightElementInComponent()' function first time, some extra initializations must be done.
	bool firstSearch = true;

	while (numberOfComponents > 1)
	{
		// Findig lowest element for each component and adding it to corresponding list.
		for (int component = 1; component < listsOfComponents.size(); component++)
		{
			if (listsOfComponents[component][0] == -1) continue;
			
			int elementWithLowestWeight = findLowestWeightElementInComponent(listsOfComponents, ADJ, component, &firstSearch, edgesSubsets);
			listsOfComponents[component].push_back(elementWithLowestWeight);
		}
		firstSearch = false;


		// Finds same elements in different lists and puts them into one, keeping one subtree and marking as irrelevant another.
		for (int component = 1; component < listsOfComponents.size(); component++)
		{
			if (numberOfComponents < 2) break;
			if (listsOfComponents[component][0] == -1) continue;
			// Used to start from only new elements.
			int firstNewElementIndex = listsOfComponents[component].size() - 1;
			findListHeaderAsNewElement(listsOfComponents, component, edgesSubsets, &numberOfComponents);
			findNewAndAddedElementsFromOtherComponents(listsOfComponents, component, edgesSubsets, firstNewElementIndex, &numberOfComponents);
		}
	}

	// Says which column keeps MST.
	int columnWithMST = 0;
	for (int component = 1; component < listsOfComponents.size(); component++)
	{
		if (listsOfComponents[component][0] != -1)
		{
			columnWithMST = component;
			break;
		}
	}

	cleaningRedundantEdgeOfMST(edgesSubsets, columnWithMST, MST);
}

int findLowestWeightElementInComponent(std::vector<std::vector<int> > &listsOfComponents, std::vector<ElementOfAdjacencyList*> &ADJ,
	int component, bool *firstSearch, std::vector<std::vector<Edges> > &edgesSubsets)
{
	ElementOfAdjacencyList *elementWithLowestWeight = new ElementOfAdjacencyList;
	elementWithLowestWeight->weight = INT32_MAX;

	Edges newEdge;

	for (int elementOfComponent = 0; elementOfComponent < listsOfComponents[component].size(); elementOfComponent++)
	{
		int elementWhoseAdjacentEdgesAreToBeChecked = listsOfComponents[component][elementOfComponent];

		ElementOfAdjacencyList *currentElementWithLowestWeight = ADJ[elementWhoseAdjacentEdgesAreToBeChecked];
		bool lowestWeightElementExists = false;

		// Checks that there is at least one element, that is not in least already.
		do
		{
			if (!(std::find(listsOfComponents[component].begin(), listsOfComponents[component].end(),
				currentElementWithLowestWeight->name) != listsOfComponents[component].end()))
			{
					lowestWeightElementExists = true;
					break;
			}
			currentElementWithLowestWeight = currentElementWithLowestWeight->next;
		} while (currentElementWithLowestWeight != NULL);


		ElementOfAdjacencyList *currentElementToCompareTo = NULL;
		if (currentElementWithLowestWeight != NULL) currentElementToCompareTo = currentElementWithLowestWeight->next;

		// Search of lowest weight edge.
		while (currentElementToCompareTo != NULL)
		{
			if (!(std::find(listsOfComponents[component].begin(), listsOfComponents[component].end(),
				currentElementToCompareTo->name) != listsOfComponents[component].end()))
			{
				if (currentElementToCompareTo->weight < currentElementWithLowestWeight->weight)
				{
					currentElementWithLowestWeight = currentElementToCompareTo;
				}
			}
			currentElementToCompareTo = currentElementToCompareTo->next;
		}

		// Checking element to have lowest weight across all comonent.
		if ((lowestWeightElementExists) && (currentElementWithLowestWeight->weight < elementWithLowestWeight->weight))
		{
			elementWithLowestWeight = currentElementWithLowestWeight;
			newEdge.firstVertex = elementWhoseAdjacentEdgesAreToBeChecked;
			newEdge.secondVertex = elementWithLowestWeight->name;
		}
	}

	// Used to supply header element with an edge.
	if (*firstSearch)
	{
		edgesSubsets[component].push_back(newEdge);
	}

	edgesSubsets[component].push_back(newEdge);

	return elementWithLowestWeight->name;
}

// Searches if new added element to lists after current is same as header of current list. 
// If so, adds all elements, that are not already in list, and sets -1 marker on it. 
void findListHeaderAsNewElement(std::vector<std::vector<int> > &listsOfComponents, int workingComponent, 
	std::vector<std::vector<Edges> > &edgesSubsets, int *numberOfComponents)
{
	int workingElement = listsOfComponents[workingComponent][0];

	// Searching for presense of current list header as new element of other components.
	// Adding 1 is used to start from component following current.
	for (int nextComponent = workingComponent + 1; nextComponent < listsOfComponents.size(); nextComponent++)
	{
		if (listsOfComponents[nextComponent][0] == -1) continue;

		int lastElementOfComponent = listsOfComponents[nextComponent].back();

		if (workingElement == lastElementOfComponent)
		{
			addElementFromAnotherComponent(listsOfComponents, nextComponent, workingComponent, edgesSubsets);

			// Marking subtree as unexisting anymore.
			listsOfComponents[nextComponent][0] = -1;
			(*numberOfComponents)--;
		
		}
	}
}


// Searches if subsequent lists have new element or newly added elements from other components in subsequent components.
// If so, adds all elements, that are not already in list, and sets -1 marker on it. 
void findNewAndAddedElementsFromOtherComponents(std::vector<std::vector<int> > &listsOfComponents, int workingComponent,
	std::vector<std::vector<Edges> > &edgesSubsets, int workingElementIndex, int *numberOfComponents)
{
	do
	{
		int workingElement = listsOfComponents[workingComponent][workingElementIndex];

		// Searching for presense of new elements in subsequent components.
		// Adding 1 is used to start from component following current.
		for (int nextComponent = workingComponent + 1; nextComponent < listsOfComponents.size(); nextComponent++)
		{
			if (listsOfComponents[nextComponent][0] == -1) continue;

			// If element found - adds all elements, that are not already in list.
			if (std::find(listsOfComponents[nextComponent].begin(), listsOfComponents[nextComponent].end(),
				workingElement) != listsOfComponents[nextComponent].end())
			{
				addElementFromAnotherComponent(listsOfComponents, nextComponent, workingComponent, edgesSubsets);

				// Marking subtree as unexisting anymore.
				listsOfComponents[nextComponent][0] = -1;
				(*numberOfComponents)--;
			}
		}
	} while (listsOfComponents[workingComponent].back() != listsOfComponents[workingComponent][workingElementIndex++]);
}

// Adding each element that is not at current working list and transfering edges.
void addElementFromAnotherComponent(std::vector<std::vector<int> > &listsOfComponents, int nextComponent, 
	int workingComponent, std::vector<std::vector<Edges> > &edgesSubsets)
{
	for (int elementOfComponent = 0; elementOfComponent < listsOfComponents[nextComponent].size(); elementOfComponent++)
	{
		// If element not found in current working list - add it. 
		if (!(std::find(listsOfComponents[workingComponent].begin(), listsOfComponents[workingComponent].end(),
			listsOfComponents[nextComponent][elementOfComponent]) != listsOfComponents[workingComponent].end()))
		{
			listsOfComponents[workingComponent].push_back(listsOfComponents[nextComponent][elementOfComponent]);
		}
	}

	// Transfering all edges to new list.
	for (int edgeOfSubset = 0; edgeOfSubset < edgesSubsets[nextComponent].size(); edgeOfSubset++)
	{
		edgesSubsets[workingComponent].push_back(edgesSubsets[nextComponent][edgeOfSubset]);
	}
}

void cleaningRedundantEdgeOfMST(std::vector<std::vector<Edges> > &edgesSubsets, int columnWithMST, std::vector<Edges> &MST)
{
	MST.push_back(edgesSubsets[columnWithMST][0]);

	// Going through each accumulated edge.
	for (int edge = 1; edge < edgesSubsets[columnWithMST].size(); edge++)
	{
		int numberOfCopiesNotFound = 0;
		// Going through each edge already in MST vector.
		for (int edgeInMST = 0; edgeInMST < MST.size(); edgeInMST++)
		{
			// If no direct copies.
			if (!((MST[edgeInMST].firstVertex == edgesSubsets[columnWithMST][edge].firstVertex) &&
				(MST[edgeInMST].secondVertex == edgesSubsets[columnWithMST][edge].secondVertex)))
			{
				// If no mirror copies.
				if (!((MST[edgeInMST].firstVertex == edgesSubsets[columnWithMST][edge].secondVertex) &&
					(MST[edgeInMST].secondVertex == edgesSubsets[columnWithMST][edge].firstVertex)))
				{
					numberOfCopiesNotFound++;
				}
			}
		}

		if (numberOfCopiesNotFound == MST.size()) MST.push_back(edgesSubsets[columnWithMST][edge]);
	}
}