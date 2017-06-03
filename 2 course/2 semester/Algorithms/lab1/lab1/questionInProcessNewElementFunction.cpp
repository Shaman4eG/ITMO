#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "main.h"

void doChosenAction(bool *exit, MenuItems menuItem, bool *needClear);

void showMenu()
{
	std::cout << "1. Input from file\n2. Search\n3. Show stats\n4. Exit\n\n";
}

MenuItems getMenuItemAndCheckValidity()
{
	std::string menuItemPrekeeper;
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

std::string processNewElement(std::string newElement)
{
	std::string processedElement = "";
	int indexToPutNewLetter = 0;

	for (int i = 0; i < newElement.size(); i++)
	{
		if ((newElement[i] >= constants::AsciiCodeOfLetter_A) &&
			(newElement[i] <= constants::AsciiCodeOfLetter_z))
		{
			processedElement[indexToPutNewLetter++] = tolower(newElement[i]);
		}
	}
	std::cout << processedElement << std::endl;

	return processedElement;
}

void inputFromFile(bool *needClear)
{
	// CHANGE TO NOT HARD NAME
	std::string fileName = "input.txt";

	//std::cout << "Input file name: ";
	//getline(std::cin, fileName);
	std::ifstream inf(fileName);

	if (!inf)
	{
		std::cout << "File not found or failed to open it.\n\n";
		*needClear = false;
		return;
	}

	std::string newElement;
	while (inf >> newElement)
	{
		newElement = processNewElement(newElement);
		//insertNewElement();
	}
}

void doChosenAction(bool *exit, MenuItems menuItem, bool *needClear)
{
	switch (menuItem)
	{
	case INPUT:
		inputFromFile(needClear);
		break;

	case SEARCH:
		//search();
		break;

	case STATS:
		//showStats();
		break;

	case EXIT:
		*exit = true;
		break;
	}

}

int main()
{
	std::vector<ElementOfHashTable> hashTable(constants::baseSizeOfHashTable * constants::startingExtentionCoefficientOfHashTable);
	ElementOfHashTable* freePtr = &hashTable[constants::baseSizeOfHashTable];

	bool exit = false;
	MenuItems menuItem = EXIT;
	bool needClear = true;

	while (!exit)
	{
		if (needClear)
		{
			system("cls");
			showMenu();
		}
		else needClear = true;
		menuItem = getMenuItemAndCheckValidity();
		doChosenAction(&exit, menuItem, &needClear);
	}

	return 0;
}

