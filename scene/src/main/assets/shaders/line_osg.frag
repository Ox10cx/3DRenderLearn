#version 300 es
precision mediump float;

uniform lowp float u_device_pixel_ratio;
uniform highp vec4 u_color;
uniform lowp float u_blur;
uniform lowp float u_opacity;

in mediump vec2 v_normal;
in mediump float v_gamma_scale;
in mediump vec2 v_width2;

out vec4 fragColor;

void main() {
    highp vec4 color = u_color;
    lowp float blur = u_blur;
    lowp float opacity = u_opacity;

    mediump float dist = length(v_normal) * v_width2.s;
    mediump float blur2 = (blur + 1.0 / u_device_pixel_ratio) * v_gamma_scale;
    mediump float alpha = clamp(min(dist - (v_width2.t - blur2), v_width2.s - dist) / blur2, 0.0, 1.0);

    // fragColor = color * (alpha * opacity);

     fragColor = color;
}