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
    float x = UV.x;
    float y = UV.y;
    float f = 0.25f;
    float dist = (sin(x * PI) + sin(y * PI)) / 2;
    x -= 0.5;
    y -= 0.5;
    float o = sqrt((x * x) + (y * y));
    float theta = asin(o / dist);
    float radius = f * theta;
    float sigma = atan(abs(x) / abs(y));
    float sourceX = radius * sin(sigma);
    float sourceY = radius * cos(sigma);
    if (x < 0) {
        if (y > 0) {
            sourceX *= -1;
        } else {
            sourceX *= -1;
            sourceY *= -1;
        }
    } else if (y < 0) {
        sourceY *= -1;
    }
    sourceX += 0.5;
    sourceY += 0.5;
    sourceY *= -1;
    // Output color = color of the texture at the specified UV
    color = texture( render, vec2(sourceX, sourceY) ).rgb;
    //color = vec3(radius, radius, radius);
}