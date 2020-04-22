#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.hpp"
#include "postprocessor.hpp"

using namespace std;
using namespace cog;

int main( void )
{
	
	cout << "Initiating CogEngine..." << endl;
	render_init(1024, 1024);

	// Post processing
	Postprocessor* sphere = new Postprocessor("shaders/projection.frag", 1024, 1024);
	Postprocessor* blur_h = new Postprocessor("shaders/blur.frag", 1024, 1024);
	//use_postprocessor(sphere);
	blur_h->addFloatParam("radius", 1.0f);
	blur_h->addVec2Param("dir", 1.0f, 0.0f);
	use_postprocessor(blur_h);

	do {
		
		render_update();

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ); // Check if the ESC key was pressed or the window was closed

	render_cleanup();
	delete sphere;
	delete blur_h;

	return 0;
}