#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <thread>
#include "stdafx.h"
#include <conio.h>
#include <string>

#pragma comment( lib, "user32.lib")
#pragma comment( lib, "gdi32.lib")

using namespace std;

HHOOK _hook;
KBDLLHOOKSTRUCT _eventInfo;

void showErrorMessage(){
  cout << "Usage : main hook|hotkey" << endl;
}

void showHookSetupFailed(){
  cout << "Hook setting failed" << endl;
}

void showHookSetupSuccessful(){
  cout << "Hook setting done" << endl;
}

void showHookReleaseFailed(){
  cout << "Hook releasing failed" << endl;
}

void showHookReleaseSuccessful(){
  cout << "Hook releasing done" << endl;
}


void showHotkeySetupFailed(){
  cout << "Hotkey setting failed" << endl;
}

void showHotkeySetupSuccessful(){
  cout << "Hotkey setting done" << endl;
}

void showHotkeyReleaseFailed(){
  cout << "Hotkey releasing failed" << endl;
}

void showHotkeyReleaseSuccessful(){
  cout << "Hotkey releasing done" << endl;
}

void releaseHook(){
  if (UnhookWindowsHookEx(_hook)){
      showHookReleaseSuccessful();
  } else {
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
        std::cout << "Entering hook mode, to exit of it, press\"esc\" button. " << std::endl;
        int key = 0;
        do
        {
          key = _getch();
          std::cout << "Code of pressed button \"" << (char)key <<"\" is: " << key << std::endl;
        } while (key != 27);
        std::cout << "Exiting hook mode." << std::endl;

      } 
      else if (_eventInfo.vkCode == VK_MENU)
      {
        releaseHook();
      }
    }
  }
  return CallNextHookEx(_hook,hookHandlingCode,actionIdentifier,eventInfo);
}

void setHook(){
  if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, hookCallback, NULL, 0)))
  {
      showHookSetupFailed();
  } else 
  {
      showHookSetupSuccessful();
  }
}

void registerHotKey()
{
  if (RegisterHotKey(NULL,1,MOD_SHIFT | MOD_NOREPEAT,0))
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
  std::cout << "Enter type of work(hook/hotkey): ";
  std::cin >> mode;

  setlocale(LC_ALL,"Russian");
  if (mode.compare(0, mode.length(), "hook", 0, sizeof("hook")) == 0)
  {
    cout << "Hook selected" << endl;
    setHook();
  } 
  else if (mode.compare(0, mode.length(), "hotkey", 0, sizeof("hotkey")) == 0)
  {
    cout << "Hotkey selected" << endl;
    registerHotKey();
  } 
  else 
  {
    showErrorMessage();
    return 1;
  }

  MSG msg;
  while(GetMessage(&msg, NULL, 0, 0))
  {
    if (msg.message == WM_HOTKEY)
    {
        std::cout << "Entering hotkey mode, to exit of it, press\"esc\" button. " << std::endl;
        int key = 0;
        do
        {
          key = _getch();
          std::cout << "Code of pressed button \"" << (char)key <<"\" is: " << key << std::endl;
        } while (key != 27);
        std::cout << "Exiting hotkey mode." << std::endl;

    }
  }
  return 0;
}
