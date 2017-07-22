#pragma once

#include "structuresAndConstants.h"

#include <vector>

class PriorityQueue
{
private:
	int minChild(int i, std::vector<unsigned long long> &key, int n, int d);
	int firstChild(int n, int d, int i);
	int lastChild(int n, int d, int i);
	int father(int n, int d, int i);

public:
	PriorityQueue(std::vector<unsigned int> &index, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d);

	void immerse(std::vector<unsigned int> &index, int i, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d);
	void emerge(std::vector<unsigned int> &index, int i, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int n, int d);
	void getMin(std::vector<unsigned int> &index, unsigned int *name1, unsigned long long *key1, std::vector<unsigned int> &name, std::vector<unsigned long long> &key, int *n, int d);
};