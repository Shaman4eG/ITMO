#include "../Headers/graphCreation.h"

// Using graph parameters creates graph. Returns created graph in ADJ parameter.
// Edges are spread between all vertices as even as possible.
void formGraph(bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters)
{
	srand(time(0));

	clearAdjacencyLists(ADJ, graphParameters);

	// After getting graph parameters we know necessary number of adjacency lists.
	ADJ.resize(graphParameters->numberOfVertices + 1, NULL);

	// Considering each vertices' number of edges difference is less than 2 edges from other vertices, 
	// we can calculate number of complete rows.
	int numberOfCompleteRows = floor((double)graphParameters->numberOfEdges / graphParameters->numberOfVertices);
	// To find last column with extra element we substract number of edges in complete rows from all edges. 
	int lastColumnWithExtraElement = graphParameters->numberOfEdges - numberOfCompleteRows * graphParameters->numberOfVertices;

	fillAdjacencyLists(ADJ, numberOfCompleteRows, graphParameters, lastColumnWithExtraElement);

	// Flag that enables search of shortest path in graph function.
	*graphWasCreated = true;
}

// Releases allocated memory.
void clearAdjacencyLists(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters)
{
	std::vector<ElementOfAdjacencyList*> adjacentVerticesOfVertexToDelete(graphParameters->numberOfVertices);
	ElementOfAdjacencyList* elementToDelete = NULL;
	for (int i = 1; i < ADJ.size(); i++)
	{
		elementToDelete = ADJ[i];
		for (int j = 0; j < adjacentVerticesOfVertexToDelete.size(); j++)
		{
			if (elementToDelete != NULL)
			{
				adjacentVerticesOfVertexToDelete[j] = elementToDelete;
				elementToDelete = elementToDelete->next;
			}
			else break;
		}

		for (int j = 0; j < adjacentVerticesOfVertexToDelete.size(); j++)
		{
			if (adjacentVerticesOfVertexToDelete[j] != NULL) delete adjacentVerticesOfVertexToDelete[j];
			else break;
		}
		adjacentVerticesOfVertexToDelete.clear();
		adjacentVerticesOfVertexToDelete.resize(graphParameters->numberOfVertices);
	}
	ADJ.clear();
}

void fillAdjacencyLists(std::vector<ElementOfAdjacencyList*> &ADJ, int numberOfCompleteRows, GraphParameters *graphParameters,
	int lastColumnWithExtraElement)
{
	int totalNumberOfElementsInColumn = numberOfCompleteRows + 1;
	int numberOfEdgesLeft = graphParameters->numberOfEdges;
	// Prevents multiple decrease of totalNumberOfElementsInColumn, because it is supposed to become lower by just 1.
	bool isDecreased = false;

	for (int column = 1; column <= graphParameters->numberOfVertices; column++) 
	{
		// All subsequent columns have 1 less element in adjacency list.
		if ((!isDecreased) && (column > lastColumnWithExtraElement))
		{
			totalNumberOfElementsInColumn--;
			isDecreased = true;
		}

		for (int row = 0; row < totalNumberOfElementsInColumn; row++)
		{
			if (numberOfEdgesLeft-- > 0) addNewElement(ADJ, column, graphParameters);
			else return;
		}
	}
}

// Adds new element to adjacency list.
void addNewElement(std::vector<ElementOfAdjacencyList*> &ADJ, int column, GraphParameters *graphParameters)
{
	ElementOfAdjacencyList *newElem = new ElementOfAdjacencyList();
	newElem->name = generateAdjacentVertexName(ADJ[column], graphParameters->numberOfVertices, column);
	// Is needed to add edge if current vertex is already connected to all other vertices.
	if (newElem->name == 0)
	{
		addNewElement(ADJ, column - 1, graphParameters);
		return;
	}

	newElem->weight = generateWeight(graphParameters, column, ADJ[newElem->name]);
	newElem->next = ADJ[column];
	ADJ[column] = newElem;
	// second paramter - column = newElemn->name because name of adjacent vertex and its column are equal.
	addReflectionElement(ADJ, newElem->name, graphParameters, newElem, column);
}

// Graph is indirect, so when one vertex gets adjacent edge to another it belongs to both.
// This function adds new edge to second vertex.
void addReflectionElement(std::vector<ElementOfAdjacencyList*> &ADJ, int column, GraphParameters *graphParameters,
	ElementOfAdjacencyList *newElem, int callerVertexName)
{
	ElementOfAdjacencyList *reflectionElement = new ElementOfAdjacencyList();
	reflectionElement->name = callerVertexName;
	reflectionElement->weight = newElem->weight;
	reflectionElement->next = ADJ[column];
	ADJ[column] = reflectionElement;
}

// Randomly generates adjacent vertex. 
// If this vertex is already in vector, tries another.
// Else returns vertex name. 
unsigned long generateAdjacentVertexName(ElementOfAdjacencyList *firstElementOfAdjacencyList, unsigned int numberOfVertices, 
										 int baseVertex)
{

	ElementOfAdjacencyList *currentElement = firstElementOfAdjacencyList;
	unsigned long vertexToMakeAdjacent = rand() % numberOfVertices + 1;

	if (currentElement == NULL)
	{
		if (vertexToMakeAdjacent != baseVertex) return vertexToMakeAdjacent;
		else
		{
			vertexToMakeAdjacent++;
			if (vertexToMakeAdjacent > numberOfVertices) vertexToMakeAdjacent = 1;
			return vertexToMakeAdjacent;
		}
	}

	// Used to check if vertex is adjacent to all vertices.
	int vertexTriedFirst = vertexToMakeAdjacent;
	while (true)
	{
		do 
		{
			if ((vertexToMakeAdjacent == currentElement->name) ||
				(vertexToMakeAdjacent == baseVertex))
			{
				vertexToMakeAdjacent++;
				if (vertexToMakeAdjacent > numberOfVertices) vertexToMakeAdjacent = 1;
				currentElement = firstElementOfAdjacencyList;
				break;
			}
			currentElement = currentElement->next;
		} while (currentElement != NULL);

		if (currentElement == NULL) return vertexToMakeAdjacent;
		if (vertexToMakeAdjacent == vertexTriedFirst) return 0;
	}
}

unsigned long generateWeight(GraphParameters *graphParameters, int currentBaseVertex, 
							 ElementOfAdjacencyList* adjacencyListToCheck)
{
	unsigned long weight = rand();
	weight %= graphParameters->highestPossibleWeight;
	weight += graphParameters->lowestPossibleWeight;

	return weight;
}
