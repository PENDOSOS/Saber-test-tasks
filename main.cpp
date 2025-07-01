#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "1.h"
#include "2.h"
#include "3.h"

int main()
{
	uint32_t test = 3590324224;
	test = 107;
	//test = 1234;
	//test = 1234;
	//test = 107;
	test = 4294967295;
	test = 0;
	//std::cout << invertBitSequence(test);

	List* testList = new List;

	// AddNode adds new node to list
	{
		testList->AddNode(std::string("001   fsdfsdf  12"));
		testList->AddNode(std::string(""));
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

	vec3 points[] = {
			{0, 0, 0}, //0
			{0, 0, 1}, //1
			{0, 1, 0}, //2
			{0, 1, 1}, //3
			{1, 0, 0}, //4
			{1, 0, 1}, //5
			{1, 1, 0}, //6
			{1, 1, 1}, //7
	};

	int const faces[] = {
			6, 0, 4, // bottom
			0, 6, 2, //

			5, 1, 7, // top
			1, 3, 7, //

			4, 0, 1, // left
			1, 5, 4, //

			3, 2, 6, // right
			6, 7, 3, //

			3, 1, 0, // back
			3, 0, 2, //

			4, 5, 7, // front
			4, 7, 6, //
	};

	vec3 normals[8];
	calc_mesh_normals(normals, points, faces, 8, 12);

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "point: ( " << points[i].x << "; " << points[i].y << "; " << points[i].z << " )" << std::endl 
			<< "normal: ( " << normals[i].x << "; " << normals[i].y << "; " << normals[i].z << " )" << std::endl;
	}

	//calc_mesh_normals();
	return 0;
}