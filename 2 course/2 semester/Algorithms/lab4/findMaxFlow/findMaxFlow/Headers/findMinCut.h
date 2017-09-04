#pragma once

#include "structuresAndConstants.h"
#include "findMaxFlow.h"

void findMinCut(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges, int maxFlow, 
	std::vector<ElementOfPath> &combination);
void findCombinationsOfProbableMinCuts(std::vector <std::vector <Edge> > &listsOfEdges, GraphParameters *graphParameters,
	std::vector<ElementOfPath> &minCutPossibleEdges, int maxFlow, std::vector<ElementOfPath> &combination);
void go(int offset, int k, std::vector<ElementOfPath> &combination, std::vector<ElementOfPath> &minCutPossibleEdges,
	std::vector <std::vector <Edge> > &listsOfEdges, GraphParameters *graphParameters, int maxFlow, bool *minCutFound);
void extractEdges(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &combination,
	std::vector<int> &row, std::vector<int> &indexOfElementOfCombination);
bool preparingDFS(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges);
void restoreGraph(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &combination,
	std::vector<int> &row, std::vector<int> &indexOfElementOfCombination);