#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.hpp"

using namespace std;
using namespace vox::render;

int main( void )
{
	
	render_init(1024, 768);
	
	do {
		
		render_update();

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ); // Check if the ESC key was pressed or the window was closed

	render_cleanup();

	return 0;
}