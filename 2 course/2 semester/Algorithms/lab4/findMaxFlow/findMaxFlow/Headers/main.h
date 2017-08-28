#pragma once

#include "structuresAndConstants.h"
#include "graphCreation.h"

#include <iostream>
#include <vector>
#include <stdio.h>

GraphParameters setGraphParameters();

MenuItems getMenuItem();

void doChosenAction(MenuItems menuItem, bool *graphCreated, bool *exit, GraphParameters *graphParameters,
	std::vector <std::vector <Edge> > &listsOfEdges);

void findMaxFlowPreparation(bool *graphCreated, GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges);
int findMaxFlow(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges);



