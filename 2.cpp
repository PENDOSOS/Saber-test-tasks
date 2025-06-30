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

// fwrite ?
// дата с пробелами
// указатели в файле плохо (?)

void List::Serialize(FILE* file)
{
	if (file == nullptr)
		return;

	int64_t index = 0; 
	for (int i = 0; i < count; i++)//while (currentNode != nullptr)
	{
		ListNodeFile* dataToWrite = new ListNodeFile{i, randomNodeIndices[i], nodePointers[i]->data};
		std::cout << fwrite(dataToWrite, sizeof(ListNodeFile), 1, file);
		delete dataToWrite;
	}
}

void List::Deserialize(FILE* file)
{
	if (file == nullptr)
		return;

	if (count > 0)
		ClearList();

	// key - current node index, value - random node index
	std::unordered_map<int64_t, int64_t> nodeRelations;

	/*std::vector<std::string> lineElements;
	lineElements.resize(3);

	char data[1000];*/

	ListNodeFile readData;
	ListNode readData1;

	while (fread(&readData, sizeof(ListNodeFile), 1, file))
	{
		nodeRelations[readData.nodeIndex] = readData.randIndex;
		AddNode(readData.data);
		randomNodeIndices.push_back(readData.randIndex);
	}

	// restore 
	for (int i = 0; i < count; i++)
	{
		ListNode* randomNode = nullptr;
		ListNode* currentNode = nodePointers[i];

		if (nodeRelations[i] != -1)
			randomNode = nodePointers[nodeRelations[i]];
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
	int64_t/*ListNode**/ randomNode;
	while (currentNode != nullptr)
	{
		randomNode = GetPointerToRandomNode();
		randomNodeIndices.push_back(randomNode);
		if (randomNode == -1)
			currentNode->rand = nullptr;
		else
			currentNode->rand = nodePointers[randomNode]/*randomNode*/;

		currentNode = currentNode->next;
	}
}

int64_t/*ListNode**/ List::GetPointerToRandomNode()
{	
	int64_t elem = -1 + std::rand() % (count + 1);
	return elem;
	/*if (elem == -1)
		return nullptr;
	else
	{
		return nodePointers[elem];
	}*/
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
