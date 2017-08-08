#pragma once

#include "structuresAndConstants.h"
#include "graphCreation.h"
#include "findingMST.h"

#include <iostream>
#include <limits>
#include <algorithm>
#include <fstream>  

MenuItems getMenuItem();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters, std::vector<Edges> &MST);

bool experiment(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<Edges> &MST, bool *graphWasCreated);
void doExperiment(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<Edges> &MST, std::vector<double> &timingsOfA,
	std::vector<double> &timingsOfB, GraphParameters *graphParameters, bool *graphWasCreated, Timings *timings,
	std::vector<long> &numberOfEdges);

GraphParameters getGraphParameters();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters);


