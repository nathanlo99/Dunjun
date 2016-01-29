#version 120

attribute vec2 v_position;
attribute vec3 v_color;
attribute vec2 v_texCoord;

varying vec3 f_color;
varying vec2 f_texCoord;

uniform mat4 u_model;

void main(){
  f_color = v_color;
  f_texCoord = v_texCoord;
  gl_Position = u_model * vec4(v_position, 0.0, 1.0);
}
