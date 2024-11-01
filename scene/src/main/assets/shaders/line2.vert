#version 300 es


// floor(127 / 2) 等于 63.0
// 目前允许的最大斜接限制是 2.0。挤出法线存储在一个字节中（-128..127）。
// 我们将常规法线缩放到长度 63，但也有一些“特殊”法线具有更大的长度（在这种情况下，最大长度为 126）。
// #define scale 63.0  // 这里的 scale 定义为 63.0，用于缩放法线长度

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

out vec2 v_normal;
out vec2 v_width2;
out float v_gamma_scale;
out highp float v_linesofar;


void main() {
    // 线条边缘逐渐消失的距离。
    // 高分辨率设备需要更小的距离以避免锯齿现象。
    float ANTIALIASING = 1.0 / u_device_pixel_ratio / 2.0;

    vec2 a_extrude = a_data.xy - 128.0;
    float a_direction = mod(a_data.z, 4.0) - 1.0;

    v_linesofar = (floor(a_data.z / 4.0) + a_data.w * 64.0) * 2.0;

    vec2 pos = floor(a_pos_normal * 0.5);

    //  如果它是圆帽形，则x为1，否则为0
    //  如果法线向上，则y为1；如果法线向下，则y为-1
    //  信息存储在a_pos_normal的最低有效位中
    mediump vec2 normal = a_pos_normal - 2.0 * pos;
    normal.y = normal.y * 2.0 - 1.0;
    v_normal = normal;

    mediump float gapwidth = u_gapwidth / 2.0;
    float halfwidth = u_width / 2.0;
    lowp float offset = -1.0 * u_offset;

    float inset = gapwidth + (gapwidth > 0.0 ? ANTIALIASING : 0.0);
    float outset = gapwidth + halfwidth * (gapwidth > 0.0 ? 2.0 : 1.0) + (halfwidth == 0.0 ? 0.0 : ANTIALIASING);

    // 将挤出向量先缩放到单位向量，然后再根据此顶点的线宽进行放大
    mediump vec2 dist = outset * a_extrude * scale;

    // 在绘制实际线条旁边的线条时计算偏移量。
    // 我们通过创建一个指向挤出方向的向量来实现这一点，但是当我们绘制圆形端点（a_direction = -1 或 1）时，
    // 需要旋转这个向量，因为这些圆形端点的挤出向量指向另一个方向。
    mediump float u = 0.5 * a_direction;
    mediump float t = 1.0 - abs(u);
    mediump vec2 offset2 = offset * a_extrude * scale * normal.y * mat2(t, -u, u, t);

    vec4 projected_extrude = u_matrix * vec4(dist / u_ratio, 0.0, 0.0);
    gl_Position = u_matrix * vec4(pos + offset2 / u_ratio, 0.0, 1.0) + projected_extrude;


    // 计算透视视图将挤出部分压缩或拉伸了多少
    float extrude_length_without_perspective = length(dist);
    float extrude_length_with_perspective = length(projected_extrude.xy / gl_Position.w * u_units_to_pixels);
    v_gamma_scale = extrude_length_without_perspective / extrude_length_with_perspective;

    v_width2 = vec2(outset, inset);
}



