#include "../Headers/findMinCut.h"

void findMinCut(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges, int maxFlow,
	std::vector<ElementOfPath> &combination)
{
	// All edges, whiches flows are filled (equal to capacity).
	std::vector<ElementOfPath> minCutPossibleEdges;
	for (int i = 1; i < listsOfEdges.size(); i++)
	{
		for (int j = 0; j < listsOfEdges[i].size(); j++)
		{
			if (listsOfEdges[i][j].capacity != 0)
			{
				if (listsOfEdges[i][j].flow == listsOfEdges[i][j].capacity)
				{
					ElementOfPath elementToAdd;
					elementToAdd.capacity = listsOfEdges[i][j].capacity;
					elementToAdd.from = (VertexName)i;
					elementToAdd.thisVertex = listsOfEdges[i][j].vertex;
					minCutPossibleEdges.push_back(elementToAdd);
				}
			}
		}
	}

	findCombinationsOfProbableMinCuts(listsOfEdges, graphParameters, minCutPossibleEdges, maxFlow, combination);
}

void findCombinationsOfProbableMinCuts(std::vector <std::vector <Edge> > &listsOfEdges, GraphParameters *graphParameters,
	std::vector<ElementOfPath> &minCutPossibleEdges, int maxFlow, std::vector<ElementOfPath> &combination)
{
	bool minCutFound = false;
	for (int k = 1; k <= minCutPossibleEdges.size(); k++)
	{
		go(0, k, combination, minCutPossibleEdges, listsOfEdges, graphParameters, maxFlow, &minCutFound);
		if (minCutFound) break;
		combination.clear();
	}
}

void go(int offset, int k, std::vector<ElementOfPath> &combination, std::vector<ElementOfPath> &minCutPossibleEdges,
	std::vector <std::vector <Edge> > &listsOfEdges, GraphParameters *graphParameters, int maxFlow, bool *minCutFound)
{
	if (k == 0)
	{
		// Used for fast return of edges.
		std::vector<int> row;
		std::vector<int> indexOfElementOfCombination;

		extractEdges(listsOfEdges, combination, row, indexOfElementOfCombination);

		// Looking for a way from start to finish. If there is none - compare min cut value to found max flow.
		// If they are equal - minimum cut edges are found.
		bool pathFound = preparingDFS(graphParameters, listsOfEdges);
		restoreGraph(listsOfEdges, combination, row, indexOfElementOfCombination);
		if (pathFound) return;

		// Count min cut.
		int minCut = 0;
		for (int i = 0; i < combination.size(); i++) minCut += combination[i].capacity;

		if (minCut == maxFlow) *minCutFound = true;

		return;
	}

	for (int i = offset; i <= minCutPossibleEdges.size() - k; ++i)
	{
		combination.push_back(minCutPossibleEdges[i]);
		go(i + 1, k - 1, combination, minCutPossibleEdges, listsOfEdges, graphParameters, maxFlow, minCutFound);
		if (*minCutFound) return;
		combination.pop_back();
	}
}

void extractEdges(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &combination,
	std::vector<int> &row, std::vector<int> &indexOfElementOfCombination)
{
	for (int i = 1; i < listsOfEdges.size(); i++)
	{
		for (int j = 0; j < listsOfEdges[i].size(); j++)
		{
			for (int z = 0; z < combination.size(); z++)
			{
				if ((combination[z].from == i) &&
					(combination[z].thisVertex == listsOfEdges[i][j].vertex) &&
					(combination[z].capacity == listsOfEdges[i][j].capacity))
				{
					listsOfEdges[i][j].capacity = 0;
					listsOfEdges[i][j].flow = 0;
					row.push_back(j);
					indexOfElementOfCombination.push_back(z);
				}
			}
		}
	}
}

bool preparingDFS(GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges)
{
	// Keeps information about visited vertices of graph. Used in DFS algorithm.
	std::vector<Visitation> visitations(graphParameters->numberOfVertices + 1, UNVISITED);

	// Keeps unfinished paths found during DFS, including one completed.
	std::vector<ElementOfPath> prior;

	bool pathFound = false;
	// A is first vertex in variant 3. It does not have parent, so second parameter is empty edge.
	ElementOfPath emptyEdge;
	ElementOfPath firstEdge;
	firstEdge.thisVertex = A;
	DFS(firstEdge, emptyEdge, listsOfEdges, visitations, prior, &pathFound, 1);

	return pathFound;
}

void restoreGraph(std::vector <std::vector <Edge> > &listsOfEdges, std::vector<ElementOfPath> &combination,
	std::vector<int> &row, std::vector<int> &indexOfElementOfCombination)
{
	for (int i = 0; i < row.size(); i++)
	{
		Edge returningEdge;
		returningEdge.capacity = combination[indexOfElementOfCombination[i]].capacity;
		returningEdge.flow = combination[indexOfElementOfCombination[i]].capacity;
		returningEdge.vertex = combination[indexOfElementOfCombination[i]].thisVertex;
		listsOfEdges[combination[indexOfElementOfCombination[i]].from][row[i]] = returningEdge;
	}
}