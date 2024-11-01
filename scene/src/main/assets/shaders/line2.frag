#version 300 es

uniform highp vec4 u_color;
uniform lowp float u_blur;
uniform lowp float u_opacity;
uniform lowp float u_device_pixel_ratio;

in vec2 v_normal;
in vec2 v_width2;
in float v_gamma_scale;
in highp float v_linesofar;

out vec4 fragColor;

void main() {
    // Calculate the distance of the pixel from the line in pixels.
    float dist = length(v_normal) * v_width2.s;

    // Calculate the antialiasing fade factor. This is either when fading in
    // the line in case of an offset line (v_width2.t) or when fading out
    // (v_width2.s)
    float blur2 = (u_blur + 1.0 / u_device_pixel_ratio) * v_gamma_scale;
    float alpha = clamp(min(dist - (v_width2.t - blur2), v_width2.s - dist) / blur2, 0.0, 1.0);

    // fragColor = u_color * (alpha * u_opacity);
    fragColor = u_color;

}
