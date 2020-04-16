#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "voxobj.hpp"
#include "glm/glm.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "macros.hpp"
#include "array_utils.hpp"

using namespace glm;
using namespace std;
using namespace vox::obj;

VoxObj::VoxObj () {}

VoxObj::VoxObj (string name, Mesh* mesh, string texpath): name(name), mesh(mesh), texpath(texpath) {}
VoxObj::VoxObj (string name, Mesh* mesh, string texpath, vec3 position): name(name), mesh(mesh), texpath(texpath), position(position) {}

VoxObj::~VoxObj () {
    mesh->objRefs--;
    if (mesh->objRefs == 0)
        delete mesh;
        
    texture->objRefs--;
    if (texture->objRefs == 0)
        delete texture;
}