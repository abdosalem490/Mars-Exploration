#pragma once
#include"List_Interface.h"
#include "Node.h"
#include <iostream>
using namespace std;

template< class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; 

	Node<ItemType>* getNodeBefore(const ItemType& anEntry) const {
		Node<ItemType>* ptr;
		if (headPtr != nullptr)
			ptr = headPtr->getNext();
		else
			ptr = nullptr;
		Node<ItemType>* prev = headPtr;
		if (headPtr == nullptr)
			return nullptr;
		if (headPtr->getNext() == nullptr)
		{
			if (headPtr->getItem() == anEntry)
				return nullptr;
			else return nullptr;
		}
		if (prev->getItem() == anEntry)
		{
			return nullptr;
		}
		while (ptr != nullptr)
		{
			if (ptr->getItem() == anEntry)
			{
				return prev;
			}
			prev = ptr;
			ptr = ptr->getNext();

		}
		return nullptr;
	}
	
	Node<ItemType>* getNodeAt(int position) const {
		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++)
			curPtr = curPtr->getNext();
		return curPtr;
	}
	
	Node<ItemType>* copyChain(const Node<ItemType>* origChainPtr) {
		Node<ItemType>* copiedChainPtr;
		if (origChainPtr == nullptr)
		{
			copiedChainPtr = nullptr;
		}
		else
		{
			// Build new chain from given one
			Node<ItemType>* copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
			copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
		} // end if
		return copiedChainPtr;
	}
public:
	LinkedSortedList() : headPtr(nullptr) {}
	LinkedSortedList(const LinkedSortedList<ItemType>& aList) {

		headPtr = copyChain(aList.headPtr);
	}
	~LinkedSortedList() {
			clear();
	}
	void insertSorted(const ItemType& newEntry) {

		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		Node<ItemType>* prevPtr = getNodeBefore(newEntry);
		if (isEmpty() || (prevPtr == nullptr)) // Add at beginning
		{
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else // Add after node before
		{
			Node<ItemType>* aftPtr = prevPtr->getNext();
			newNodePtr->setNext(aftPtr);
			prevPtr->setNext(newNodePtr);
		}

	}
	bool removeSorted(const ItemType& anEntry) {

		if (headPtr == nullptr)
			return false;
		if (headPtr->getNext() == nullptr)
		{
			if (headPtr->getItem() == anEntry)
			{
				headPtr = nullptr;
				delete headPtr;
				return true;
			}
			else return false;
		}
		Node<ItemType>* p = headPtr;
		if (p->getItem() == anEntry)
		{
			headPtr = headPtr->getNext()
				;
			return true;
		}
		while (p != nullptr)
		{
			if (p->getNext()->getItem() == anEntry)
			{
				p->setNext(p->getNext()->getNext());
				break;
			}
			p = p->getNext();
		}
		if (p == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int getPosition(const ItemType& anEntry) const {

		int count = 0;
		Node<ItemType>* ptr = headPtr;
		while (ptr != nullptr)
		{
			count++;
			if (ptr->getItem() == anEntry)
				break;
			ptr = ptr->getNext();
		}
		return count;

	}
	// The following methods are the same as given in ListInterface:
	bool isEmpty() const {

		if (headPtr == nullptr)
			return true;
		else return false;

	}
	int getLength() const {

		int count = 0;
		Node<ItemType>* ptr = headPtr;
		while (ptr != nullptr)
		{
			count++;
			ptr = ptr->getNext();
		}
		return count;

	}
	bool remove(int position) {

		if (headPtr == nullptr)
			return false;

		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = headPtr; // Save pointer to node
			headPtr = headPtr->getNext();
		}
		else
		{
			Node<ItemType>* prevPtr = getNodeAt(position - 1);

			curPtr = prevPtr->getNext();

			prevPtr->setNext(curPtr->getNext());

		}
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		return true;

	}
	void clear() {

		while (!isEmpty())
			remove(1);

	}
	ItemType getEntry(int position) const {
		int count = 0;
		Node<ItemType>* ptr = headPtr;
		while (ptr != nullptr)
		{
			if (count == position)
				break;
			count++;
			ptr = ptr->getNext();
		}
		return ptr->getItem();
		
	}//throw(PrecondViolatedExcep);

	void PrintList() const
	{
		Node<ItemType>* p = headPtr;
		while (p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}

};