#version 430

in vec2 TexCoord; // From vertex shader
in float is_enable;
in vec3 pos;
out vec4 frag_color;

uniform sampler2D FireTexture;

const vec3 RED = vec3(1.0, 0.0, 0.0);
const vec3 GREEN = vec3(0.0, 1.0, 0.0);
const vec3 BLUE = vec3(0.0, 0.0, 1.0);
uniform int Opt;

const vec3 center = vec3(0.0, 0.0, -15.0);

void main() {
    
    vec4 alpha = texture2D(FireTexture, TexCoord).aaaa;
    vec4 color = texture2D(FireTexture, TexCoord);
    frag_color = vec4(
        color[0]*alpha[0],
        color[1]*alpha[1],
        color[2]*alpha[2],
        color[3]*alpha[3]
    );

    frag_color = texture2D(FireTexture, TexCoord);

    vec3 offset = pos - center;
    float radius = sqrt(
        offset[0]*offset[0]+
        offset[1]*offset[1]
        //+offset[2]*offset[2]
    );

    if (Opt == 3) {
        if(radius < 5.0f){
            float module = max(5.0f-radius, 0.0f) ;/// 10.0f;
            frag_color.r *= module;
            frag_color.g *= module;
            frag_color.b *= module*3.0;
        } else if (radius > 15.0f && radius < 20.0f) {
            float module = max(radius-15.0f, 0.0f) ;/// 10.0f;
            frag_color.r *= module;
            frag_color.g *= module;
            frag_color.b *= module*3.0;
        } else {
            float module = max(20.0f-radius, 0.0f) / 10.0f;
            frag_color.r *= module;
            frag_color.g *= module;
            frag_color.b *= module;
        } 
        
        if(abs(offset[2]) > 25.0f) discard;
    }

    if(abs(is_enable) <= 0.1f || frag_color.a < 0.1f) discard;

}
