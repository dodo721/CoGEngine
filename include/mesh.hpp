#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;

namespace cog {

    class Mesh {
        vector<float> vertices;
        vector<float> uvs;
        vector<unsigned int> indices;
        public:
            unsigned int VAO;
            unsigned int vertexBuffer;
            unsigned int uvBuffer;
            unsigned int indiceBuffer;
            unsigned int vertSize;
            unsigned int uvSize;
            unsigned int objRefs = 0;
            Mesh();
            Mesh(vector<float> verts, vector<float> uv, vector<unsigned int> indices);
            int getVertSize();
            int getUVSize();
            int getIndicesSize();
            float* getVerts();
            float* getUVs();
            unsigned int* getIndices();
    };
    
}

#endif