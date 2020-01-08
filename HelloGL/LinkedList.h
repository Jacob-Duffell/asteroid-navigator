#pragma once

#include "Structures.h"
#include "SceneObject.h"

struct ObjectNode
{
	SceneObject* data;
	ObjectNode* next;
};

class LinkedList
{
public:
	LinkedList(SceneObject* data);
	~LinkedList();

	void AddToFront(SceneObject* data);

	void PrintData(ObjectNode* p);
	void DeleteList(ObjectNode * p);
	void DeleteAfter(ObjectNode* p);
	ObjectNode* MakeNewNode(SceneObject* data);
	ObjectNode* MakeNewHead(ObjectNode* p, ObjectNode* newNode);
	SceneObject * GetNode(int pos);
	ObjectNode* Search(ObjectNode* p);
	ObjectNode* InsertAfter(ObjectNode* p, ObjectNode* newNode);

private:
	ObjectNode* _head;
};