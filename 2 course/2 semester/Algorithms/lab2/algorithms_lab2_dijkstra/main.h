#pragma once

#include "structuresAndConstants.h"
#include "priotityQueue.h"
#include "graphCreation.h"
#include "shortestPathFinding.h"

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
