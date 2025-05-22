#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b)
{
	ItemInfo temp = *a;
	*a = *b;
	*b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ()
{
	capacity = 50;
    heapArr = new ItemInfo[capacity];
    currentSize = 0;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
	return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
	return (2 * index) + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
	return (2 * index) + 2;
}

ItemInfo* PriorityQ::peek()
{
	if (currentSize == 0)
	{
        return nullptr;
	}

    return &heapArr[0];
}

void PriorityQ::heapify(int i)
{
	int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < currentSize && heapArr[left].damage > heapArr[largest].damage)
	{
        largest = left;
	}

    if (right < currentSize && heapArr[right].damage > heapArr[largest].damage)
	{
        largest = right;
	}

    if (largest != i)
    {
        swap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ItemInfo item)
{
	heapArr[currentSize] = item;
    int index = currentSize;
    currentSize++;

    while (index != 0 && heapArr[parent(index)].damage < heapArr[index].damage)
    {
        swap(&heapArr[index], &heapArr[parent(index)]);
        index = parent(index);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
	for (int i = 0; i < currentSize; i++)
    {
        cout << "\tItem: " << heapArr[i].itemName << endl;
        cout << "\tDamage: " << heapArr[i].damage << endl;
        cout << "\tComment: " << heapArr[i].comment << endl;
        cout << "\t=================" << endl;
    }
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) {
	// TODO
	// skipping for now
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
	if (currentSize == 0)
	{
        return;
	}

    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;

    heapify(0);
}


void PriorityQ::deleteKey(string itemName)
{
	int index = -1;

    for (int i = 0; i < currentSize; i++)
    {
        if (heapArr[i].itemName == itemName)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return;
    }

    heapArr[index] = heapArr[currentSize - 1];
    currentSize--;

    heapify(index);
}