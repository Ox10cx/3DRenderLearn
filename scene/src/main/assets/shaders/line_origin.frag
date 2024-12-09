#version 300 es

precision mediump float;

uniform vec4 u_color;
uniform float v_alpha;

out vec4 fragColor;

void main() {
    fragColor = vec4(1.0, 0.0, 1.0, 1.0);
}