#ifndef CUBE_HPP
#define CUBE_HPP

#include <glm/glm.hpp>

namespace cog {
    class Obj;
}

cog::Obj* createCube (glm::vec3 position);
cog::Obj* createCube ();

#endif