// Approximate time - 2 hours

#include "3.h"

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

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
	if (nfaces == 0 || nverts == 0 || normals == nullptr || verts == nullptr || faces == nullptr)
		return;

	std::vector<vec3*> vertNormals;
	vertNormals.resize(nverts);

	for (int i = 0; i < nverts; i++)
	{
		vertNormals[i] = &normals[i];
		vertNormals[i]->x = 0;
		vertNormals[i]->y = 0;
		vertNormals[i]->z = 0;
	}

	for (int i = 0; i < nfaces; i++)
	{
		const vec3* firstVertex = &verts[faces[3 * i]];
		const vec3* secondVertex = &verts[faces[3 * i + 1]];
		const vec3* thirdVertex = &verts[faces[3 * i + 2]];

		vec3 normal = { 0, 0, 0 };

		calc_normal(&normal, firstVertex, secondVertex, thirdVertex);

		vertNormals[faces[3 * i]]->x += normal.x;
		vertNormals[faces[3 * i]]->y += normal.y;
		vertNormals[faces[3 * i]]->z += normal.z;

		vertNormals[faces[3 * i + 1]]->x += normal.x;
		vertNormals[faces[3 * i + 1]]->y += normal.y;
		vertNormals[faces[3 * i + 1]]->z += normal.z;

		vertNormals[faces[3 * i + 2]]->x += normal.x;
		vertNormals[faces[3 * i + 2]]->y += normal.y;
		vertNormals[faces[3 * i + 2]]->z += normal.z;
	}

	for (int i = 0; i < nverts; i++)
	{
		normalize(vertNormals[i]);
	}
}