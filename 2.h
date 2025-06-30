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
	ListNode* GetPointerToRandomNode();

	void ClearList();

	ListNode* head;
	ListNode* tail;
	int count;

	// vector to store all pointers to nodes in one memory block
	std::vector<ListNode*> nodePointers;
};