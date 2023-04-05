#version 330

flat out int VId;

void main ( void )
{
  VId = gl_VertexID;
  gl_Position = vec4(0, 0, 0, 1);
}