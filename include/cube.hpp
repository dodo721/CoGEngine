#ifndef CUBE_HPP
#define CUBE_HPP

#include <glm/glm.hpp>

namespace vox {
    namespace obj {
        class Obj;
    }
}

vox::obj::Obj* createCube (glm::vec3 position);
vox::obj::Obj* createCube ();

#endif