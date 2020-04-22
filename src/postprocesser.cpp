#include "postprocessor.hpp"

#include <iostream>
#include "glad/glad.h"
#include "shader.hpp"

using namespace std;
using namespace cog;
using namespace glm;

Postprocessor::Postprocessor (string shaderPath, GLuint width, GLuint height): shaderPath(shaderPath), width(width), height(height) {
    programId = LoadShaders( "shaders/postprocess.vert", shaderPath.c_str() );
    sampler = glGetUniformLocation(programId, "render");
    if (!genBuffers()) {
        throw;
    }
    genMesh();
}

bool Postprocessor::genBuffers () {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // The texture we're going to render to
    glGenTextures(1, &texture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    else
        return true;
}

void Postprocessor::genMesh () {
    // The fullscreen quad's FBO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Postprocessor::bind () {
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0,0,width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

void Postprocessor::draw () {
    if (next != NULL) {
        next->bind();
    } else {
        // Render to the screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    }

    glBindVertexArray(vao);
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programId);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set our "renderedTexture" sampler to user Texture Unit 0
    glUniform1i(sampler, 0);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6); // From index 0 to 3 -> 1 triangle

    glDisableVertexAttribArray(0);
}

void Postprocessor::addFloatParam (string name, float param) {
    floatParams[name] = param;
}

void Postprocessor::addVec2Param (string name, float x, float y) {
    //vec2Params[name] = param;
}