#ifndef VOXOBJ_HPP
#define VOXOBJ_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace vox {
    namespace obj {

        class Mesh;
        class Texture;

        class VoxObj {
            public:
                Mesh *mesh;
                std::string name;
                std::string texpath;
                Texture *texture;
                glm::vec3 position = glm::vec3(0);
                VoxObj();
                VoxObj(std::string name, Mesh* mesh, std::string texpath);
                VoxObj(std::string name, Mesh* mesh, std::string texpath, glm::vec3 position);
                ~VoxObj();
        };

    }
}

#endif