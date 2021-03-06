#pragma once

#include "structuresAndConstants.h"

#include <vector>
#include <ctime>

void formGraph(bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters,
	std::vector<Edges> &MST);

void clearAdjacencyLists(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters);

void fillAdjacencyLists(std::vector<ElementOfAdjacencyList*> &ADJ, int numberOfCompleteRows, GraphParameters *graphParameters,
	int lastColumnWithExtraElement, int numberOfEdgesLeft);
void firstRowSpecialFilling(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, int *numberOfEdgesLeft);
void addNewElement(std::vector<ElementOfAdjacencyList*> &ADJ, int column, GraphParameters *graphParameters);
void addReflectionElement(std::vector<ElementOfAdjacencyList*> &ADJ, int column, GraphParameters *graphParameters,
	ElementOfAdjacencyList *newElem, int callerVertexName);

unsigned long generateAdjacentVertexName(ElementOfAdjacencyList *firstElementOfAdjacencyList, unsigned int numberOfVertices,
	int baseVertex);
unsigned long generateWeight(GraphParameters *graphParameters);