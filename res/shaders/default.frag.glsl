#version 120

uniform sampler2D u_tex;

varying vec3 f_color;
varying vec2 f_texCoord;

void main() {
  vec3 texColor = texture2D(u_tex, f_texCoord).rgb;
  vec3 gamma = vec3(1.0/2.2);
  vec3 color = texColor * f_color;
  gl_FragColor = vec4(pow(color, gamma), 1.0);
}
