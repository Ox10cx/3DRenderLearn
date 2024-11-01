uniform highp vec4 u_color;
uniform lowp float u_blur;
uniform lowp float u_opacity;

varying vec2 v_width2;
varying vec2 v_normal;
varying float v_gamma_scale;

void main() {
	float DEVICE_PIXEL_RATIO = 0.01;
    float dist = length(v_normal) * v_width2.s;
    float blur2 = (blur + 1.0 / DEVICE_PIXEL_RATIO) * v_gamma_scale;
    float alpha = clamp(min(dist - (v_width2.t - blur2), v_width2.s - dist) / blur2, 0.0, 1.0);

    gl_FragColor = vec4(1.0, 0, 0, 1.0);
}
