#include "graphCreation.h"

// Using graph parameters creates graph. Returns created graph in ADJ parameter.
// Edges are spread between all vertices as even as possible.
void formGraph(bool *graphWasCreated, std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, GraphParameters *graphParameters)
{
	srand(time(0));

	// Considering each vertices' number of edges difference is less than 2 edges from other vertices, 
	// we can calculate number of complete rows vectors.
	int resizeValue = floor((double)graphParameters->numberOfEdges / (double)graphParameters->numberOfVertices);
	// To find left edges we substract number of edges in complete rows from all edges. 
	int edgesInLastRow = graphParameters->numberOfEdges - resizeValue * graphParameters->numberOfVertices;

	createVectorsForAdjacencyLists(*graphParameters, ADJ, edgesInLastRow, resizeValue);
	fillCompleteRows(ADJ, resizeValue, *graphParameters);
	fillLastRow(ADJ, resizeValue, edgesInLastRow, *graphParameters);

	// Flag that enables search of shortest path in graph function.
	*graphWasCreated = true;
}

// Creates vectors of precise size, which would keep adjacency lists.
// If-condition is needed to resize vectors accurately, because last vertices can have 1 less edge.
void createVectorsForAdjacencyLists(GraphParameters graphParameters, std::vector< std::vector< ElementOfAdjacencyList > > &ADJ,
									  int edgesInLastRow, int resizeValue)
{
	for (int i = 0; i < graphParameters.numberOfVertices; i++)
	{
		ADJ.push_back(std::vector<ElementOfAdjacencyList>());
		if (i < edgesInLastRow) ADJ[i].resize(resizeValue + 1);
		else ADJ[i].resize(resizeValue);

		// Initializing name with value that is not equal to any vertex name, because overwise all names would be initialized with name '0'.
		for (int j = 0; j < ADJ[i].size(); j++) ADJ[i][j].name = graphParameters.numberOfVertices;
	}
}

// Filling data in adjacency vertices in complete rows.
// We use 'resizeValue' in first for loop, because it guarantees that there would be still edges to insert.
void fillCompleteRows(std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, int resizeValue, GraphParameters graphParameters)
{
	for (int row = 0; row < resizeValue; row++)
	{
		for (int column = 0; column < graphParameters.numberOfVertices; column++)
		{
			ADJ[column][row].name = generateAdjacentVertexName(ADJ[column], row, graphParameters);
			ADJ[column][row].weight = rand() * rand() % graphParameters.highestPossibleWeight;
			if (row != 0) ADJ[column][row].next = &ADJ[column][row - 1];
			else ADJ[column][row].next = NULL;
		}
	}
}

// Filling data in adjacency vertices last row.
void fillLastRow(std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, int resizeValue, int edgesInLastRow, 
				 GraphParameters graphParameters)
{
	int lastRowIndex = resizeValue;
	for (int column = 0; column < edgesInLastRow; column++)
	{
		ADJ[column][lastRowIndex].name = generateAdjacentVertexName(ADJ[column], lastRowIndex, graphParameters);
		ADJ[column][lastRowIndex].weight = rand() * rand() % graphParameters.highestPossibleWeight;
		ADJ[column][lastRowIndex].next = &ADJ[column][lastRowIndex - 1];
	}
}

// Randomly generates adjacent vertex. 
// If this vertex is already in vector, tries another.
// Else returns vertex name. 
unsigned long generateAdjacentVertexName(std::vector<ElementOfAdjacencyList> &currentVertexAdjacencyData, int currentElementIndex,
	GraphParameters graphParameters)
{
	// Preparing data to use lib function 'std::find'.
	std::vector<unsigned long> namesKeeper(currentVertexAdjacencyData.size());
	for (int i = 0; i < currentVertexAdjacencyData.size(); i++)
	{
		namesKeeper[i] = currentVertexAdjacencyData[i].name;
	}

	unsigned long vertexToMakeAdjacent = vertexToMakeAdjacent = rand() % graphParameters.numberOfVertices;
	while (true)
	{
		if (std::find(namesKeeper.begin(), namesKeeper.end(), vertexToMakeAdjacent) != namesKeeper.end())
		{
			vertexToMakeAdjacent++;
			if (vertexToMakeAdjacent == graphParameters.numberOfVertices) vertexToMakeAdjacent = 0;
			continue;
		}
		else return vertexToMakeAdjacent;
	}
}