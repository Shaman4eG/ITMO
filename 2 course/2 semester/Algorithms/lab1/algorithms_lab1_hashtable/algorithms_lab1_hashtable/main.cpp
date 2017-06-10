#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "main.h"

int main()
{
	std::vector<ElementOfHashTable> hashTable;
	hashTable.reserve(constants::reserevedMemory);
	bool exit = false;
	MenuItems menuItem = EXIT;
	int numberOfCollisions = 0;
	int numberOfElementsGivenForInput = 0;
	int numberOfSearchesMadeByUser = 0;
	int numberOfComparisons = 0;
	bool hashTableExists = false;

	showMenu();
	while (!exit)
	{
		menuItem = getAndCheckMenuItem();
		doChosenAction(&exit, menuItem, hashTable, &numberOfCollisions,
			&numberOfElementsGivenForInput, &numberOfSearchesMadeByUser,
			&numberOfComparisons, &hashTableExists);
	}

	return 0;
}

void showMenu()
{
	std::cout << "1. Input from file\n2. Search\n3. Show stats\n4. Exit\n\n";
}

MenuItems getAndCheckMenuItem()
{
	std::string menuItemPrekeeper = "";
	MenuItems menuItem = EXIT;
	std::regex menuItemChecker(constants::menuRegex);

	while (true)
	{
		getline(std::cin, menuItemPrekeeper);
		bool validInput = std::regex_match(menuItemPrekeeper, menuItemChecker);

		if (!validInput)
		{
			std::cout << ("Invalid input.\n\n");
			continue;
		}
		else
		{
			menuItem = MenuItems(menuItemPrekeeper[0] - '0');
			return menuItem;
		}
	}
}



void doChosenAction(bool *exit, MenuItems menuItem, std::vector<ElementOfHashTable> &hashTable,
	int* numberOfCollisions, int* numberOfElementsGivenForInput, int* numberOfSearchesMadeByUser,
	int* numberOfComparisons, bool* hashTableExists)
{
	switch (menuItem)
	{
	case INPUT:
		inputFromFile(hashTable, numberOfCollisions, numberOfElementsGivenForInput);
		*hashTableExists = true;
		break;

	case SEARCH:
		if (*hashTableExists)
		{
			searchElement(hashTable, numberOfComparisons);
			(*numberOfSearchesMadeByUser)++;
		}
		else
		{
			std::cout << "Hash table was not created.\n\n";
		}
		break;

	case STATS:
		showStats(numberOfCollisions, numberOfElementsGivenForInput,
			numberOfSearchesMadeByUser, numberOfComparisons);
		break;

	case EXIT:
		*exit = true;
		break;
	}

}

void inputFromFile(std::vector<ElementOfHashTable> &hashTable,
	int* numberOfCollisions, int* numberOfElementsGivenForInput)
{
	hashTable.clear();
	hashTable.resize(constants::baseSizeOfHashTable * constants::startingExtentionCoefficientOfHashTable);
	ElementOfHashTable* freePtr = &hashTable[constants::baseSizeOfHashTable];
	(*numberOfCollisions) = 0;
	(*numberOfElementsGivenForInput) = 0;

	std::string fileName = "";
	std::cout << "Input file name: ";
	getline(std::cin, fileName);
	std::ifstream inf(fileName);

	if (!inf)
	{
		std::cout << "File not found or failed to open it.\n\n";
		return;
	}

	std::string newElement;
	while (inf >> newElement)
	{
		newElement = processNewElement(newElement);
		if (newElement != constants::noLettersInWordMarker)
		{
			insertNewElement(hashTable, &freePtr, newElement, numberOfCollisions, numberOfElementsGivenForInput);
		}
	}

	std::cout << "Success!\n\n";

}

