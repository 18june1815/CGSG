#version 330

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;
                     

uniform mat4 MatrWVP;
uniform mat4 MatrW;
uniform mat4 MatrWInv;
uniform float Time;

out vec4 GeomColor;
out vec3 DrawNormal;
out vec3 DrawPos;
out vec2 GeomTexCoord;
out float VId;

void main ( void )
{
  VId = gl_VertexID;

  vec3 inp = InPosition;
  if (inp.y < 2)
    inp.y = 2;

  gl_Position = vec4(inp, 1); 
  GeomColor = InColor;
  GeomColor.a = 1;
  /*if (InPosition.y < 2)
    GeomColor.a = 1 - (2 - InPosition.y) / 2;
  else
    GeomColor.a = 1;
    */
  DrawPos = vec3(MatrW * vec4(InPosition, 1));
  
  DrawNormal = InNormal;
  DrawNormal = transpose(mat3(MatrWInv)) * InNormal;
  GeomTexCoord = InTexCoord;
}