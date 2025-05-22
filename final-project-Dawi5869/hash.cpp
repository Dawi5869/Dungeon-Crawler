// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include<sstream>


using namespace std;


node* HashTable::createNode(string charName, node* nextNode)
{
	node* newNode = new node;

    newNode->characterName = charName;
    
    newNode->next = nextNode;

    return newNode;
}


HashTable::HashTable(int bsize)
{
	tableSize = bsize;

    table = new node*[tableSize];

    for (int i = 0; i < tableSize; i++)
	{
        table[i] = nullptr;
	}

    numCollision = 0;
}


void HashTable::printTable()
{

	for (int i = 0; i < tableSize; i++)
    {
        cout << "table[" << i << "]: ";
        node* curr = table[i];
        
        while (curr != nullptr)
        {
            cout << curr->characterName;
            if (curr->next != nullptr)
                cout << ", ";
            curr = curr->next;
        }
        cout << endl;
    }

}


//function to calculate hash function
unsigned int HashTable::hashFunction(string charName)
{
	int sum = 0;

    for (int i = 0; i < charName.length(); i++)
	{
        sum += (int)charName[i];
	}

    return sum % tableSize;
}



node* HashTable::searchCharacter(string charName)
{
	int index = hashFunction(charName);

    node* curr = table[index];

    while (curr != nullptr)
    {
        if (curr->characterName == charName)
		{
            return curr;
		}

        curr = curr->next;
    }

    return nullptr; // not found
}



//function to insert
void HashTable::insertItem(ItemInfo newItem)
{
	node* found = searchCharacter(newItem.characterName);

    if (found != nullptr)
    {
        found->pq.insertElement(newItem);
    }
    else
    {
        int index = hashFunction(newItem.characterName);

        if (table[index] != nullptr)
		{
            numCollision++;
		}

        node* newNode = createNode(newItem.characterName, table[index]);
        table[index] = newNode;

        table[index]->pq.insertElement(newItem);
    }
}


void HashTable:: buildBulk(string fname)
{
    ifstream file(fname);

    if (!file.is_open())
    {
        cout << "wrong file name or path" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string characterName, itemName, damageStr, comment;

        getline(ss, characterName, ';');
        getline(ss, itemName, ';');
        getline(ss, damageStr, ';');
        getline(ss, comment, ';');

        int damage = stoi(damageStr);

        ItemInfo item;
        item.characterName = characterName;
        item.itemName = itemName;
        item.damage = damage;
        item.comment = comment;

        insertItem(item);
    }

    file.close();
}

void HashTable::deleteEntry(string charName, string itemName) 
{
	int index = hashFunction(charName);
    node* curr = table[index];
    node* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->characterName == charName)
        {
            curr->pq.deleteKey(itemName);

            if (curr->pq.isEmpty())
            {
                if (prev == nullptr)
                {
                    table[index] = curr->next;
                }

                else
                {
                    prev->next = curr->next;
                }
                delete curr;
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "no record found" << endl;
}
