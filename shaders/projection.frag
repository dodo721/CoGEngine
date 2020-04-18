#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D render;
uniform float PI = 3.1415926535897932384626433832795;

void main(){

    // Fisheye Projection
    /*float x = UV.x - 0.5;
    float y = UV.y - 0.5;
    float theta = atan(abs(x) / abs(y));
    float f = 3.5;
    float radius = f * theta;
    float newX = radius * sin(theta);
    float newY = radius * cos(theta);
    newX += 0.5;
    newY += 0.5;*/
    
    float x = UV.x;
    float y = UV.y;
    float f = 3.445f;
    float dist = (sin(x * PI) + sin(y * PI)) / 2;
    x -= 0.5;
    y -= 0.5;
    float o = sqrt((x * x) + (y * y));
    float theta = asin(o / dist);
    float radius = f * theta;
    float sourceX = radius * sin(theta);
    float sourceY = radius * cos(theta);

    // Output color = color of the texture at the specified UV
    color = texture( render, vec2(sourceX, sourceY) ).rgb;
    color = vec3(dist, dist, dist);
}