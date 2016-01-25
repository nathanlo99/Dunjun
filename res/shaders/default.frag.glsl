#version 120

uniform sampler2D u_tex;

varying vec3 f_color;
varying vec2 f_texCoord;

void main() {
  vec3 texColor = texture2D(u_tex, f_texCoord).rgb;
  gl_FragColor = vec4(texColor * f_color, 1.0);
}
