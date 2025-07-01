// Approximate time - 5 hours

#include "2.h"

#include <random>
#include <unordered_map>
#include <sstream>
#include <iostream>

List::~List()
{
	ClearList();
}

void List::Serialize(FILE* file)
{
	if (file == nullptr)
		return;
	
	for (int64_t i = 0; i < count; i++)
	{
		size_t dataSize = nodePointers[i]->data.size();
		fwrite(&dataSize, sizeof(size_t), 1, file);
		if (dataSize > 0)
			fwrite(nodePointers[i]->data.c_str(), sizeof(char), dataSize, file);
		fwrite(&i, sizeof(int64_t), 1, file);
		fwrite(&randomNodeIndices[i], sizeof(int64_t), 1, file);
	}
}

void List::Deserialize(FILE* file)
{
	if (file == nullptr)
		return;

	if (count > 0)
		ClearList();

	// key - current node index, value - random node index in current node
	std::unordered_map<int64_t, int64_t> nodeRelations;

	size_t dataSize = 0;
	int64_t nodeIndex = 0;
	int64_t randIndex = 0;
	
	while (fread(&dataSize, sizeof(size_t), 1, file))
	{
		std::string data;
		if (dataSize)
		{
			char* buf = new char[dataSize + 1];
			if (!fread(buf, sizeof(char), dataSize, file))
			{
				delete[] buf;
				return;
			}
			buf[dataSize] = '\0';
			data = buf;
			delete[] buf;
		}

		if (!fread(&nodeIndex, sizeof(int64_t), 1, file))
			return;

		if (!fread(&randIndex, sizeof(int64_t), 1, file))
			return;

		nodeRelations[nodeIndex] = randIndex;
		AddNode(data);
		randomNodeIndices.push_back(randIndex);
	}

	// restore 
	for (int i = 0; i < count; i++)
	{
		ListNode* randomNode = nullptr;
		ListNode* currentNode = nodePointers[i];

		if (nodeRelations[i] != -1 && nodeRelations[i] != i)
		{
			randomNode = nodePointers[nodeRelations[i]];
		}
		currentNode->rand = randomNode;
	}
}

void List::AddNode(std::string data)
{
	ListNode* newNode = new ListNode{ nullptr, nullptr, nullptr, data };
	nodePointers.push_back(newNode);
	if (head != nullptr)
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	else
	{
		head = newNode;
		tail = newNode;
	}
	count++;
}

void List::SetPointersToRandomNodes()
{
	std::srand(time(0));
	ListNode* currentNode = head;
	int64_t randomNode;
	while (currentNode != nullptr)
	{
		randomNode = GetIndexOfRandomNode();
		randomNodeIndices.push_back(randomNode);
		if (randomNode == -1 || nodePointers[randomNode] == currentNode)
			currentNode->rand = nullptr;
		else
			currentNode->rand = nodePointers[randomNode];

		currentNode = currentNode->next;
	}
}

int64_t List::GetIndexOfRandomNode()
{	
	int64_t elem = -1 + std::rand() % (count + 1);
	return elem;
}

void List::ClearList()
{
	ListNode* currentNode = tail;
	while (currentNode != nullptr)
	{
		currentNode = tail->prev;
		delete tail;
		tail = currentNode;
		count--;
	}
	head = nullptr;
	nodePointers.clear();
	randomNodeIndices.clear();
}
