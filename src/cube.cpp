#include "cube.hpp"
#include "array_utils.hpp"
#include "mesh.hpp"
#include "voxobj.hpp"

using namespace glm;
using namespace vox::obj;

float cube_vertex_array[] = {
    -1.0f, -1.0f, -1.0f,            // 0 - bottom left
    -1.0f, 1.0f, -1.0f,             // 1 - top left
    1.0f, 1.0f, -1.0f,              // 2 - top right
    1.0f, -1.0f, -1.0f              // 3 - bottom right
};

float cube_uv_array[] = {
    -1.0f, -1.0f,
    -1.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, -1.0f
};

unsigned int cube_indices_array[] = {
    3, 0, 1,
    1, 2, 3
};

vector<float> cube_vertex_data = arrayToVector<float>(cube_vertex_array, sizeof(cube_vertex_array) / sizeof(cube_vertex_array[0]));
vector<float> cube_uv_data = arrayToVector<float>(cube_uv_array, sizeof(cube_uv_array) / sizeof(cube_uv_array[0]));
vector<unsigned int> cube_indices_data = arrayToVector<unsigned int>(cube_indices_array, sizeof(cube_indices_array) / sizeof(cube_indices_array[0]));
Mesh* cubeMesh = new Mesh(cube_vertex_data, cube_uv_data, cube_indices_data);

VoxObj* createCube (vec3 position) {
    VoxObj* obj = new VoxObj("Cube", cubeMesh, "grass.png", position);
    return obj;
}

VoxObj* createCube () {
    VoxObj* obj = new VoxObj("Cube", cubeMesh, "grass.png");
    return obj;
}