#pragma once

#include "structuresAndConstants.h"
#include "graphCreation.h"

#include <iostream>
#include <limits>
#include <algorithm>

MenuItems getMenuItem();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
void doChosenAction(MenuItems menuItem, bool *exit, bool *graphWasCreated, std::vector<ElementOfAdjacencyList*> &ADJ,
	GraphParameters *graphParameters, std::vector<Edges> &MST);

GraphParameters getGraphParameters();
std::string checkInputValidness(std::string whatToInputPhrase, std::regex regex);
bool checkOfMutualVerticesAndEdgesAppropriateness(GraphParameters *graphParameters);

void findMST(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, std::vector<Edges> &MST);

int findLowestWeightElementInComponent(std::vector<std::vector<int> > &listsOfComponents, std::vector<ElementOfAdjacencyList*> &ADJ,
	int component, bool *firstSearch, std::vector<std::vector<Edges> > &edgesSubsets);

void findListHeaderAsNewElement(std::vector<std::vector<int> > &listsOfComponents, int workingComponent,
	std::vector<std::vector<Edges> > &edgesSubsets, int *numberOfComponents);
void findNewAndAddedElementsFromOtherComponents(std::vector<std::vector<int> > &listsOfComponents, int workingComponent,
	std::vector<std::vector<Edges> > &edgesSubsets, int workingElementIndex, int *numberOfComponents);

void addElementFromAnotherComponent(std::vector<std::vector<int> > &listsOfComponents, int nextComponent,
	int workingComponent, std::vector<std::vector<Edges> > &edgesSubsets);

void cleaningRedundantEdgeOfMST(std::vector<std::vector<Edges> > &edgesSubsets, int columnWithMST, std::vector<Edges> &MST);