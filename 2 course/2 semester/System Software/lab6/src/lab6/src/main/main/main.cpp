#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <thread>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

HHOOK _hook;
KBDLLHOOKSTRUCT _eventInfo;

void showErrorMessage() {
	cout << "Usage : main hook|hotkey" << endl;
}

void showHookSetupFailed() {
	cout << "Hook setting failed" << endl;
}

void showHookSetupSuccessful() {
	cout << "Hook setting done" << endl;
}

void showHookReleaseFailed() {
	cout << "Hook releasing failed" << endl;
}

void showHookReleaseSuccessful() {
	cout << "Hook releasing done" << endl;
}


void showHotkeySetupFailed() {
	cout << "Hotkey setting failed" << endl;
}

void showHotkeySetupSuccessful() {
	cout << "Hotkey setting done" << endl;
}

void showHotkeyReleaseFailed() {
	cout << "Hotkey releasing failed" << endl;
}

void showHotkeyReleaseSuccessful() {
	cout << "Hotkey releasing done" << endl;
}

void releaseHook() {
	if (UnhookWindowsHookEx(_hook)) {
		showHookReleaseSuccessful();
	}
	else {
		showHookReleaseFailed();
	}
}

LRESULT __stdcall hookCallback(int hookHandlingCode, WPARAM actionIdentifier, LPARAM eventInfo)
{
	if (hookHandlingCode >= 0)
	{
		_eventInfo = *((KBDLLHOOKSTRUCT*)eventInfo);
		if (((actionIdentifier == WM_KEYDOWN) || (actionIdentifier == WM_SYSKEYDOWN)) && (GetAsyncKeyState(160) != 0))
		{
			if (_eventInfo.vkCode == 160)
			{
				std::cout << "Entering hook mode, to exit of it, press \"esc\" button. " << std::endl;

				std::cin.ignore(100000, '\n');
	
				std::vector<char> symbols;
				std::vector<int> numberOfPresses;

				char key;
				_getch();
				
				do
				{
					key = _getch();
					if (key == 27) break;

					bool found = false;
					for (int i = 0; i < symbols.size(); i++)
					{
						if (key == symbols[i])
						{
							numberOfPresses[i]++;
							std::cout << "Symbol \"" << key << "\" was pressed " << numberOfPresses[i] <<
								" times." << std::endl;
							found = true;
							break;
						}
					}

					if (found) continue;

					symbols.push_back(key);
					numberOfPresses.push_back(1);
					std::cout << "Symbol \"" << key << "\" was pressed 1 time." << std::endl;

				} while (true);
				std::cout << "Exiting hook mode." << std::endl;
				PostQuitMessage(0);
				ofstream myfile;
				myfile.open("output.txt");
				for (int i = 0; i < symbols.size(); i++)
				{
					myfile << symbols[i] << " - " << numberOfPresses[i] << endl;
				}
				myfile.close();

			}
			else if (_eventInfo.vkCode == VK_MENU)
			{
				releaseHook();
			}
		}
	}
	return CallNextHookEx(_hook, hookHandlingCode, actionIdentifier, eventInfo);
}

void setHook() {
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, hookCallback, NULL, 0)))
	{
		showHookSetupFailed();
	}
	else
	{
		showHookSetupSuccessful();
	}
}

void registerHotKey()
{
	if (RegisterHotKey(NULL, 1, MOD_SHIFT | MOD_NOREPEAT, 'C'))
	{
		showHotkeySetupSuccessful();
	}
	else
	{
		showHotkeySetupFailed();
	}
}

int main()
{
	std::string mode;
	std::cout << "1. hook\n2. hotkey\n";
	std::cin >> mode;

	int menuItem = mode[0] - '0';

	switch (menuItem)
	{
	case 1:
		cout << "Hook selected" << endl;
		setHook();
		break;

	case 2:
		cout << "Hotkey selected" << endl;
		registerHotKey();
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			std::cout << "Entering hotkey mode, to exit of it, press \"esc\" button. " << std::endl;

			std::vector<char> symbols;
			std::vector<int> numberOfPresses;

			char key;
			do
			{
				key = _getch();
				if (key == 27) break;

				bool found = false;
				for (int i = 0; i < symbols.size(); i++)
				{
					if (key == symbols[i])
					{
						numberOfPresses[i]++;
						std::cout << "Symbol \"" << key << "\" was pressed " << numberOfPresses[i] <<
							" times." << std::endl;
						found = true;
						break;
					}
				}

				if (found) continue;
				
				symbols.push_back(key);
				numberOfPresses.push_back(1);
				std::cout << "Symbol \"" << key << "\" was pressed 1 time." << std::endl;

			} while (true);
			std::cout << "Exiting hotkey mode." << std::endl;
			PostQuitMessage(0);

			ofstream myfile;
			myfile.open("output.txt");
			for (int i = 0; i < symbols.size(); i++)
			{
				myfile << symbols[i] << " - " << numberOfPresses[i] << endl;
			}
			myfile.close();
		}
	}

	_getch();
	return 0;
}
