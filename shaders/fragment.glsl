
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TextCoord;
// uniform vec4 ourColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    FragColor = mix(texture(ourTexture, TextCoord), texture(ourTexture2, TextCoord), 0.2);
} 