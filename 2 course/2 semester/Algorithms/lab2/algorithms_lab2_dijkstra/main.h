#pragma once

#include "priotityQueue.h"
#include "structuresAndConstants.h"
#include "graphCreation.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <math.h>
#include <algorithm>
#include <climits>



void showMenu();
MenuItems getAndCheckMenuItem();
void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters, std::vector<unsigned long> &dist, std::vector<unsigned long> &up);

GraphParameters getGraphParameters();

void findingShortestPath(bool *graphWasCreated, std::vector<unsigned long> &dist, std::vector<unsigned long> &up,
	std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters);
void ldgDijkstraDHeap(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long> &dist,
	std::vector<unsigned long> &up, GraphParameters *graphParameters);
