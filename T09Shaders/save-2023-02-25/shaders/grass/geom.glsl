#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 MatrWVP;
uniform vec3 CamLoc;
uniform vec3 CamRight;
uniform vec3 CamUp;
uniform float Time;

flat in int VId[];
                  
out vec4 DrawColor;
out vec2 DrawTexCoord;
flat out float DrawId;

layout(binding = 1) uniform sampler2D TexH;

float GetHeight( vec3 Pos )
{
  float HeightFieldSize = 2800., HeightFieldH = 30.0, size = 300.0;
  float x, y;

  //x = round((Pos.x + HeightFieldSize / 2.0) / HeightFieldSize);
  //y = round((-Pos.z + HeightFieldSize / 2.0) / HeightFieldSize);

  x = (Pos.x + size / 2.) / size;
  y =  (size / 2. - Pos.z) / size;

  vec4 tc = texture(TexH, vec2(x, y));
  //vec4 tc = texture(TexH, vec2(x, y));
 
  return  10 * tc.r - 1;
}


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
  float size = 0.5, a = 0;
  //vec3 p = vec3(150 - VId[0] % 10, 0, 150 - VId[0] / 10);
  vec3 p = vec3(VId[0] % 10, 0, VId[0] / 10);
  p.y = GetHeight(p);                     

  vec3
    r = CamRight * size,
    u = CamUp * size;

  DrawColor = vec4(0, 0, 0, 1);
   
  gl_Position = MatrWVP * vec4(p.xyz + Rot(-1, 1, a) * size, 1);
  DrawTexCoord = vec2(0, -1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(-1, -1, a) * size, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(1, 1, a) * size, 1);
  DrawTexCoord = vec2(1, -1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(1, -1, a) * size, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();                                            
  EndPrimitive(); 
}