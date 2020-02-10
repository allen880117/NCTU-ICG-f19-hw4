#version 430

in vec2 TexCoord; // From vertex shader
in float  is_enable;
out vec4 frag_color;

uniform sampler2D EarthTexture;
uniform int Opt;

const vec3 RED = vec3(1.0, 0.0, 0.0);
const vec3 GREEN = vec3(0.0, 1.0, 0.0);
const vec3 BLUE = vec3(0.0, 0.0, 1.0);

in vec3 N;
in vec3 V;
in vec3 Lp;

void main() {
    vec3 L = normalize(Lp-V);

    frag_color = texture2D(EarthTexture, TexCoord);
    if(abs(is_enable) <= 0.1f || frag_color.a < 0.1f) discard;

    if(Opt == 0) {
        if(dot(L, N) > 0.0) {
            frag_color.r *= 2.5;
            frag_color.g *= 1.5;
            frag_color.b *= 1.2;
            frag_color *= smoothstep(0, 0.12, dot(L, N));
        }
    } else if (Opt == 1 || Opt == 2 || Opt == 3) {
        frag_color.r *= 0.5;
        frag_color.g *= 0.5;
        frag_color.b *= 0.5;

        if(dot(L, N) > 0.0) {
            frag_color.r *= 2.5;
            frag_color.g *= 1.5;
            frag_color.b *= 1.2;
            frag_color *= smoothstep(0,0.12, dot(L, N));
        }

        if( abs(dot(V, N)) <= 5.0 ){
            frag_color = vec4(0.0, 1.0, 1.0, 1.0);
        }
    }
}
