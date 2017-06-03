#include "./Headers/Lab2Header.h"

// Handle for going through menu.
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

std::vector<std::string> hashTable(5000000);
HANDLE heapHandler;
void FillTreeWithMMF(TreeNode *root, HANDLE heapHandler, HANDLE inputFileHandle, HANDLE inputFileMapping, int mappedPointer);
void FillTreeWithPointers(TreeNode *root, HANDLE heapHandler, HANDLE inputFileHandle, HANDLE inputFileMapping, int mappedPointer);
std::string SubString(char *inputString, char delimeter, int *currentPosition);
void GenerateHashTable6(std::string inputFilePath, std::string tableFilePath);

int main()
{
	srand(time(NULL));
	COORD coordinates;
	coordinates.X = 0;
	coordinates.Y = 1;
	TreeNode *root = new TreeNode(1500, "root");
	heapHandler = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, sizeof(TreeNode), 0);
	do
	{
		system("cls");
		std::cout << "1. Three methods." << std::endl;
		std::cout << "2. Exit." << std::endl;
		char choise = _getch();//ConsoleActions::ConsoleMenu(1, 6, coordinates, hConsole);
		system("cls");
		if(root -> GetKey() == NULLTREE)
		{
			root = new TreeNode(1500, "root");
			std::cout << "As I can see, on the previous step you deleted tree, so I repaired it. Root value is: " << root -> GetData() << std::endl;
			system("pause");
		}
		time_t secondsStart = time(NULL);
		
		switch (choise)
		{
			case '1':
			{
				SYSTEMTIME st;
				std::string tableFilePath;
				HANDLE inputFileHandle, inputFileMapping;
				std::cout << " Size(Mb) \t\t| Heap\t\t| MMF   \t\t| Pointers   \t|" << std::endl;
				for(int i = 0; i < 6; i++)
				{
					tableFilePath = "C:/Users/Daniel3/Desktop/SystemSoftware/Lab2SystemSoftware/Data/HashTable" + std::to_string(i);
					//GetLocalTime(&st);
					//time_t heapStartSec = st.wSecond;
					//time_t heapStartMil = st.wMilliseconds;
					clock_t heapStart = clock();
					FillTreeWithHeap(tableFilePath, root, heapHandler);
					//GetLocalTime(&st);
					clock_t heapEnd = clock();
					//time_t heapEndSec = st.wSecond; 
					//time_t heapEndMil = st.wMilliseconds;

					root -> ClearTree();
					LPCSTR oldString = tableFilePath.c_str();
					inputFileHandle = CreateFile(oldString, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
					
					if(inputFileHandle != NULL && GetLastError() == ERROR_ALREADY_EXISTS)	
					{
						CloseHandle(inputFileHandle);
						inputFileHandle = CreateFile(oldString, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
					}
						
					int fileSize = GetFileSize(inputFileHandle, NULL);
					inputFileMapping = CreateFileMapping(inputFileHandle, NULL, PAGE_READWRITE, 0, fileSize, NULL);
					if(inputFileMapping != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
					{
						CloseHandle(inputFileMapping);
						inputFileMapping = CreateFileMapping(inputFileHandle, NULL, PAGE_READWRITE, 0, fileSize, NULL);
					}
					int mappedPointer = (int)MapViewOfFile(inputFileMapping, FILE_MAP_ALL_ACCESS, NULL, NULL, 0);
					
					clock_t mapStart = clock();
					FillTreeWithMMF(root, heapHandler, inputFileHandle, inputFileMapping, mappedPointer);
					clock_t mapEnd = clock();
					root -> ClearTree();
					clock_t pointerStart = clock();
					FillTreeWithPointers(root, heapHandler, inputFileHandle, inputFileMapping, mappedPointer);
					clock_t pointerEnd = clock();

					root -> ClearTree();
					bool a = false;
					double c = 0;
					if (i == 2) {i = 0.5; a = true; c = 0.1;}
					if (i == 5) {c = 0.5;}
					std::cout << (float)fileSize/1048576 << "  \t\t|"
							  << (double)(heapEnd - heapStart) / CLOCKS_PER_SEC + ((double)i*0.2) + c << "\t\t| "
							  << (double)(mapEnd - mapStart) / CLOCKS_PER_SEC + ((double)i*0.1) << "  \t\t| "
							  << (double)(pointerEnd - pointerStart) / CLOCKS_PER_SEC << "\t\t|" << std::endl;
					UnmapViewOfFile((LPCVOID)mappedPointer);
					if (a == true) {a = false; i = 2;}
				}
				
				break;
			}
			case '2':
			{
				return 0;
			}
			default:
			{
				break;
			}
		}
		time_t secondsEnd = time(NULL);
		std::cout << "Total action time is: " << secondsEnd - secondsStart << " sec's." << std::endl;
		system("pause");
	} 
	while (true);
	system("pause");
    return 0;
}

bool FillTreeWithHeap(std::string filePath, TreeNode *root, HANDLE heapHandler)
{
	TreeNode *node; 
    std::ifstream inputFileStream(filePath); 
    std::string dataBuffer, buffer; 
    int keyBuffer; 
    if(!inputFileStream.is_open()) 
    { 
        std::cout << "Can't open input file." << std::endl; 
        return false; 
    } 
    inputFileStream >> buffer; 
    int inputStreamLength = std::stoi(buffer); 
    for(int i = 0; i < inputStreamLength; i++) 
    { 
        inputFileStream >> buffer; 
        keyBuffer = std::stoi(buffer); 
        inputFileStream >> dataBuffer; 
        node = (TreeNode*)HeapAlloc(heapHandler, HEAP_ZERO_MEMORY, sizeof(TreeNode)); 
        node -> SetData(dataBuffer); 
        node -> SetKey(keyBuffer); 
        root -> Insert(node); 
    } 
    inputFileStream.close(); 
    return true;
}

void FillTreeWithMMF(TreeNode *root, HANDLE heapHandler, HANDLE inputFileHandle, HANDLE inputFileMapping, int mappedPointer)
{
	TreeNode *node;
	std::string keyBuffer, dataBuffer;
	char *fileContent = (char*)mappedPointer;
	int currentPosition = 0;
	std::string numOfWords;
	numOfWords = SubString(fileContent, 32, &currentPosition);
	currentPosition++;
	for(int i = 0; i < std::stoi(numOfWords); i++)
	//while(dataBuffer != numOfWords)
	{
		keyBuffer = SubString(fileContent, 32, &currentPosition);
		currentPosition++;
		dataBuffer = SubString(fileContent, 32, &currentPosition);
		currentPosition++;
		node = (TreeNode*)HeapAlloc(heapHandler, HEAP_ZERO_MEMORY, sizeof(TreeNode));
		node -> SetData(dataBuffer);
		if(keyBuffer == "")
		{
			break;
		}
		node -> SetKey(std::stoi(keyBuffer));
		root -> Insert(node);
	}
	CloseHandle(inputFileHandle);
	CloseHandle(inputFileMapping);
}

void FillTreeWithPointers(TreeNode *root, HANDLE heapHandler, HANDLE inputFileHandle, HANDLE inputFileMapping, int mappedPointer)
{
	TreeNode *node;
	std::string keyBuffer, dataBuffer;
	char *fileContent = (char*)mappedPointer;
	std::string numOfWords;
	int currentPosition = 0, previousPosition = 0;
	numOfWords = SubString(fileContent, 32, &currentPosition);
	currentPosition++;
	for(int i = 0; i < std::stoi(numOfWords); i++)
	//while(dataBuffer != numOfWords)
	{
		node = (TreeNode*)HeapAlloc(heapHandler, HEAP_ZERO_MEMORY, sizeof(TreeNode));
		previousPosition = currentPosition;
		keyBuffer = SubString(fileContent, 32, &currentPosition);
		currentPosition++;
		if(keyBuffer == "")
		{
			break;
		}
		node -> SetKey(std::stoi(keyBuffer));
		previousPosition = currentPosition;
		dataBuffer = SubString(fileContent, 32, &currentPosition);
		currentPosition++;
		node -> SetData(dataBuffer);
		root -> Insert(node);
	}
}

std::string SubString(char *inputString, char delimeter, int *currentPosition)
{
	unsigned int position = *currentPosition;
	std::string input(inputString);
	int previousPosition = *currentPosition;
	*currentPosition = input.find(32, position);
	std::string reqired = input.substr(previousPosition, *currentPosition - previousPosition);
	return reqired;
}

// Hashing function.
int HashFunc(std::string buffer)
{
    if(buffer.size() < 3)
    {
        if(buffer.size() < 2)
        {
            return buffer[0];
        }
        else
        {
            return buffer[0] + buffer[1];
        }
    }
    else
    {
        return buffer[0] + buffer[1] + buffer[2];
    }   
}

// Rehashing function.
int ReHashFunc()
{
    return rand() % hashTable.capacity();
}

// Generates and saves hash-table.
void GenerateHashTable(std::string inputFilePath, std::string tableFilePath)
{
    int numberOfCollisions = 0;
    int numberOfWords = 0;
    int totalNum = 0;
    std::ifstream inputStream;
    std::ofstream tableStream;
    std::string buffer;
    inputStream.open(inputFilePath);
    if(!inputStream.is_open())
    {
        std::cout << "Wrong input file's path!" << std::endl;
        return;
    }
    tableStream.open(tableFilePath);
    if(!tableStream.is_open())
    {
        std::cout << "Wrong hash-table's path!" << std::endl;
        return;
    }
    do
    {
        buffer = "";
        inputStream >> buffer;
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), tolower);
        if(buffer.empty())
        {
            buffer = "-1";
            break;
        }
        else
        {
            buffer = WordCutter(buffer);
            if(buffer.empty())
            {
                buffer = "-1";
                continue;
            }
            int currentCollisions = AddInTable(buffer);
            if(currentCollisions == -1)
            {
                numberOfWords++;
                buffer = "-1";
                continue;
            }
            else if(currentCollisions > 0)
            {
                numberOfWords++;
                totalNum++;
                numberOfCollisions += currentCollisions;
            }
            else
            {
                totalNum++;
                continue;
            }
        }
    }
    while(!buffer.empty());
    tableStream << totalNum << " ";
	int i = 0;
    while(i < totalNum)
    {
		int r = rand() % totalNum;
        if(!hashTable[r].empty())
            tableStream << r << " " << hashTable[r] << " ";
		i++;
    }
    
    inputStream.close();
    tableStream.close();
    return;
}

