#include "../Headers/graphCreation.h"

// Creates graph according to 3rd variant.
void createGraph(bool *graphCreated, GraphParameters *graphParameters, std::vector <std::vector <Edge> > &listsOfEdges)
{
	listsOfEdges.clear();
	listsOfEdges.resize(graphParameters->numberOfVertices, std::vector <Edge>());

	listsOfEdges[A].push_back(createNewEdge(B, FORWARD, graphParameters));
	listsOfEdges[A].push_back(createNewEdge(C, FORWARD, graphParameters));
	listsOfEdges[A].push_back(createNewEdge(F, FORWARD, graphParameters));

	listsOfEdges[B].push_back(createNewEdge(C, FORWARD, graphParameters));
	listsOfEdges[B].push_back(createNewEdge(D, FORWARD, graphParameters));
	listsOfEdges[B].push_back(createNewEdge(D, BACKWARD, graphParameters));

	listsOfEdges[C].push_back(createNewEdge(B, BACKWARD, graphParameters));
	listsOfEdges[C].push_back(createNewEdge(E, FORWARD, graphParameters));
	listsOfEdges[C].push_back(createNewEdge(E, BACKWARD, graphParameters));

	listsOfEdges[D].push_back(createNewEdge(B, FORWARD, graphParameters));
	listsOfEdges[D].push_back(createNewEdge(B, BACKWARD, graphParameters));
	listsOfEdges[D].push_back(createNewEdge(E, BACKWARD, graphParameters));
	listsOfEdges[D].push_back(createNewEdge(F, FORWARD, graphParameters));

	listsOfEdges[E].push_back(createNewEdge(C, FORWARD, graphParameters));
	listsOfEdges[E].push_back(createNewEdge(C, BACKWARD, graphParameters));
	listsOfEdges[E].push_back(createNewEdge(D, FORWARD, graphParameters));
	listsOfEdges[E].push_back(createNewEdge(F, FORWARD, graphParameters));

	*graphCreated = true;
}

// To distinguish forward and backward edges later, during main algorithm execution,
// we use capacity. If it equals 0 - edge is backward.
Edge createNewEdge(VertexName vertex, Direction direction, GraphParameters *graphParameters)
{
	Edge newEdge;
	newEdge.vertex = vertex;
	if (direction == BACKWARD) newEdge.capacity = 0;
	else newEdge.capacity = rand() % graphParameters->highestPossibleWeight + graphParameters->lowestPossibleWeight;

	return newEdge;
}