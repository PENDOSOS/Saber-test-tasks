#include "2.h"

#include <random>
#include <map>
#include <sstream>

List::~List()
{
}

void List::Serialize(FILE* file)
{
	if (file == nullptr)
		return;

	ListNode* currentNode = head;
	while (currentNode != nullptr)
	{
		// write addresses of node's pointers in file to have possibility to restore full structure of list
		fprintf(file, "%s %p %p\n", currentNode->data.c_str(), currentNode, currentNode->rand);

		currentNode = currentNode->next;
	}
}

void List::Deserialize(FILE* file)
{
	if (file == nullptr)
		return;

	if (count > 0)
		ClearList();

	// map to store relation between node and random node
	std::map<std::string, std::string> nodeRelations;
	// map to store association between old and new address of node
	std::map<ListNode*, std::string> fromNewToOldAddress;
	// map to store association between new and old address of node
	std::map<std::string, ListNode*> fromOldToNewAddress;
	std::vector<std::string> lineElements;
	lineElements.resize(3);

	char data[1000];

	// reading file content line by line
	while (fgets(data, 1000, file) != nullptr)
	{
		std::string temp{ data };
		// divide line on words by spaces
		std::istringstream sstream(temp);
		sstream >> lineElements[0]; // node data
		sstream >> lineElements[1]; // ptr to current node
		sstream >> lineElements[2]; // ptr to random node in current node
		// check if all data was read succesfully
		if (lineElements[0] == "" || lineElements[1] == "" || lineElements[2] == "")
			return;
		AddNode(lineElements[0]);
		nodeRelations[lineElements[1]] = lineElements[2];
		fromNewToOldAddress[GetTail()] = lineElements[1];
		fromOldToNewAddress[lineElements[1]] = GetTail();
	}

	for (int i = 0; i < count; i++)
	{
		ListNode* randomNode = nullptr;
		ListNode* currentNode = nodePointers[i];
		// find old random node address by current node address
		std::string oldRandomNodeAddress = nodeRelations[fromNewToOldAddress[currentNode]];
		// check if old random node address isn't null then assign new random node addres to current node 
		// else assign nullptr
		if (std::stoull(oldRandomNodeAddress)) // just enough to get nonzero value to check if pointer is not null
			randomNode = fromOldToNewAddress[oldRandomNodeAddress];
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
	ListNode* randomNode = nullptr;
	while (currentNode != nullptr)
	{
		randomNode = GetPointerToRandomNode();

		if (randomNode == currentNode)
			currentNode->rand = nullptr;
		else
			currentNode->rand = randomNode;

		currentNode = currentNode->next;
	}
}

ListNode* List::GetPointerToRandomNode()
{	
	int elem = -1 + std::rand() % (count + 1);
	if (elem == -1)
		return nullptr;
	else
	{
		return nodePointers[elem];
	}
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
}