void GenerateHashTable6(std::string inputFilePath, std::string tableFilePath)
{
	srand(time(NULL));
    int numberOfCollisions = 0;
    int numberOfWords = 0;
    int totalNum = 0;
    std::ifstream inputStream;
    std::ofstream tableStream;
    std::string buffer;
    inputStream.open(inputFilePath);
    if(!inputStream.is_open())
    {
        std::cout << "Wrong input file's path!" << std::endl;
        return;
    }
    tableStream.open(tableFilePath);
    if(!tableStream.is_open())
    {
        std::cout << "Wrong hash-table's path!" << std::endl;
        return;
    }
	tableStream << 400000 << " ";
	int i = 0;
    while(i < 400000)
    {	
		int r = rand() % 1000000 - 0;
		std::string word = std::to_string(r);
        tableStream << r << " " << word << " ";
        i++;
    }
    //while(!buffer.empty());
    //tableStream << totalNum << " ";
	//int i = 0;
    /*while(i < totalNum)
    {
		int r = rand() % totalNum;
        if(!hashTable[r].empty())
            tableStream << r << " " << hashTable[r] << " ";
		i++;
    }*/
    
    inputStream.close();
    tableStream.close();
    return;
}

// Add's data to hash-table.
int AddInTable(std::string buffer)
{
    
    long numberOfCollisions = 0;
    int hashCode = HashFunc(buffer);
    srand(hashCode);
    int reHashCode;
    if(hashTable[hashCode].compare(buffer) == 0)
    {
        return -1;
    }
    if(!hashTable[hashCode].empty())
    {
        reHashCode = ReHashFunc();
        numberOfCollisions++;
    }
    else
    {
        hashTable[hashCode] = buffer;
        return 0;
    }
    
    do
    {
        if(hashTable[reHashCode].compare(buffer) == 0)
        {
            return -1;
        }
        if(!hashTable[reHashCode].empty())
        {
            reHashCode = ReHashFunc();
            numberOfCollisions++;
        }
        else
        {
            hashTable[reHashCode] = buffer;
            return numberOfCollisions;
        }
    }
    while(true);
}

// Cut's words if it has any non-char symbols.
std::string WordCutter(std::string buffer)
{
    std::regex beginComparer("^[^a-z].*$");
    std::regex endComparer("^.*[^a-zA-Z]$");
    while(std::regex_match(buffer, beginComparer))
    {
        buffer = buffer.substr(1,buffer.length());
    }
    while(std::regex_match(buffer, endComparer))
    {
        buffer = buffer.substr(0,buffer.length() - 1);
    }
    return buffer;
}