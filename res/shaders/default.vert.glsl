#version 120

attribute vec2 v_position;
attribute vec3 v_color;
attribute vec2 v_texCoord;

varying vec3 f_color;
varying vec2 f_texCoord;

void main(){
  gl_Position = vec4(v_position, 0.0, 1.0);
  f_color = v_color;
  // f_texCoord = v_texCoord;
  f_texCoord = vec2(v_texCoord.s, 1 - v_texCoord.t);
}
