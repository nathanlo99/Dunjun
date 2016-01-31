#version 120

struct Transform {
  vec3 position;
  vec4 rotation;
  vec3 scale;
};

vec3 quaternionRotate(vec4 q, vec3 v) {
  vec3 t = 2.0f * cross(q.xyz, v);
  return v + q.w * t + cross(q.xyz, t);
}

attribute vec2 v_position;
attribute vec3 v_color;
attribute vec2 v_texCoord;

varying vec3 f_color;
varying vec2 f_texCoord;

uniform Transform u_transform;
uniform mat4 u_camera;

void main(){
  f_color = v_color;
  f_texCoord = v_texCoord;

  vec3 pos = vec3(v_position, 0.0);
  pos = u_transform.scale * pos;
  pos = quaternionRotate(u_transform.rotation, pos);
  pos = u_transform.position + pos;
  gl_Position = u_camera * vec4(pos, 1.0);
}
