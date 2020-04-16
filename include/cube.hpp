#ifndef CUBE_HPP
#define CUBE_HPP

#include <glm/glm.hpp>

namespace vox {
    namespace obj {
        class VoxObj;
    }
}

vox::obj::VoxObj* createCube (glm::vec3 position);
vox::obj::VoxObj* createCube ();

#endif