std::string processNewElement(std::string newElement)
{
	std::string processedElement = "";
	processedElement.resize(constants::maxLengthOfInputWord, ' ');
	int indexToPutNewLetter = 0;

	if (newElement.size() > processedElement.size()) newElement.resize(processedElement.size());

	for (int i = 0; i < newElement.size(); i++)
	{
		newElement[i] = tolower(newElement[i]);
		if ((newElement[i] >= constants::asciiCodeOfLetter_a) &&
			(newElement[i] <= constants::asciiCodeOfLetter_z))
		{
			processedElement[indexToPutNewLetter++] = newElement[i];
		}
	}

	// No letters in word, hence do not add it to hash-table.
	if (indexToPutNewLetter == 0) return constants::noLettersInWordMarker;

	return processedElement;
}

void insertNewElement(std::vector<ElementOfHashTable> &hashTable, ElementOfHashTable** freePtr,
	std::string newElement, int* numberOfCollisions, int* numberOfElementsGivenForInput)
{
	int hashCode = hashFunction(newElement);
	ElementOfHashTable* slotPtr = &hashTable[hashCode];
	(*numberOfElementsGivenForInput)++;

	while (true)
	{
		if (newElement == slotPtr->value) return;
		else if (slotPtr->value == "")
		{
			slotPtr->value = newElement;
			break;
		}
		else if (slotPtr->referenceToCollidedElement == NULL)
		{
			slotPtr->referenceToCollidedElement = *freePtr;
			(*freePtr)->value = newElement;
			(*freePtr)++;
			(*numberOfCollisions)++;
			break;
		}
		else
		{
			slotPtr = slotPtr->referenceToCollidedElement;
			(*numberOfCollisions)++;
			continue;
		}
	}

	// Checking if hashtable is full. If it is, get control of already allocated slots.
	if ((*freePtr) == &hashTable[hashTable.size() - 1])
	{
		hashTable.resize(hashTable.size() * constants::regularExtentionCoefficientOfHashTable);
	}
}

// Sum of codes of first 3 letters.
int hashFunction(std::string element)
{
	int bias = constants::biasForEachSymbolToBeginningOfHashTable;
	int hashCode = element[0] - bias;

	for (int i = 1; i < 3; i++)
	{
		if (element[i] != ' ') hashCode += element[i] - bias;
		else break;
	}

	return hashCode;
}



void searchElement(std::vector<ElementOfHashTable> &hashTable, int* numberOfComparisons)
{
	std::string valueToSearch = "";
	std::regex wordToSearchChecker(constants::searchInputRegex);

	std::cout << "Input value to search: ";
	std::getline(std::cin, valueToSearch);

	bool validInput = std::regex_match(valueToSearch, wordToSearchChecker);
	if (!validInput)
	{
		std::cout << "Not found!\n\n";
		return;
	}

	valueToSearch.resize(constants::maxLengthOfInputWord, ' ');

	int hashCode = hashFunction(valueToSearch);
	ElementOfHashTable* slotPtr = &hashTable[hashCode];

	while (true)
	{
		(*numberOfComparisons)++;
		if (valueToSearch == slotPtr->value)
		{
			std::cout << "Found!\n\n";
			return;
		}
		else if (slotPtr->referenceToCollidedElement != NULL)
		{
			slotPtr = slotPtr->referenceToCollidedElement;
			continue;
		}
		else
		{
			std::cout << "Not found!\n\n";
			return;
		}
	}
}



void showStats(int* numberOfCollisions, int* numberOfElementsGivenForInput,
	int* numberOfSearchesMadeByUser, int* numberOfComparisons)
{
	double averageNumberOfCollisions = 0;
	double d_NumberOfCollisions = *numberOfCollisions;
	if (*numberOfElementsGivenForInput != 0)
	{
		averageNumberOfCollisions = d_NumberOfCollisions / (*numberOfElementsGivenForInput);
	}

	double averageNumberOfComparisonsMadeDuringSearch = 0;
	double d_NumberOfComparisons = *numberOfComparisons;
	if (*numberOfSearchesMadeByUser != 0)
	{
		averageNumberOfComparisonsMadeDuringSearch = d_NumberOfComparisons / (*numberOfSearchesMadeByUser);
	}

	std::cout << "Average number of collisions = " << averageNumberOfCollisions << std::endl;
	std::cout << "Average number of comaparisons made during search = " << averageNumberOfComparisonsMadeDuringSearch
		<< std::endl << std::endl;
}


