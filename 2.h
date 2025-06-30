#pragma once

#include <string>
#include <vector>

// структуру ListNode модифицировать нельзя  
struct ListNode 
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};

class List 
{
public:
	List() : head(nullptr), tail(nullptr), count(0) {}
	~List();
	void Serialize(FILE* file); // сохранение в файл ( файл открыт с помощью fopen(path, " wb"))
	void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

	void AddNode(std::string data);
	void SetPointersToRandomNodes();

	ListNode* GetTail() { return tail; }
private:
	ListNode* GetPointerToRandomNode();

	void ClearList();
private:
	ListNode* head;
	ListNode* tail;
	int count;

	// vector to store all pointers to nodes in one memory block
	std::vector<ListNode*> nodePointers;
};