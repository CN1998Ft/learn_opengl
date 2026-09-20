#version 410 core
out vec4 FragColour;

in vec3 ourColour;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    // FragColour = texture(texture1, TexCoord) * vec4(ourColour, 1.0);
}
