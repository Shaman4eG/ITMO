#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <process.h>
#include <sstream>
using namespace std;

#define MAX_SEM_COUNT 2
#define MAX_LENGTH 256
CRITICAL_SECTION criticalSection;

void SaveData(std::string data);

HANDLE getSharingStartEvent(int access)
{
  HANDLE hEvent;
  if (access == 1)
  {
    hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "StartShare");
  } 
  else 
  {
    hEvent = OpenEvent(SYNCHRONIZE, FALSE, "StartShare");
  }
  if (hEvent == NULL)
  {
    cout << "creating event" << endl;
    hEvent = CreateEvent(NULL, TRUE, FALSE, "StartShare");
  }
  return hEvent;
}

HANDLE getFileMutex(){
  HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, "fileMutex");
  if (hMutex == NULL){
    hMutex = CreateMutex(NULL, FALSE, "fileMutex");
  }
  return hMutex;
}

HANDLE getDataBaseSemaphore()
{
  HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "fileMutex");
  if (hSemaphore == NULL)
  {
    hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, "getDataBaseSemaphore");
  }
  return hSemaphore;
}

int writeUser(HANDLE fileMutex, const char* fileName, string login, string password)
{
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  ofstream fout(fileName, ios_base::app);
  fout <<"$"<<login<<"/"<<password;
  fout.close();
  ReleaseMutex(fileMutex);
  return 0;
}

int passToDataBase(int championship)
{
    HANDLE hSemaphore = getDataBaseSemaphore();
    HANDLE hEvent = NULL;
    cout << "Waiting for queue..." << endl;
    DWORD dwWaitResult = WaitForSingleObject(hSemaphore, INFINITE);
    cout << "Welcome to the DataBase!" << endl;
    if (championship == 1)
    {
      hEvent = getSharingStartEvent(0);
      cout << "Waiting for starting sharing..." << endl;
      WaitForSingleObject(hEvent, INFINITE);
    }
    string word;
    string computerNum;
    srand(time(NULL));
    while (true)
	{
        if ((championship == 1) && (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0)){
          cout << "Sharing ended." << endl;
          CloseHandle(hEvent);
          break;
        }
        cout << "Type the word or num to share or type \\exit" << endl;
        getline(cin, word);
        if (word.compare("\\exit") == 0)
        {
          cout << "Thank you for using our DataBase!" << endl;
          break;
        }
		    SaveData(word);
        computerNum = rand() % 1000;
        cout << "You've shared " << word << " with me and I've shared " 
             << computerNum << " with you. We're the best team'" << endl;
    }
    ReleaseSemaphore(hSemaphore, 1, NULL);
    CloseHandle(hSemaphore);
    return 0;
}

void SaveData(std::string data)
{
	  std::cout << "Saving data..." << std::endl;
  	EnterCriticalSection(&criticalSection);
    std::cout << "Saved!" << std::endl;
  	LeaveCriticalSection(&criticalSection);
}

int checkUser(HANDLE fileMutex, const char* fileName, string login, string password)
{
  string rLogin;
  string rPassword;
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  char buff[50];
  ifstream fin(fileName);
  int stop = 2;
  int del = 1;
  int index = 0;
  char ch;
  while ((stop!=0) && fin.get(ch)) {
    //cout << ch << endl;
    if (ch == '$'){
      stop--;
      if (stop == 0){
        stop = 1;
        del = 1;
        //cout << "login : " << rLogin << endl;
        //cout << "password : " << rPassword << endl;
        //cout << "-" << rLogin << "-" << rPassword << "-" << endl;
        if ((login.compare(rLogin) == 0) && (password.compare(rPassword) == 0)) return 0;
        //cout << "login is " << login.compare(rLogin) << "password is " << password.compare(rPassword) << endl;
        rLogin.clear();
        rPassword.clear();
      }
      continue;
    }
    if (ch == '/'){
      del--;
      continue;
    }
    if ((stop == 1) && (del == 1)){
      rLogin.append(1, ch);
      continue;
    }
    if ((stop == 1) && (del == 0) && (ch != '\n')){
      rPassword.append(1, ch);
      continue;
    }
  }
  //cout << "login : " << rLogin << endl;
  //cout << "password : " << rPassword << endl;
  //cout << "-" << rLogin << "-" << rPassword << "-" << endl;
  //cout << "login is " << login.compare(rLogin) << "password is " << password.compare(rPassword) << endl;
  if ((login.compare(rLogin) == 0) && (password.compare(rPassword) == 0)) return 0;
  fin.close();
  return 1;
}

