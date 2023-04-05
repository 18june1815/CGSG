#version 420

layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutColor1;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform float Time;
uniform vec3 CamLoc;
uniform mat4 ShadowMatr;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
uniform float Trans;


layout(binding = 0) uniform sampler2D Tex;
layout(binding = 1) uniform sampler2D ShadowMap;

uniform bool IsTexture0;

vec3 Shade( vec3 P, vec3 N)
{
  vec3 LightPos = vec3(10, 30, 10);
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
  vec3 L = normalize(LightPos - P);                        

  N = faceforward(N, V, N);

  vec3 tex = vec3(0);
  
  if (IsTexture0)
  {
    vec4 tc = texture(Tex, DrawTexCoord);
    tex = vec3(tc);
  }
  else
    tex = Ka;

  
  // Ambient
  color = tex;
  // Diffuse
  color += max(0, dot(N, L)) * tex;
  // Specular
  vec3 R = reflect(V, N); 
  //R = V - 2.0 * dot(N, V) * N;
  //R = dot(N, V) * N;

  color += pow(max(0, dot(N, L)), Ph) * Ks;
  //color = P * 0.5 + 0.5;

  return color;//
  //return N * 0.5 + 0.5; //vec3(dot(N, L)) * 0.5 + 0.5;

}

void main( void )
{                                                             
  OutColor = DrawColor + 0.3 * sin(Time * 0.5);
  vec3 color = Shade(vec3(DrawPos), normalize(DrawNormal)); 

  float sh = 1, s;
  vec4 p = ShadowMatr * vec4(DrawPos, 1) * 0.5 + 0.5;
  if (p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x <= 1 && p.y <= 1 && p.z <= 1)
  {
    sh = 0.8;
    s = texture(ShadowMap, p.xy).r;
    float b = 0.01;
    //s = (s - (1 - b)) / b;

    //sh = s;
    if (p.z > s)
      sh = 0.30;
  }
  OutColor = vec4(color * sh, Trans);

  if (all(equal(DrawNormal, vec3(0, 0, 0))))
    OutColor1 = vec4(0.5, 0.5, 0., 1.);
  else 
    OutColor1 = vec4(normalize(DrawNormal), 1);

  //OutColor = vec4(s, s, s, Trans);

//  OutColor = vec4(0, 0, 1, 1);
}