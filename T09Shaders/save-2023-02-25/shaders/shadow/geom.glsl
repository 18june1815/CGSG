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

void main( void )
{
  float size = 5, a = 0;
  float s = 0.3;
  mat4 m = 
    mat4(vec4(s, 0, 0, 0),
         vec4(0, s, 0, 0),
         vec4(0, 0, s, 0),
         vec4(1 - s, 1 - s, 0, 1));

    
  gl_Position = MatrWVP * m * vec4(-1, 1, 0, 1);
  DrawTexCoord = vec2(0, 1);
  EmitVertex();
  gl_Position = MatrWVP * m * vec4(-1, -1, 0, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();
  gl_Position = MatrWVP * m * vec4(1, 1, 0, 1);
  DrawTexCoord = vec2(1, 1);
  EmitVertex();
  gl_Position = MatrWVP * m * vec4(1, -1, 0, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();                                            
  EndPrimitive(); 
}