#version 300 es
precision mediump float;

const float scale = 0.015873016;

layout(location = 0)   in vec2 a_pos;
layout(location = 1)   in vec2 a_data;
layout(location = 2)   in vec2 a_execute_normal;
layout(location = 3)   in vec2 a_dir;

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
    mediump float gapwidth = u_gapwidth;
    lowp float offset = u_offset;
    mediump float width = u_width;

    mediump float ANTIALIASING = 1.0 / u_device_pixel_ratio / 2.0 / u_half_height;

    vec2 a_extrude = a_execute_normal.xy - 128.0;

    float a_direction = mod(a_dir.x, 4.0) - 1.0;

    vec2 data = floor(a_data.xy * 0.5);
    mediump vec2 normal = a_data.xy - 2.0 * data;
    normal.y = normal.y * 2.0 - 1.0;
    v_normal = normal;

    gapwidth = gapwidth / 2.0;
    float halfwidth = width / 2.0;
    offset = -1.0 * offset;

    float inset = gapwidth + (gapwidth > 0.0 ? ANTIALIASING : 0.0);
    float outset = gapwidth + halfwidth * (gapwidth > 0.0 ? 2.0 : 1.0) + (halfwidth == 0.0 ? 0.0 : ANTIALIASING);

    mediump vec2 dist = outset * a_extrude * scale;

    mediump float u = 0.5 * a_direction;
    mediump float t = 1.0 - abs(u);


    mediump vec2 offset2 = offset * a_extrude * scale * normal.y * mat2(t, -u, u, t);

    vec2 distRatio = dist / u_ratio;
    vec4 projected_extrude =  u_matrix * vec4(distRatio, 0.0, 0.0);


    vec2 offsetRatio = a_pos.xy + offset2 / u_ratio;
    gl_Position = u_matrix * vec4(offsetRatio.x, offsetRatio.y, 0.0, 1.0) + projected_extrude;

    float extrude_length_without_perspective = length(dist);
    float extrude_length_with_perspective = length(projected_extrude.xy / gl_Position.w * u_units_to_pixels);
    v_gamma_scale = extrude_length_without_perspective / extrude_length_with_perspective;
    v_width2 = vec2(outset, inset);
}