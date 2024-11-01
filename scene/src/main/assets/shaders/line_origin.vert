#version 300 es

precision mediump float;

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_data;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_dir;

float scale = 0.015873016;
float DEVICE_PIXEL_RATIO = 0.05;

uniform float u_halfheight;
uniform float u_width;
uniform float u_gapwidth;

uniform mat4 projectMatrix;


void main() {
     float ANTIALIASING = u_gapwidth/2.0;
     float u_offset = 0.0/u_halfheight;
     float width = u_width;
     float offset = u_offset;
     offset = -1.0 * offset;
     float gapwidth = u_gapwidth;
     vec3 normal = a_normal;
     normal.z = sign(normal.z - 0.5);
     vec2 a_extrude = a_data.xz;
     float a_direction = a_dir.x - 1.0;
     float u = 0.5 * a_direction;
     float t = 1.0 - abs(u);
     vec2 offset2 = offset * a_extrude * normal.z * mat2(t, -u, u, t);
     vec3 offset3 = vec3(offset2.x, 0, offset2.y);

     gapwidth = gapwidth / 2.0;
     float halfwidth = width / 2.0;
     float outset = gapwidth + halfwidth * (gapwidth > 0.0 ? 2.0 : 1.0) + ANTIALIASING;
     vec2 dist = outset * a_extrude;
     vec3 dist3 = vec3(dist.x, 0, dist.y);
     vec4 projected_extrude =  projectMatrix * vec4(dist3, 0.0);
     gl_Position = projectMatrix * vec4(a_pos + offset3, 1.0) + projected_extrude;
}