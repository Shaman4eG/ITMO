#include "priotityQueue.h"


PriorityQueue::PriorityQueue( std::vector<unsigned int> &index, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d)
{
	for (int i = n; i > 0; i--) immerse(index, i, name, key, n, d);
}

void PriorityQueue::immerse(std::vector<unsigned int> &index, int i, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d)
{
	unsigned long long key0 = key[i];
	unsigned int name0 = name[i];
	int c = minChild(i, key, n, d);

	while ((c != i) && (key0 > key[c]))
	{
		key[i] = key[c];
		name[i] = name[c];
		index[name[i]] = i;
		i = c;
		c = minChild(i, key, n, d);
	}

	key[i] = key0; 
	name[i] = name0;
	index[name[i]] = i;
}

void PriorityQueue::emerge(std::vector<unsigned int> &index, int i, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d)
{
	unsigned long long key0 = key[i];
	unsigned int name0 = name[i];
	int p = father(n, d, i);
	
	while ((i != 1) && (key[p] > key0))
	{
		key[i] = key[p];
		name[i] = name[p];
		index[name[i]] = i;
		i = p;
		p = father(n, d, i);
	}

	key[i] = key0;
	name[i] = name0;
	index[name[i]] = i;
}

int PriorityQueue::minChild(int i, std::vector<unsigned long long> &key, int n, int d)
{
	int kf = firstChild(n, d, i);
	int minChild = 0;
	if (kf == 0) minChild = i;
	else
	{
		int kl = lastChild(n, d, i);
		unsigned long minKey = key[kf];
		minChild = kf;

		for (int j = kf + 1; j <= kl; j++)
		{
			if (key[j] < minKey)
			{
				minKey = key[j];
				minChild = j;
			}
		}
	}

	return minChild;
}

int PriorityQueue::firstChild(int n, int d, int i)
{
	int k = (i - 1) * d + 2;
	if (k > n) return 0;
	else return k;
}

int PriorityQueue::lastChild(int n, int d, int i)
{
	int k = firstChild(n, d, i);
	if (k == 0) return 0;
	else if (k + d - 1 < n) return k + d - 1;
	else return n;
}

int PriorityQueue::father(int n, int d, int i)
{
	return ((i - 2) / d) + 1;
}



void PriorityQueue::getMin(std::vector<unsigned int> &index, unsigned int *name1, unsigned long long *key1, std::vector<unsigned int> &name,
	std::vector<unsigned long long> &key, int *n, int d)
{
	*name1 = name[1];
	*key1 = key[1];

	name[1] = name[*n];
	key[1] = key[*n];

	name[*n] = *name1;
	key[*n] = *key1;

	index[*name1] = *n;
	(*n)--;
	if (*n > 1) immerse(index, 1, name, key, *n, d);
}
