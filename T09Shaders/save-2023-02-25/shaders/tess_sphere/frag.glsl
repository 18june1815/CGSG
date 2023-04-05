#version 420

layout(location = 0) out vec4 OutColor;

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

vec3 Shade( vec3 P, vec3 N)
{
  vec3 LightPos = vec3(10, 30, 10);
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
  vec3 L = normalize(LightPos - P);                        

  N = faceforward(N, V, N);
  
  // Ambient
  color = Ka;
  // Diffuse
  color += max(0, dot(N, L)) * Ka;
  // Specular
  vec3 R = reflect(V, N); 

  color += pow(max(0, dot(N, L)), Ph) * Ks;

  return color;
}


void main( void )
{                                                             
  OutColor = vec4(1, 0, 1, 1);
  vec3 color = Shade(vec3(DrawPos), normalize(DrawNormal)); 
  OutColor = vec4(color, 1);
}