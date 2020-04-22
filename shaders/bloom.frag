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
uniform float threshold;
uniform vec2 dir;
uniform int samples;

void main(){
    
    color = texture2D(render, UV).rgb;
	if (stDev == 0)
		return;
    else if (length(color) < threshold)
        return;
    
	vec3 blurcolor = vec3(0.0);
	
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
		blurcolor += texture2D(render, vec2(UV.x  + offset*hstep, UV.y + offset*vstep)).rgb * gauss;
	}
	blurcolor = blurcolor / sum;

    if (length(blurcolor) > length(color))
        color = blurcolor;

}