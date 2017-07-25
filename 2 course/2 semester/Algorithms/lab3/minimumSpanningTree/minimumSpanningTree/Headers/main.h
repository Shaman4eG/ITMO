#pragma once

#include "structuresAndConstants.h"
#include "graphCreation.h"

#include <iostream>

MenuItems getMenuItem();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters);

GraphParameters getGraphParameters();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters);