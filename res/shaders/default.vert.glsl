#version 120

attribute vec2 v_position;
attribute vec3 v_color;

varying vec3 f_color;

void main(){
  gl_Position = vec4(v_position, 0.0, 1.0);
  f_color = v_color;
}
