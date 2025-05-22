#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include "PriorityQueue.hpp"
#include <fstream>

using namespace std;

struct node
{
	string characterName;
    PriorityQ pq;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    
    node* createNode(string charName, node* next);
    
    int numCollision;
public:
    HashTable(int bsize);  // Constructor
    
    void buildBulk(string fname);
    
    void insertItem(ItemInfo item);

    
    unsigned int hashFunction(string key);

    int getNumCollision(){return numCollision;};
    

    node* searchCharacter(string character);
    
    void printTable();

	void deleteEntry(string characterName, string itemName);
    
    
};

#endif
