// Approximate time - 2 hours

#include "3.h"

#include <unordered_map>
#include <vector>

void cross(vec3* result, vec3* firstVector, vec3* secondVector)
{
	result->x = firstVector->y * secondVector->z - firstVector->z * secondVector->y;
	result->y = firstVector->z * secondVector->x - firstVector->x * secondVector->z;
	result->z = firstVector->x * secondVector->y - firstVector->y * secondVector->x;
}

double calc_vector_length(vec3* vector)
{
	if (vector->x == 0 && vector->y == 0 && vector->z == 0)
		return 1e-9;

	return sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2));
}

void normalize(vec3* vector)
{
	double length = calc_vector_length(vector);

	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

void calc_normal(vec3* normal, const vec3* firstVertex, const vec3* secondVertex, const vec3* thirdVertex)
{
	vec3 firstVector = { secondVertex->x - firstVertex->x, secondVertex->y - firstVertex->y, secondVertex->z - firstVertex->z };
	vec3 secondVector = { thirdVertex->x - firstVertex->x, thirdVertex->y - firstVertex->y, thirdVertex->z - firstVertex->z };

	cross(normal, &firstVector, &secondVector);
	normalize(normal);
}

void calc_average_normal(vec3* result, const std::vector<vec3*>& normals)
{
	result->x = 0;
	result->y = 0;
	result->z = 0;

	for (int i = 0; i < normals.size(); i++)
	{
		result->x += normals[i]->x;
		result->y += normals[i]->y;
		result->z += normals[i]->z;
	}

	normalize(result);
}

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
	if (nfaces == 0 || nverts == 0 || normals == nullptr || verts == nullptr || faces == nullptr)
		return;

	// key - vertex index, value - vector which store all normals to to this vertex
	std::unordered_map<int, std::vector<vec3*>> verticesNormals;

	// calculate normal to every triangle
	for (int i = 0; i < nfaces; i++)
	{
		// take ptr to triangle vertex by its index
		const vec3* firstVertex = &verts[faces[3 * i]];
		const vec3* secondVertex = &verts[faces[3 * i + 1]];
		const vec3* thirdVertex = &verts[faces[3 * i + 2]];

		vec3* normal = new vec3{0, 0, 0};

		calc_normal(normal, firstVertex, secondVertex, thirdVertex);

		verticesNormals[faces[3 * i]].push_back(normal);
		verticesNormals[faces[3 * i + 1]].push_back(normal);
		verticesNormals[faces[3 * i + 2]].push_back(normal);
	}

	for (int i = 0; i < nverts; i++)
	{
		calc_average_normal(&normals[i], verticesNormals[i]);
		
	}

	// очищение памяти векторов 
	// вместо указателя в ключе - индекс

	//for (const auto)
}