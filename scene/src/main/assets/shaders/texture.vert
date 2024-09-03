#version 300 es

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUv;

out vec2 uv;

uniform mat4 projectMatrix;

void main() {
    gl_Position = projectMatrix * vec4(aPosition, 1.0);
    uv = aUv;
}