#version 410 core
layout (location = 0) in vec3 aPos;
// Answer_3:
// Can also just change the location = 0 to achieve the postion value as colour effect.
layout (location = 1) in vec3 aColour;

out vec3 ourColour;

// Answer_1:
uniform float xOffset;

void main()
{
    // Answer_2: change the aPos.y to negative
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
    ourColour = aColour;
    // Answer_3:
    ourColour = aPos;
}
