#version 330
layout(location=0) in vec4 in_Position;
uniform mat4 P; //projection matrix
uniform mat4 V; //view matrix
uniform mat4 M; //model matrix
uniform vec4 vertColor; //vertices colors
out vec4 col; //initialized with vertColor then sent though to fragment shader
void main(){
 gl_Position = P * V * M * in_Position;
 col = vertColor;
}