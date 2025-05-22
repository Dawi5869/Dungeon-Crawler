#include<iostream>
#include <vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "hash.hpp"
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"

using namespace std;
using namespace std::chrono;

void displayMenu()//keep it in starter code
{
    cout<<"------------------"<<endl;
    cout<<"1: Build the datastructure (call it only once)"<<endl;
    cout<<"2: Add a new item"<<endl;
    cout<<"3: Peek most powerful item from character"<<endl;
    cout<<"4: Pop most powerful item from character"<<endl;
    cout<<"5: Print all items for character"<<endl;
    cout<<"6: Get number of collisions"<<endl;
    cout<<"7: Print the table"<<endl;
	cout<<"8: Find easiest route through dungeon"<<endl;
    cout<<"9: Exit"<<endl;
    cout<<"------------------"<<endl;

}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct num of arg"<<endl;
    }
    string fname =argv[1];
    int tableSize = stoi(argv[2]);
    
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool built = false;
    while(ch!=9)
    {
        displayMenu();
        cout<<"Give your choice >> ";
        getline(cin, chs);
        ch =stoi(chs);
        switch (ch)
        {
            case 1:{ // bulk build (should only build on first call)
				if (!built)
                {
                    ht.buildBulk(fname);
                    built = true;
                }
                else
                {
                    cout << "Data structure already built" << endl;
                }
                break;
            }


            case 2:{ // Insert new items from console
				ItemInfo item;

                cout << "Character Name: ";
                getline(cin, item.characterName);

                cout << "Item Name: ";
                getline(cin, item.itemName);

                cout << "Damage: ";
                string damageStr;
                getline(cin, damageStr);
                item.damage = stoi(damageStr);

                cout << "Comment: ";
                getline(cin, item.comment);

                // Insert into hash table
                ht.insertItem(item);
                break;
            }


            case 3:{ // Peek 
				cout << "Character name: ";
                string charName;
                getline(cin, charName);

                node* charNode = ht.searchCharacter(charName);

                if (charNode == nullptr)
                {
                    cout << "no record found" << endl;
                }
                else
                {
                    ItemInfo* topItem = charNode->pq.peek();
                    if (topItem == nullptr)
                    {
                        cout << "no record found" << endl;
                    }
                    else
                    {
                        cout << "retrieved result" << endl;
                        cout << "Character: " << charNode->characterName << endl;
                        cout << "Item: " << topItem->itemName << endl;
                        cout << "Damage: " << topItem->damage << endl;
                        cout << "Comment: " << topItem->comment << endl;
                    }
                }
                break;
			}


            case 4:{ // Pop
				cout << "Character name: ";
                string charName;
                getline(cin, charName);

                cout << "Item name: ";
                string itemName;
                getline(cin, itemName);

                ht.deleteEntry(charName, itemName);

                break;
            }


            case 5:{ // Print all items for character
				cout << "Character name: ";
                string charName;
                getline(cin, charName);

                node* charNode = ht.searchCharacter(charName);

                if (charNode == nullptr)
                {
                    cout << "no record found" << endl;
                }
                else
                {
                    cout << "Character: " << charNode->characterName << endl;
                    charNode->pq.print();
                }
                break;
			}


            case 6: { // Display collisions
				cout << "Number of collision: " << ht.getNumCollision() << endl;
                break;
			}


            case 7: { // Print table
				ht.printTable();
                break;
			}

            
			case 8:{ // Find easiest path through dungeon
				cout << "Input dungeon(file name): " << endl;
				string dungeonFile;
				getline(cin, dungeonFile);
				EnemyGraph G;
				G.buildGraphFromFile(dungeonFile);
				cout << G.findEasiestPath(ht) << endl;
				break;
			}
			case 9:
				cout << "Goodbye..." << endl;
				break;
       
            default:
                cout<<"Give a valid entry"<<endl;
                break;
        }
    }
}
