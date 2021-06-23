#version 430

in vec3 vPosition;
in vec3 vColour;

uniform mat4 MVP;

out vec3 colour;

void main () {
   colour = vColour;
   gl_Position = MVP * vec4(vPosition,1.0);
}