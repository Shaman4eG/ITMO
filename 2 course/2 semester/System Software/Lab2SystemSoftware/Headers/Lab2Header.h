#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <regex>
#include <vector>

#include <conio.h>
#include <windows.h>
#include <string.h>

//#include "../../conact/ConsoleInputHeader.h"

#define NULLTREE -1

/*  Class that describing node of the binary tree 
    with Insert, Find and Remove methods 
    and Get methods for "key"(int) and "data"(std::string) - fields. */
class TreeNode
{
    private:
        int key;
        std::string data;
        TreeNode *parent;
        TreeNode *left;
        TreeNode *right;
    public:

        // Constructor. 
        TreeNode(int _key, std::string _value)
        {
            this -> key = _key;
            this -> data = _value;
            this -> parent = NULL;
            this -> left = NULL;
            this -> right = NULL;
        }
        
        // Destructor.
        ~TreeNode()
        {
            this -> key = NULLTREE;
            this -> data = "";
            this -> parent = NULL;
            this -> left = NULL;
            this -> right = NULL;
            //delete this -> parent;
            //delete this -> left;
            //delete this -> right;
        }
        
        // Returns key's value.
        int GetKey()
        {
            return key;
        }

        void SetKey(int _key)
        {
            this -> key = _key;
            return;
        }

        // Returns data's value.
        std::string GetData()
        {
            return data;
        }

        void SetData(std::string _data)
        {
            this -> data = _data;
            return;
        }

        // Returns true if we inserted leaf to the tree, else we need to create root.
        bool Insert(TreeNode *leafToInsert)
        {
            if(this == NULL)
            {
                return false;
            }
            if(leafToInsert -> key == this -> key)
            {
                return true;
            }
            else if(leafToInsert -> key > this -> key)
            {
                if(this -> right == NULL)
                {
                    this -> right = leafToInsert;
                    leafToInsert -> parent = this;
                    return true;
                }
                else
                {
                    return this -> right -> Insert(leafToInsert);
                }
            }
            else
            {
                if(this -> left == NULL)
                {
                    this -> left = leafToInsert;
                    leafToInsert -> parent = this;
                    return true;
                }
                else
                {
                    return this -> left -> Insert(leafToInsert);
                }
            }
        }

        // Returns node's pointer or NULL.
        TreeNode* Find(int key)
        {
            if(this == NULL)
            {
                return NULL;
            }
            if(this -> key == key)
            {
                return this;
            }
            if(this -> key < key)
            {
                return this -> right -> Find(key);
            }
            else
            {
                return this -> left -> Find(key);
            }
        }

        // Removing node with out bool value that means if we found node with this key.
        bool Remove(int key)
        {
            TreeNode *nodeToRemove = this -> Find(key);
            
            // If we can't find node.
            if(nodeToRemove == NULL)
            {
                return false;
            }

            // Found and check leaves.
            if(nodeToRemove -> right == NULL)
            {
                // Node has no leaves.
                if(nodeToRemove -> left == NULL)
                {
                    // Node is root, then we placing special value in it.
                    if(nodeToRemove -> parent == NULL)
                    {
                        //nodeToRemove -> key = NULLTREE;
                        return true; 
                    }
                    else if(nodeToRemove -> parent -> left == nodeToRemove)
                    {
                        nodeToRemove -> parent -> left = NULL;
                    }
                    else
                    {
                        nodeToRemove -> parent -> right = NULL;
                    }
                }
                // Node has left child.
                else
                {
                    nodeToRemove -> left -> parent = nodeToRemove -> parent;
                    if(nodeToRemove -> parent -> left == nodeToRemove)
                    {
                        nodeToRemove -> parent -> left = nodeToRemove -> left;
                    }
                    else
                    {
                        nodeToRemove -> parent -> right = nodeToRemove -> right;
                    }
                    delete nodeToRemove;
                }
            }
            // Right leaf not null.
            else
            {
                TreeNode *rightChildMinLeaf, *leftChild;
                if(nodeToRemove -> right -> left != NULL)
                {
                    leftChild = nodeToRemove -> right -> left;
                }
                else
                {
                    nodeToRemove -> right -> parent = nodeToRemove -> parent;
                    if(nodeToRemove -> parent == NULL)
                    {
                        nodeToRemove -> key = NULLTREE;
                        return true;
                    }
                    if(nodeToRemove -> parent -> left == nodeToRemove)
                    {
                        nodeToRemove -> parent -> left = nodeToRemove -> right;
                    }
                    else
                    {
                        nodeToRemove -> parent -> right = nodeToRemove -> right;
                    }
                    delete nodeToRemove;
                    return true;
                }
                do
                {
                    if(leftChild -> left != NULL)
                    {
                        leftChild = leftChild -> left;
                    }
                }
                while(leftChild -> left != NULL);

                leftChild -> parent = nodeToRemove -> parent;
                if(nodeToRemove -> parent == NULL)
                {
                    delete nodeToRemove;
                    return true;
                }
                if(nodeToRemove -> parent -> left == nodeToRemove)
                {
                    nodeToRemove -> parent -> left = leftChild;
                }
                else
                {
                    nodeToRemove -> parent -> right = leftChild;
                }
                leftChild -> left = nodeToRemove -> left;
                leftChild -> right = nodeToRemove -> right;
            }
            nodeToRemove -> ~TreeNode();
            return true;
        }

        void ClearTree()
        {
            if(this -> left != NULL)
            {
                this -> left -> ClearTree();
            }
            if(this -> right != NULL)
            {
                this -> right -> ClearTree();
            }
            this -> Remove(this -> key);
            return;
        }

        // TODO: Remake.
        void ShowTree()
        {
            if (this == NULL)
                return;
            this -> left -> ShowTree();

            std::cout << this -> key << std::endl;
           // _tprintf(_T ("%s\n"), pNode->pData);
            this -> right -> ShowTree();

            return;
        }
};

bool FillTreeWithHeap(std::string filePath, TreeNode *root, HANDLE heapHandler);
int AddInTable(std::string buffer);
std::string WordCutter(std::string buffer);
void GenerateHashTable(std::string inputFilePath, std::string tableFilePath);
int ReHashFunc();
int HashFunc(std::string buffer);