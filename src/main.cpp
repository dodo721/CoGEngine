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
	Postprocessor* blur_h = new Postprocessor("shaders/blur.frag", 1024, 1024);
	if (!blur_h->setFloatParam("radius", 3.0f)) cout << "Radius failed" << endl;
	if (!blur_h->setFloatParam("resolution", 1024.0f)) cout << "Resolution failed" << endl;
	if (!blur_h->setFloatParam("stDev", 0.01f)) cout << "StDev failed" << endl;
	if (!blur_h->setFloatParam("threshold", 0.3f)) cout << "Threshold failed" << endl;
	if (!blur_h->setVec2Param("dir", 1.0f, 0.0f)) cout << "Dir failed" << endl;
	if (!blur_h->setIntParam("samples", 20)) cout << "Samples failed" << endl;
	use_postprocessor(blur_h);

	Postprocessor* blur_v = new Postprocessor("shaders/blur.frag", 1024, 1024);
	if (!blur_v->setFloatParam("radius", 3.0f)) cout << "Radius failed" << endl;
	if (!blur_v->setFloatParam("resolution", 1024.0f)) cout << "Resolution failed" << endl;
	if (!blur_v->setFloatParam("stDev", 0.01f)) cout << "StDev failed" << endl;
	if (!blur_v->setFloatParam("threshold", 0.3f)) cout << "Threshold failed" << endl;
	if (!blur_v->setVec2Param("dir", 0.0f, 1.0f)) cout << "Dir failed" << endl;
	if (!blur_v->setIntParam("samples", 20)) cout << "Samples failed" << endl;
	use_postprocessor(blur_v);

	do {
		
		render_update();

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ); // Check if the ESC key was pressed or the window was closed

	render_cleanup();
	delete blur_h;

	return 0;
}