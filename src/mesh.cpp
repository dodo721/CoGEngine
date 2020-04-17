#include "mesh.hpp"
#include "macros.hpp"
#include "array_utils.hpp"

using namespace glm;
using namespace std;
using namespace cog;


Mesh::Mesh () {}

Mesh::Mesh (vector<float> verts, vector<float> uv, vector<unsigned int> indices): vertices(verts), uvs(uv), indices(indices) {}

int Mesh::getVertSize () {
    return vertices.size();
}

int Mesh::getUVSize () {
    return uvs.size();
}

int Mesh::getIndicesSize () {
    return indices.size();
}

float* Mesh::getVerts () {
    return &vertices[0];
}

float* Mesh::getUVs () {
    return &uvs[0];
}

unsigned int* Mesh::getIndices () {
    return &indices[0];
}