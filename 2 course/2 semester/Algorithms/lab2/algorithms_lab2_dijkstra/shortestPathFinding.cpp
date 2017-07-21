#include "shortestPathFinding.h"

// Finds shortest path in graph using Dijkstra's algorithm with d-heap priority queue.
void ldgDijkstraDHeap(std::vector<ElementOfAdjacencyList*> &ADJ, std::vector<unsigned long long> &dist,
	std::vector<unsigned long> &up, GraphParameters *graphParameters)
{
	up.resize(graphParameters->numberOfVertices + 1);
	dist.resize(graphParameters->numberOfVertices + 1);

	// Array of vertices' names. Name of vertex equals its index.
	std::vector<unsigned int> name(graphParameters->numberOfVertices + 1);
	// Represents current estimation of distance from vertex 's' to vertex 'name[i]'.
	std::vector<unsigned long long> key(graphParameters->numberOfVertices + 1);
	// Represents names' indices. Is supposed to be correct at that: index[name[i]] = i
	std::vector<unsigned int> index(graphParameters->numberOfVertices + 1);

	// Initializing data keepers.
	for (int i = 1; i <= graphParameters->numberOfVertices; i++)
	{
		up[i] = 0;
		dist[i] = ULLONG_MAX;
		index[i] = i;
		name[i] = i;
		key[i] = ULLONG_MAX;
	}

	key[graphParameters->startingVertex] = 0;
	int nq = graphParameters->numberOfVertices;
	PriorityQueue priorityQueue(index, name, key, nq, graphParameters->d);
	unsigned int name1 = name[1];
	unsigned long long key1 = key[1];

	while (nq > 0)
	{
		priorityQueue.getMin(index, &name1, &key1, name, key, &nq, graphParameters->d);
		int i = name1;
		dist[i] = key1;
		ElementOfAdjacencyList *p = ADJ[i];
		while (p != NULL)
		{
			unsigned int j = p->name;
			unsigned int jq = index[j];
			if (dist[i] != ULLONG_MAX)
			{
				if (key[jq] > dist[i] + p->weight)
				{
					key[jq] = dist[i] + p->weight;
					priorityQueue.emerge(index, jq, name, key, nq, graphParameters->d);
					up[j] = i;
				}
			}
			p = p->next;
		}
	}
}