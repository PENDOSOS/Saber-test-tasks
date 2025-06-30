#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "1.h"
#include "2.h"
#include "3.h"

int main()
{
	unsigned int* test = new unsigned int;
	*test = 3590324224;
	//*test = 1234;
	//*test = 107;
	//*test = 4294967295;
	invertBitSequence(test);
	delete test;

	List* testList = new List;

	// AddNode adds new node to list
	{
		testList->AddNode(std::string("001"));
		testList->AddNode(std::string("002"));
		testList->AddNode(std::string("003"));
		testList->AddNode(std::string("004"));
		testList->AddNode(std::string("005"));
		/*testList->AddNode(std::string("006"));
		testList->AddNode(std::string("007"));
		testList->AddNode(std::string("008"));
		testList->AddNode(std::string("009"));
		testList->AddNode(std::string("010"));
		testList->AddNode(std::string("011"));
		testList->AddNode(std::string("012"));
		testList->AddNode(std::string("013"));
		testList->AddNode(std::string("014"));
		testList->AddNode(std::string("015"));
		testList->AddNode(std::string("016"));
		testList->AddNode(std::string("017"));
		testList->AddNode(std::string("018"));
		testList->AddNode(std::string("019"));
		testList->AddNode(std::string("020"));
		testList->AddNode(std::string("021"));
		testList->AddNode(std::string("022"));
		testList->AddNode(std::string("023"));
		testList->AddNode(std::string("024"));
		testList->AddNode(std::string("025"));
		testList->AddNode(std::string("026"));
		testList->AddNode(std::string("027"));
		testList->AddNode(std::string("028"));
		testList->AddNode(std::string("029"));
		testList->AddNode(std::string("030"));*/
	}

	FILE* file = fopen("test.bin", "wb");
	testList->SetPointersToRandomNodes();
	testList->Serialize(file);
	fclose(file);

	List* testList2 = new List;
	file = fopen("test.bin", "rb");
	testList2->Deserialize(file);
	fclose(file);
	delete testList;
	delete testList2;

	calc_mesh_normals();
	return 0;
}