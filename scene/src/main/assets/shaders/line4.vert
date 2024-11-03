#version 300 es
precision mediump float;

#define scale 0.015873016


layout(location = 0) in vec2 a_pos_normal;
layout(location = 1) in vec4 a_data;


uniform mat4 u_matrix;
uniform mediump float u_ratio;
uniform vec2 u_units_to_pixels;
uniform lowp float u_device_pixel_ratio;

uniform mediump float u_gapwidth;
uniform lowp float u_offset;
uniform mediump float u_width;
uniform mediump float u_half_height;

out mediump vec2 v_normal;
out mediump float v_gamma_scale;
out mediump vec2 v_width2;


void main() {
    mediump float ANTIALIASING = 1.0 / u_device_pixel_ratio / 2.0 / u_half_height;

    vec2 a_extrude = a_data.xy - 128.0;
    float a_direction = mod(a_data.z, 4.0) - 1.0;

    vec2 pos = floor(a_pos_normal * 0.5);

    mediump vec2 normal = a_pos_normal - 2.0 * pos;
    normal.y = normal.y * 2.0 - 1.0;
    v_normal = normal;

    mediump float gapwidth = u_gapwidth / 2.0;
    float halfwidth = u_width / 2.0;
    lowp float offset = -1.0 * u_offset;


    float inset = gapwidth + (gapwidth > 0.0 ? ANTIALIASING : 0.0);
    float outset = gapwidth + halfwidth * (gapwidth > 0.0 ? 2.0 : 1.0) + (halfwidth == 0.0 ? 0.0 : ANTIALIASING);

    mediump vec2 dist = outset * a_extrude * scale;

    mediump float u = 0.5 * a_direction;
    mediump float t = 1.0 - abs(u);
    mediump vec2 offset2 = offset * a_extrude * scale * normal.y * mat2(t, -u, u, t);

    vec4 projected_extrude =  u_matrix * vec4(dist / u_ratio, 0.0, 0.0);

    gl_Position = u_matrix * vec4(pos + offset2 / u_ratio , 0.0, 1.0) + projected_extrude;


    float extrude_length_without_perspective = length(dist);
    float extrude_length_with_perspective = length(projected_extrude.xy / gl_Position.w * u_units_to_pixels);
    v_gamma_scale = extrude_length_without_perspective / extrude_length_with_perspective;
    v_width2 = vec2(outset, inset);
}