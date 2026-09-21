#version 410 core
out vec4 FragColour;

in vec3 ourColour;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixture;

void main()
{
    // Answer 1, the texture can take two arguments, 1st sampler, 2nd is the vec/float pointer
    // FragColour = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x, TexCoord.y)), 0.2);
    FragColour = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y)), mixture);
    // FragColour = texture(texture1, TexCoord) * vec4(ourColour, 1.0);
}
