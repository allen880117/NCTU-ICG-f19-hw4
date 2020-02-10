#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in int  enable;
layout(location = 3) in vec3 normal;

out vec2 TexCoord; // To Fragment Shader
out float wanna_color;
out float is_enable;

uniform mat4 OriginModelView;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform int Opt;
uniform float Xpos;

out vec3 N;
out vec3 V;
out vec3 Lp;

void main() {
  mat4 NormalMatrix = transpose(inverse(ModelView));

  TexCoord = texcoord;
  is_enable = float(enable);
  gl_Position = Projection * ModelView * vec4(position, 1.0);

  N = normalize(vec3(transpose(inverse(ModelView)) * vec4(normal, 1.0f)));
  V = vec3(ModelView * vec4(position, 1.0f));
  if(Opt == 0){
    Lp = vec3(OriginModelView * vec4(0, 0, 30, 1.0f));
  } else if (Opt == 1){
    Lp = vec3(OriginModelView * vec4(Xpos, 0, 20, 1.0f));
  } else if (Opt == 2){
    Lp = vec3(OriginModelView * vec4(Xpos, 0, -15, 1.0f));
  }
}
