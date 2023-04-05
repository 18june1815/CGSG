#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec3 CamRight, CamUp, CamDir;
uniform float Time;
uniform float FrameW, FrameH;

out vec4 DrawColor;
out vec2 DrawTexCoord;

void main( void )
{
  gl_Position = vec4(-1, 1, 0, 1);
  DrawTexCoord = vec2(0, 1);
  EmitVertex();
  gl_Position = vec4(-1, -1, 0, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();
  gl_Position = vec4(1, 1, 0, 1);
  DrawTexCoord = vec2(1, 1);
  EmitVertex();
  gl_Position = vec4(1, -1, 0, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();                                            
  EndPrimitive();   
}