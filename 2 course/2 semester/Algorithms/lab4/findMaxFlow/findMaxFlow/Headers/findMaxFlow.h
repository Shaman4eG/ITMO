#pragma once

#include "structuresAndConstants.h"

void DFS(ElementOfPath currentVertex, ElementOfPath previousVertex, std::vector <std::vector <Edge> > &listsOfEdges,
	std::vector <Visitation> &visitations, std::vector <ElementOfPath> &prior, bool *pathFound, int forMinCutVersion);

std::vector<ElementOfPath> getPath(std::vector <ElementOfPath> &prior);

int findMaxFlow(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges);

int findMinFlow(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &path,
	std::vector<Edge *> &edgesInPath);