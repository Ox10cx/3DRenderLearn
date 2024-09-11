#version 300 es

precision mediump float;

in vec2 uv;
uniform sampler2D sampler;

out vec4 fragColor;
void main() {
    fragColor = texture(sampler, uv);
}
