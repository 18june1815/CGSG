#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 MatrWVP;
uniform vec3 CamLoc;
uniform vec3 CamRight;
uniform vec3 CamUp;
uniform float Time;

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
  float size, a = 0;
  float 
    full_time = 5,
    age = mod(Time + Id / 3., full_time) / full_time,
    h = 7 * age;
  vec3 p = vec3(1, h, 1);

  size = 5 * mix(0.3, 1., age) / (age + 1) * pow(age, 0.3);
  vec3
    r = CamRight * size,
    u = CamUp * size;

  DrawColor.a = 
    age < 0.5 ? 1 : mix(1.0, 0.0, (age - 0.5) / 0.5);

  float c_y = 0.5, c_r = 0.8, c_g = 1;
  vec3 
    yellow = vec3(1, 1, 0),
    red = vec3(1, 0, 0),
    grey = vec3(0.5, 0.5, 0.5);

  DrawColor.rgb = 
    age < c_y ? mix(yellow, red, age / c_y) :
    age < c_r ? mix(red, grey, (age - c_y) / (c_r - c_y)) :
    grey;
      

  a = age * (Id % 2 * 2 - 1);
  gl_Position = MatrWVP * vec4(p.xyz + Rot(-1, 1, a) * size, 1);
  DrawTexCoord = vec2(0, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(-1, -1, a) * size, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(1, 1, a) * size, 1);
  DrawTexCoord = vec2(1, 1);
  EmitVertex();
  gl_Position = MatrWVP * vec4(p.xyz + Rot(1, -1, a) * size, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();                                            
  EndPrimitive();   
}