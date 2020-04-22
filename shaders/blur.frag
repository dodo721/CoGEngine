#version 330 core
#define PI 3.14159265359
#define E 2.71828182846

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D render;
uniform float resolution;
uniform float radius;
uniform float stDev;
uniform vec2 dir;
uniform int samples;

void main(){
    
	if (stDev == 0) {
		color = texture2D(render, UV).rgb;
		return;
	}
    //this will be our RGBA color
	color = vec3(0.0);
	
	//the amount to blur, i.e. how far off center to sample from 
	//1.0 -> blur by one pixel
	//2.0 -> blur by two pixels, eUV.
	float blur = radius/resolution; 
    
	//the direction of our blur
	//(1.0, 0.0) -> x-axis blur
	//(0.0, 1.0) -> y-axis blur
	float hstep = dir.x;
	float vstep = dir.y;
    
	//apply blurring, using a 9-tap filter with predefined gaussian weights
    
	float sum = 0;

	for (int i = -samples / 2; i < samples / 2; i++) {
		float offset = i * blur;
		float stDevSquared = stDev * stDev;
		float gauss = (1 / sqrt(2*PI*stDevSquared)) * pow(E, -((offset*offset)/(2*stDevSquared)));
		sum += gauss;
		color += texture2D(render, vec2(UV.x  + offset*hstep, UV.y + offset*vstep)).rgb * gauss;
	}
	color = color / sum;
	/*
	color += texture2D(render, vec2(UV.x - 4.0*blur*hstep, UV.y - 4.0*blur*vstep)).rgb * 0.0162162162;
	color += texture2D(render, vec2(UV.x - 3.0*blur*hstep, UV.y - 3.0*blur*vstep)).rgb * 0.0540540541;
	color += texture2D(render, vec2(UV.x - 2.0*blur*hstep, UV.y - 2.0*blur*vstep)).rgb * 0.1216216216;
	color += texture2D(render, vec2(UV.x - 1.0*blur*hstep, UV.y - 1.0*blur*vstep)).rgb * 0.1945945946;
	
	color += texture2D(render, vec2(UV.x, UV.y)).rgb * 0.2270270270;
	
	color += texture2D(render, vec2(UV.x + 1.0*blur*hstep, UV.y + 1.0*blur*vstep)).rgb * 0.1945945946;
	color += texture2D(render, vec2(UV.x + 2.0*blur*hstep, UV.y + 2.0*blur*vstep)).rgb * 0.1216216216;
	color += texture2D(render, vec2(UV.x + 3.0*blur*hstep, UV.y + 3.0*blur*vstep)).rgb * 0.0540540541;
	color += texture2D(render, vec2(UV.x + 4.0*blur*hstep, UV.y + 4.0*blur*vstep)).rgb * 0.0162162162;*/

}