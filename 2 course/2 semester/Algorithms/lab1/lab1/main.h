#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

enum MenuItems
{
	INPUT = 1,
	SEARCH,
	STATS,
	EXIT
};

namespace constants
{
	const int baseSizeOfHashTable = 76;
	const int startingExtentionCoefficientOfHashTable = 32;
	const int regularExtentionCoefficientOfHashTable = 2;
	const int reserevedMemory = 1000000;

	const std::string menuRegex = "[1-4]";
	const std::string searchInputRegex = "[a-z]{1,64}";

	const int asciiCodeOfLetter_a = 97;
	const int asciiCodeOfLetter_z = 122;

	const int maxLengthOfInputWord = 64;

	const std::string noLettersInWordMarker = " ";

	const int biasForEachSymbolToBeginningOfHashTable = 97;
}

struct ElementOfHashTable
{
	std::string value;
	ElementOfHashTable* referenceToCollidedElement;
};

void showMenu();
MenuItems getAndCheckMenuItem();

void doChosenAction(bool *exit, MenuItems menuItem, std::vector<ElementOfHashTable> &hashTable,
					int* numberOfCollisions, int* numberOfElementsGivenForInput, int* numberOfSearchesMadeByUser,
					int* numberOfComparisons, bool* hashTableExists);

void inputFromFile(std::vector<ElementOfHashTable> &hashTable,
				   int* numberOfCollisions, int* numberOfElementsGivenForInput);
std::string processNewElement(std::string newElement);
void insertNewElement(std::vector<ElementOfHashTable> &hashTable, ElementOfHashTable** freePtr,
					  std::string newElement, int* numberOfCollisions, int* numberOfElementsGivenForInput);
int hashFunction(std::string element);

void searchElement(std::vector<ElementOfHashTable> &hashTable, int* numberOfComparisons);

void showStats(int* numberOfCollisions, int* numberOfElementsGivenForInput,
			   int* numberOfSearchesMadeByUser, int* numberOfComparisons);







