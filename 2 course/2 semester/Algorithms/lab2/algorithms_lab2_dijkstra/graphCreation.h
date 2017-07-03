#pragma once

#include "structuresAndConstants.h"

#include <vector>
#include <ctime>

void formGraph(bool *graphWasCreated, std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, GraphParameters *graphParameters);
void createVectorsForAdjacencyLists(GraphParameters graphParameters, std::vector< std::vector< ElementOfAdjacencyList > > &ADJ,
	int edgesInLastRow, int resizeValue);
void fillCompleteRows(std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, int resizeValue, GraphParameters graphParameters);
void fillLastRow(std::vector< std::vector< ElementOfAdjacencyList > > &ADJ, int resizeValue, int edgesInLastRow,
	GraphParameters graphParameters);
unsigned long generateAdjacentVertexName(std::vector<ElementOfAdjacencyList> &currentVertexAdjacencyData, int currentElementIndex,
	GraphParameters graphParameters);