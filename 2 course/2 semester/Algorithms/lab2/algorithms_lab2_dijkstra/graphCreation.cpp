#include "graphCreation.h"

// Using graph parameters creates graph. Returns created graph in ADJ parameter.
// Edges are spread between all vertices as even as possible.
void formGraph(bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters)
{
	srand(time(0));

	ADJ.clear();
	// After getting graph parameters we know necessary number of adjacency lists.
	ADJ.resize(graphParameters->numberOfVertices + 1, NULL);

	// Considering each vertices' number of edges difference is less than 2 edges from other vertices, 
	// we can calculate number of complete rows.
	int numberOfCompleteRows = floor((double)graphParameters->numberOfEdges / (double)graphParameters->numberOfVertices);
	// To find left edges we substract number of edges in complete rows from all edges. 
	int edgesInLastRow = graphParameters->numberOfEdges - numberOfCompleteRows * graphParameters->numberOfVertices;

	fillCompleteRows(ADJ, numberOfCompleteRows, graphParameters);
	fillLastRow(ADJ, edgesInLastRow, graphParameters);

	// Flag that enables search of shortest path in graph function.
	*graphWasCreated = true;
}

// Filling data in adjacency vertices in complete rows.
// We use 'numberOfCompleteRows' in first for loop, because it guarantees that there would be still edges to insert.
void fillCompleteRows(std::vector<ElementOfAdjacencyList*> &ADJ, int numberOfCompleteRows, GraphParameters *graphParameters)
{
	for (int column = 1; column <= graphParameters->numberOfVertices; column++)
	{
		for (int row = 1; row <= numberOfCompleteRows; row++)
		{
			ElementOfAdjacencyList *newElem = new ElementOfAdjacencyList();
			newElem->name = generateAdjacentVertexName(ADJ[column], graphParameters->numberOfVertices, column);
			newElem->weight = generateWeight(graphParameters, column, ADJ[newElem->name]);
			newElem->next = ADJ[column];
			ADJ[column] = newElem;
		}
	}
}

// Filling data in adjacency vertices last row.
void fillLastRow(std::vector<ElementOfAdjacencyList*> &ADJ, int edgesInLastRow, GraphParameters *graphParameters)
{
	for (int column = 1; column <= edgesInLastRow; column++)
	{
			ElementOfAdjacencyList *newElem = new ElementOfAdjacencyList();
			newElem->name = generateAdjacentVertexName(ADJ[column], graphParameters->numberOfVertices, column);
			newElem->weight = generateWeight(graphParameters, column, ADJ[newElem->name]); 
			newElem->next = ADJ[column];
			ADJ[column] = newElem;
	}
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
	}
}

// Generates weight. Checks if vertexes are mutualy connected and assignes same weight for them.
unsigned long generateWeight(GraphParameters *graphParameters, int currentBaseVertex, 
							 ElementOfAdjacencyList* adjacencyListToCheck)
{
	unsigned long weight = rand();
	weight %= graphParameters->highestPossibleWeight;
	weight += graphParameters->lowestPossibleWeight;

	if (adjacencyListToCheck != NULL)
	{
		do
		{
			if (adjacencyListToCheck->name == currentBaseVertex) return adjacencyListToCheck->weight;
			adjacencyListToCheck = adjacencyListToCheck->next;
		} while (adjacencyListToCheck != NULL);
	}

	return weight;
}
