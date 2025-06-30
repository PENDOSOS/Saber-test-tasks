// Approximate time - 5 hours

#pragma once

#include <string>
#include <vector>
  
struct ListNode 
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand;
	std::string data;
};

class List 
{
public:
	List() : head(nullptr), tail(nullptr), count(0) {}
	~List();
	void Serialize(FILE* file);
	void Deserialize(FILE* file);

	void AddNode(std::string data);
	void SetPointersToRandomNodes();

	ListNode* GetTail() { return tail; }
private:
	// structure to write/read ListNode to/from file
	struct ListNodeFile
	{
		int64_t nodeIndex;
		int64_t randIndex;
		std::string data;
	};

	int64_t/*ListNode**/ GetPointerToRandomNode();

	void ClearList();

	ListNode* head;
	ListNode* tail;
	int count;

	// vector to store all pointers to nodes in one memory block
	std::vector<ListNode*> nodePointers;
	// vector to store info about random node indices
	std::vector<int64_t> randomNodeIndices;
};