#version 150 
out vec4 outputColor;
uniform float time;
uniform vec2 resolution;

 

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void main() {

  vec2 st = 0.03*resolution.xy;
    
  vec2 p = (gl_FragCoord.xy *2.0 - resolution) /min (resolution.x, resolution.y);
  float rnd = random( st );
    //movement maybe 
     vec2 translate = vec2(cos(time),sin(time));
    st += translate*0.35;

  vec3 color = vec3(0.0);

  vec2 t = vec2(p.x, p.y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);
  float r = 0.09/length (p - translate) *3.9 ;
  vec3 c = vec3(smoothstep(0.03, 1.0, r),smoothstep(0.03,1.0,r),smoothstep(0.03,1.0,r));
  color += c ;
 
  outputColor = vec4(color, 1.0);
}