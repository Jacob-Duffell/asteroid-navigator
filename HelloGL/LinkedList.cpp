#include "LinkedList.h"
#include <cstdio>

LinkedList::LinkedList(SceneObject* data)
{
	_head = new ObjectNode();
	_head->data = data;
	_head->next = nullptr;
}

LinkedList::~LinkedList()
{
	delete _head;
}

void LinkedList::AddToFront(SceneObject* data)
{
	ObjectNode * node = MakeNewNode(data);

	node->next = _head;
	_head = node;
}

ObjectNode* LinkedList::MakeNewNode(SceneObject* data)
{
	ObjectNode * newNode = new ObjectNode();
	newNode->data = data;
	newNode->next = nullptr;

	return newNode;
}

void LinkedList::PrintData(ObjectNode* p)
{
	while (p != nullptr)
	{
		printf("%5d", p->data);
		p = p->next;
	}

	printf("\n");
}

void LinkedList::DeleteList(ObjectNode* p)
{
	ObjectNode* pTemp;

	while (p != nullptr)
	{
		pTemp = p;
		p = p->next;
		delete pTemp;
	}
}

ObjectNode* LinkedList::MakeNewHead(ObjectNode* p, ObjectNode* newNode)
{
	newNode->next = p;
	return newNode;
}

SceneObject * LinkedList::GetNode(int pos)
{
	ObjectNode* p = _head;

	int count = 0;

	while (p != nullptr)
	{
		if (count == pos)
		{
			return p->data;
		}

		count++;
		p = p->next;
	}

	return nullptr; // not a valid position
}

ObjectNode* LinkedList::Search(ObjectNode* p)
{
	ObjectNode* val = _head;

	while (val != nullptr)
	{
		if (val->data == p->data)
		{
			return val;
		}

		val = val->next;
	}

	return nullptr; // value not in list
}

ObjectNode* LinkedList::InsertAfter(ObjectNode* p, ObjectNode* newNode)
{
	newNode->next = p->next;
	p->next = newNode;

	return newNode;
}

void LinkedList::DeleteAfter(ObjectNode* p)
{
	ObjectNode* pTemp;

	if (p != nullptr && p->next != nullptr)
	{
		pTemp = p->next;
		p->next = pTemp->next;
		delete pTemp;
	}
}