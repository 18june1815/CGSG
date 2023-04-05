#version 330

layout(location = 0) in vec3 InPosition;                     
uniform mat4 MatrW;

flat out float VId;
out vec3 DrawPos;

void main ( void )
{
  VId = gl_VertexID;
  gl_Position = vec4(InPosition, 1); 
  DrawPos = vec3(MatrW * vec4(InPosition, 1));
}