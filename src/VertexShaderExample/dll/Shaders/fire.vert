#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in int enable;

out vec2 TexCoord; // To Fragment Shader
out float wanna_color;
out float is_enable;

uniform mat4 Projection;
uniform mat4 ModelView;
out vec3 pos;

void main() {
  TexCoord = texcoord;
  is_enable = float(enable);
  pos = position;
  gl_Position = Projection * ModelView * vec4(position, 1.0);
}