string getData(const char* message, const char* forbiddenSymbols, int maxLength)
{
  string data;
  do{
    cout << message << endl;
    getline(cin, data);
  } while ((data.find_first_of(forbiddenSymbols) != string::npos) || (data.length() > maxLength));
  return data;
}

int registerUser()
{
  HANDLE fileMutex = getFileMutex();
  string login = getData("Please, enter your login (less than or equals to 32 symbols without $ and /) and press Enter : ", "$/", 32);
  string password = getData("Please, enter your password (less than or equals to 32 symbols without $ and /) and press Enter : ", "$/", 32);
  writeUser(fileMutex,"users.txt",login,password);
  CloseHandle(fileMutex);
  return 0;
}

int admitUser(int championship)
{
  HANDLE fileMutex = getFileMutex();
  string login = getData("Please, enter your login and press Enter : ", "$/", 32);
  string password = getData("Please, enter your password and press Enter : ", "$/", 32);
  if (checkUser(fileMutex,"users.txt",login,password) == 0){
    ReleaseMutex(fileMutex);
    CloseHandle(fileMutex);
    passToDataBase(championship);
  } else {
    ReleaseMutex(fileMutex);
    CloseHandle(fileMutex);
    cout << "Invalid login or password" << endl;
  }
  return 0;
}

int StartShare()
{
  string password;
  HANDLE hEvent = getSharingStartEvent(1);
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Sharing already started" << endl;
    return 0;
  }
  do{
    cout << "Please, type password to start sharing: " << endl;
    getline(cin, password);
  } while (password.compare("hexademical") != 0);
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Sharing already started" << endl;
    return 0;
  }
  cout << "before" << endl;
  //ResetEvent(hEvent);
  SetEvent(hEvent);
  cout << "after" << endl;
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Sharing have started !" << endl;
    return 0;
  }
  CloseHandle(hEvent);
  return 0;
}

int StopShare()
{
  string password;
  HANDLE hEvent = getSharingStartEvent(1);
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Sharing already stopped" << endl;
    return 0;
  }
  do{
    cout << "Please, type password to stop sharing : " << endl;
    getline(cin, password);
  } while (password.compare("hexademical") != 0);
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Sharing already stopped" << endl;
    return 0;
  }
  cout << "before" << endl;
  //SetEvent(hEvent);
  ResetEvent(hEvent);
  cout << "after" << endl;
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Sharing have stopped !" << endl;
    return 0;
  }
  CloseHandle(hEvent);
  return 0;
}

int main()
{
  InitializeCriticalSection(&criticalSection);
  cout << "Welcome to the DataBase!" << endl;
  string word = "";
  while(true)
  {
    system("cls");
    cout << "Menu : \n - Login \n - SignIn \n - SignInSharing \n - StartShare \n - StopShare \n - Exit" << endl;
    getline(cin, word);
    if (word.compare("SignIn") == 0)
    {
      admitUser(0);
    } 
    else if (word.compare("SignInSharing") == 0)
    {
      admitUser(1);
    } 
    else if (word.compare("StartShare") == 0)
    {
      StartShare();
    } 
    else if (word.compare("StopShare") == 0)
    {
      StopShare();
    } 
    else if (word.compare("Login") == 0)
    {
      registerUser();
    } 
    else if (word.compare("Exit") == 0)
    {
      cout << "Good buy!";
      return 0;
    }
  }
}
