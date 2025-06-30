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

int calc_vector_length(vec3* vector)
{
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
	vec3* firstVector = new vec3{ secondVertex->x - firstVertex->x, secondVertex->y - firstVertex->y, secondVertex->z - firstVertex->z };
	vec3* secondVector = new vec3{ thirdVertex->x - firstVertex->x, thirdVertex->y - firstVertex->y, thirdVertex->z - firstVertex->z };

	cross(normal, firstVector, secondVector);
	normalize(normal);

	delete firstVector;
	delete secondVector;
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

	// key - vertex, value - vector which store all normals to to this vertex
	std::unordered_map<const vec3*, std::vector<vec3*>> verticesNormals;

	// calculate normal to every triangle
	for (int i = 0; i < nfaces; i++)
	{
		// take ptr to triangle vertex by its index
		const vec3* firstVertex = &verts[faces[3 * i]];
		const vec3* secondVertex = &verts[faces[3 * i + 1]];
		const vec3* thirdVertex = &verts[faces[3 * i + 2]];

		vec3* normal = new vec3{0, 0, 0};

		calc_normal(normal, firstVertex, secondVertex, thirdVertex);

		verticesNormals[firstVertex].push_back(normal);
		verticesNormals[secondVertex].push_back(normal);
		verticesNormals[thirdVertex].push_back(normal);
	}

	for (int i = 0; i < nverts; i++)
	{
		calc_average_normal(&normals[i], verticesNormals[&verts[i]]);
	}


}