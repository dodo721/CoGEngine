#ifndef VOXOBJ_HPP
#define VOXOBJ_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace cog {

    class Mesh;
    class Texture;

    class Obj {
        public:
            Mesh *mesh;
            std::string name;
            std::string texpath;
            Texture *texture;
            glm::vec3 position = glm::vec3(0);
            Obj();
            Obj(std::string name, Mesh* mesh, std::string texpath);
            Obj(std::string name, Mesh* mesh, std::string texpath, glm::vec3 position);
            ~Obj();
    };
    
}

#endif