#ifndef POSTPROCESSOR_HPP
#define POSTPROCESSOR_HPP

#include <string>

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
        std::string shaderPath;
        bool genBuffers();
        void genMesh();
        public:
            Postprocessor (std::string shaderPath, unsigned int width, unsigned int height);
            void bind();
            void draw();
    };

}

#endif