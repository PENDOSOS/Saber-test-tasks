// Approximate time - 2 hours

struct vec3
{
	double x, y, z;
};

//  
// Calculate smooth (average) per-vertex normal 
//  
// [out] normals - output per-vertex normal  
// [in] verts - input per-vertex positions 
// [in] faces - triangles (triplets of vertex indices) 
// [in] nverts - total number of vertices 
// [in] nfaces - total number of triangles
//
void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces);