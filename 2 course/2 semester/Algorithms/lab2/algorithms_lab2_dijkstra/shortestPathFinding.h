#pragma once

#include "structuresAndConstants.h"
#include "priotityQueue.h"

void ldgDijkstraDHeap(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long> &dist,
	std::vector<unsigned long> &up, GraphParameters *graphParameters);