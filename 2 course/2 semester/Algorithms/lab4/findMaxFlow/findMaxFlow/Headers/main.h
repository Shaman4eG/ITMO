#pragma once

#include "structuresAndConstants.h"
#include "graphCreation.h"
#include "findMaxFlow.h"
#include "findMinCut.h"

#include <iostream>
#include <vector>
#include <stdio.h>

GraphParameters setGraphParameters();

MenuItems getMenuItem();

void doChosenAction(MenuItems menuItem, bool *graphCreated, bool *exit, GraphParameters *graphParameters,
	std::vector <std::vector <Edge> > &listsOfEdges);

void findMaxFlowAndMinCutPreparation(bool *graphCreated, GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges);

char convertVertexName(VertexName currentVertex);

