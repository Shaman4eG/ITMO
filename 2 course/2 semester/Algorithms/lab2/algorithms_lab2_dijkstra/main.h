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
#include <time.h>
#include <Windows.h>



MenuItems getMenuItem();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters, std::vector<unsigned long long> &dist, std::vector<unsigned long> &up, Timings *timings);

GraphParameters getGraphParameters();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters);

void algorithmsComparison(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long long> &dist,
	std::vector<unsigned long> &up, GraphParameters *graphParameters, Timings *timings);
void experimentWithChangingNumberOfEdges(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long long> &dist,
	std::vector<unsigned long> &up);
