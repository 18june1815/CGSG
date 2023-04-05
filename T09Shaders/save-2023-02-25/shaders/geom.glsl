#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 MatrWVP;
uniform vec3 CamLoc;
uniform vec3 CamRight;
uniform vec3 CamUp;

flat in float VId[];
out vec4 DrawColor;
out vec2 DrawTexCoord;
flat out float DrawId;

vec3 Rot( float x, float y, float alpha )
{
  float  
    co = cos(alpha),
    si = sin(alpha);
  return CamRight * (x * co - y * si) + CamUp * (x * si + y * co);
}
void main( void )
{
  int Id = int(VId[0]);
  DrawId = VId[0];

  float s = 1;
  vec3 p = vec3(0, 0, 1);
  vec3
    r = CamRight * s,
    u = CamUp * s;

  DrawColor = vec4(1, 1, 1, 1);

  gl_Position = MatrWVP * vec4(p.xyz - r + u, 1);
  DrawTexCoord = vec2(0, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz - r - u, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + r + u, 1);
  DrawTexCoord = vec2(1, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + r - u, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();                                            
  EndPrimitive();   
}