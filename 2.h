#pragma once

#include <string>
#include <vector>

// ��������� ListNode �������������� ������  
struct ListNode 
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand; // ��������� �� ������������ ������� ������� ������, ���� NULL
	std::string data;
};

class List 
{
public:
	List() : head(nullptr), tail(nullptr), count(0) {}
	~List();
	void Serialize(FILE* file); // ���������� � ���� ( ���� ������ � ������� fopen(path, " wb"))
	void Deserialize(FILE* file); // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

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