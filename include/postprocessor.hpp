#ifndef POSTPROCESSOR_HPP
#define POSTPROCESSOR_HPP

#include <string>
#include <map>
#include "glm/glm.hpp"

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
        std::map<unsigned int, float> floatParams;
        std::map<unsigned int, int> intParams;
        std::map<unsigned int, glm::vec2> vec2Params;
        void genMesh();
        bool genBuffers();
        public:
            Postprocessor (std::string shaderPath, unsigned int width, unsigned int height);
            void bind();
            void draw();
            bool setFloatParam (std::string name, float param);
            bool setIntParam (std::string name, int param);
            bool setVec2Param (std::string name, glm::vec2 param);
            bool setVec2Param (std::string name, float x, float y);
            std::string shaderPath;
            Postprocessor* next = NULL;
            Postprocessor* prev = NULL;
    };

}

#endif