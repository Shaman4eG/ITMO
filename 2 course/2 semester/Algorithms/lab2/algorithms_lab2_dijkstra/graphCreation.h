#pragma once

#include "structuresAndConstants.h"

#include <vector>
#include <ctime>

void formGraph(bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters);
void fillCompleteRows(std::vector<ElementOfAdjacencyList*> &ADJ, int numberOfCompleteRows, GraphParameters *graphParameters);
void fillLastRow(std::vector<ElementOfAdjacencyList*> &ADJ, int edgesInLastRow, GraphParameters *graphParameters);
unsigned long generateAdjacentVertexName(ElementOfAdjacencyList *firstElementOfAdjacencyList, unsigned int numberOfVertices,
	int baseVertex);