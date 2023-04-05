#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 GeomColor[];
in vec2 GeomTexCoord[];
in float VId[];

uniform mat4 MatrWVP;
uniform vec3 CamLoc;
uniform vec3 CamRight;
uniform vec3 CamUp;
uniform float Time;

out vec4 DrawColor;
out vec2 DrawTexCoord;

void main( void )
{
  float s = 0.8 + 0.3 * sin(Time * 5 + VId[0]);
  vec4 p = gl_in[0].gl_Position;
  vec3
    r = CamRight * s,
    u = CamUp * s;

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

  DrawColor = GeomColor[0];
}