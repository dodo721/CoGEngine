#include "render.hpp"

#include <iostream>
#include <math.h>
#include <string>

#include <mesh.hpp>
#include <voxobj.hpp>
#include <cube.hpp>
#include <macros.hpp>
#include <shader.hpp>
#include <texture.hpp>

//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

using namespace glm;
using namespace std;
using namespace vox;
using namespace obj;

namespace vox::render {

    GLFWwindow* window;

    vector<Texture*> textures (0);
    vector<VoxObj*> objects (0);

    GLuint programID;
    GLuint MatrixID;
    GLuint TextureID;

    bool render_init (int width, int height) {
        // Initialise GLFW
        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW\n" );
            return false;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow( width, height, "Tutorial 05 - Textured Cube", NULL, NULL);
        if( window == NULL ){
            fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
        

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders( "shaders/stdvert.vert", "shaders/stdfrag.frag" );

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");
        
        // Get a handle for our "myTextureSampler" uniform
        TextureID  = glGetUniformLocation(programID, "tex2d");

        VoxObj* cube = createCube();
        objects.push_back(cube);
        VoxObj* cube2 = createCube(vec3(2,0,0));
        objects.push_back(cube2);

        npforeach (VoxObj*, obj, objects)
            cout << "Loading " << obj->name << endl;
            loadVoxObj(*obj);
        }

        return true;
        
    }

    void render_cleanup () {
        // Cleanup VBO and shader
        npforeach (VoxObj*, obj, objects)
            glDeleteBuffers(1, &obj->mesh->vertexBuffer);
            glDeleteBuffers(1, &obj->mesh->uvBuffer);
            glDeleteVertexArrays(1, &obj->mesh->VAO);
            glDeleteTextures(1, &obj->texture->textureId);
            delete obj;
        }

        glDeleteProgram(programID);
        // Close OpenGL window and terminate GLFW
        glfwTerminate();
    }

    void render_update () {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                    glm::vec3(0,0,0), // and looks at the origin
                                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                            );

        npforeach(VoxObj*, obj, objects)

            // Bind our texture in Texture Unit 0
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, obj->texture->textureId);
            // Set our "myTextureSampler" sampler to use Texture Unit 0
            glUniform1i(TextureID, 0);

            //cout << obj->position.x << ", " << obj->position.y << ", " << obj->position.z << endl;
            // Model matrix : an identity matrix (model will be at the origin)
            glm::mat4 Model = glm::translate(glm::mat4(1.0f), obj->position);
            // Our ModelViewProjection : multiplication of our 3 matrices
            glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
            // Send our transformation to the currently bound shader, 
            // in the "MVP" uniform
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glBindVertexArray(obj->mesh->VAO);

            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->vertexBuffer);
            glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            
            // 2nd attribute buffer : UVs
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->uvBuffer);
            glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                2,                                // size : U+V => 2
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
            );

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->mesh->indiceBuffer);

            // Draw the triangles !
            glDrawElements(
                GL_TRIANGLES,      // mode
                obj->mesh->getIndicesSize(),    // count
                GL_UNSIGNED_INT,   // type
                (void*)0           // element array buffer offset
            );

            /*// Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, obj->mesh->getVertSize()); // 12*3 indices starting at 0 -> 12 triangles*/

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

        }
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void loadVoxObj (VoxObj& obj) {

        glGenVertexArrays(1, &obj.mesh->VAO);
        glBindVertexArray(obj.mesh->VAO);

        glGenBuffers(1, &obj.mesh->vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, obj.mesh->getVertSize() * sizeof(obj.mesh->getVerts()[0]), obj.mesh->getVerts(), GL_STATIC_DRAW);

        glGenBuffers(1, &obj.mesh->uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, obj.mesh->getUVSize() * sizeof(obj.mesh->getUVs()[0]), obj.mesh->getUVs(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        //std::vector<unsigned int> indices;

        // fill "indices" as needed

        // Generate a buffer for the indices
        glGenBuffers(1, &obj.mesh->indiceBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.mesh->indiceBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.mesh->getIndicesSize() * sizeof(unsigned int), obj.mesh->getIndices(), GL_STATIC_DRAW);

        npforeach(Texture*, tex, textures)
            if (tex->filePath == obj.texpath) {
                obj.texture = tex;
                tex->objRefs++;
                return;
            }
        }

        Texture* texture  = new Texture(obj.texpath);
        texture->objRefs++;
        textures.push_back(texture);
        obj.texture = texture;
    }

}