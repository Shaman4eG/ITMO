#pragma once

#include "structuresAndConstants.h"

void DFS(ElementOfPath currentVertex, ElementOfPath previousVertex, std::vector <std::vector <Edge> > &listsOfEdges,
	std::vector <Visitation> &visitations, std::vector <ElementOfPath> &prior, bool *pathFound);

std::vector<ElementOfPath> getPath(std::vector <ElementOfPath> &prior);

int findMinFlow(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &path,
	std::vector<Edge *> &edgesInPath);