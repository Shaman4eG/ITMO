#include "priotityQueue.h"


PriorityQueue::PriorityQueue( std::vector<unsigned int> &index, std::vector<unsigned int> &name, std::vector<unsigned long> &key, int n, int d)
{
	for (int i = n; i > 0; i--) immerse(index, i, name, key, n, d);
}

void PriorityQueue::immerse(std::vector<unsigned int> &index, int i, std::vector<unsigned int> &name, std::vector<unsigned long> &key, int n, int d)
{
	unsigned int key0 = key[i];
	int name0 = name[i];
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

int PriorityQueue::minChild(int i, std::vector<unsigned long> &key, int n, int d)
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
	else return k + d - 1;
}
