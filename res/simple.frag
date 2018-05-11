#version 330 core

uniform vec4 ourColour;

out vec4 FragColor;

void main()
{
    FragColor = ourColour;
}