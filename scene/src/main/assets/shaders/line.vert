
float DEVICE_PIXEL_RATIO = 0.01;
float ANTIALIASING = 1.0/ DEVICE_PIXEL_RATIO / 2.0;
float scale = 0.015873016;

attribute vec2 a_pos;
attribute vec4 a_data;

uniform mat4 u_matrix;
uniform mediump float u_ratio;
uniform vec2 u_gl_units_to_pixels;
uniform highp vec4 u_color;
uniform lowp float u_blur;
uniform lowp float u_opacity;
uniform mediump float u_gapwidth;
uniform lowp float u_offset;
uniform mediump float u_width;

varying vec2 v_normal;
varying vec2 v_width2;
varying float v_gamma_scale;

void main() {
    highp vec4 color = u_color;
    lowp float blur = u_blur;
    lowp float opacity = u_opacity;
    mediump float gapwidth = u_gapwidth;
    lowp float offset = u_offset;

    vec2 a_extrude = a_data.xy - 128.0;
    float a_direction = mod(a_data.z, 4.0) - 1.0;
    mediump vec2 normal = mod(a_pos, 2.0);
    normal.y = sign(normal.y - 0.5);
    v_normal = normal;

    gapwidth = gapwidth / 2.0;
    float halfwidth = width / 2.0;
    offset = -1.0 * offset;

    float inset = gapwidth + (gapwidth > 0.0 ? ANTIALIASING : 0.0);
    float outset = gapwidth + halfwidth * (gapwidth > 0.0 ? 2.0 : 1.0) + ANTIALIASING;

    mediump vec2 dist = outset * a_extrude * scale;
    mediump float u = 0.5 * a_direction;
    mediump float t = 1.0 - abs(u);
    mediump vec2 offset2 = offset * a_extrude * scale * normal.y * mat2(t, -u, u, t);

    vec2 pos = floor(a_pos * 0.5);

    vec4 projected_extrude = u_matrix * vec4(dist / u_ratio, 0.0, 0.0);
    gl_Position = u_matrix * vec4(pos + offset2 / u_ratio, 0.0, 1.0) + projected_extrude;

    float extrude_length_without_perspective = length(dist);
    float extrude_length_with_perspective = length(projected_extrude.xy / gl_Position.w * u_gl_units_to_pixels);
    v_gamma_scale = extrude_length_without_perspective / extrude_length_with_perspective;
    v_width2 = vec2(outset, inset);
}