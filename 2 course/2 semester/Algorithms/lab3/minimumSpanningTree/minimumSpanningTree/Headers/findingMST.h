#include "structuresAndConstants.h"
#include <queue>
#include <functional>

// To compare two edges.
class myComparator
{
public:
	int operator() (const Edges &edge1, const Edges &edge2)
	{
		return edge1.weight > edge2.weight;
	}
};

void findMST(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, std::vector<Edges> &MST, Timings *timings);

// BORUVKA
void boruvka(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, std::vector<Edges> &MST);

int findLowestWeightElementInComponent(std::vector<std::vector<int> > &listsOfComponents, std::vector<ElementOfAdjacencyList*> &ADJ,
	int component, bool *firstSearch, std::vector<std::vector<Edges> > &edgesSubsets);

void findListHeaderAsNewElement(std::vector<std::vector<int> > &listsOfComponents, int workingComponent,
	std::vector<std::vector<Edges> > &edgesSubsets, int *numberOfComponents);
void findNewAndAddedElementsFromOtherComponents(std::vector<std::vector<int> > &listsOfComponents, int workingComponent,
	std::vector<std::vector<Edges> > &edgesSubsets, int workingElementIndex, int *numberOfComponents);

void addElementFromAnotherComponent(std::vector<std::vector<int> > &listsOfComponents, int nextComponent,
	int workingComponent, std::vector<std::vector<Edges> > &edgesSubsets);

void cleaningRedundantEdgeOfMST(std::vector<std::vector<Edges> > &edgesSubsets, int columnWithMST, std::vector<Edges> &MST);


// KRUSKAL
void kruskal(std::vector<ElementOfAdjacencyList*> &ADJ, GraphParameters *graphParameters, std::vector<Edges> &MST);
void createPriorityQueueOfEdges(std::priority_queue <Edges, std::vector<Edges>, myComparator > &sortedEdges,
	std::vector<ElementOfAdjacencyList*> &ADJ);
void formingMST(std::priority_queue <Edges, std::vector<Edges>, myComparator > sortedEdges, GraphParameters *graphParameters,
	std::vector<Edges> &MST);