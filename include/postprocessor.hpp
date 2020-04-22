#ifndef POSTPROCESSOR_HPP
#define POSTPROCESSOR_HPP

#include <string>
#include <map>

namespace glm {
    class vec2;
}

namespace cog {

    class Postprocessor {
        unsigned int width;
        unsigned int height;
        unsigned int fbo;
        unsigned int texture;
        unsigned int sampler;
        unsigned int depthBuffer;
        unsigned int programId;
        unsigned int vao;
        unsigned int vbo;
        std::map<std::string, float> floatParams;
        std::map<std::string, glm::vec2> vec2Params;
        void genMesh();
        bool genBuffers();
        public:
            Postprocessor (std::string shaderPath, unsigned int width, unsigned int height);
            void bind();
            void draw();
            void addFloatParam (std::string name, float param);
            void addVec2Param (std::string name, float x, float y);
            std::string shaderPath;
            Postprocessor* next = NULL;
            Postprocessor* prev = NULL;
    };

}

#endif