#version 300 es

precision mediump float;

uniform lowp float u_device_pixel_ratio;
uniform highp vec4 u_color;
uniform lowp float u_blur;
uniform lowp float u_opacity;

in vec2 v_width2;
in vec2 v_normal;
in float v_gamma_scale;

out vec4 fragColor;

void main() {
    highp vec4 color = u_color;
    lowp float blur = u_blur;
    lowp float opacity = u_opacity;

    float dist = length(v_normal) * v_width2.s;
    float blur2 = (blur + 1.0 / u_device_pixel_ratio) * v_gamma_scale;
    float alpha = clamp(min(dist - (v_width2.t - blur2), v_width2.s - dist) / blur2, 0.0, 1.0);
    // fragColor = color * (alpha * opacity);

    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
