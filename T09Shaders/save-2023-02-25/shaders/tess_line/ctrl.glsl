#version 430

layout(vertices = 4) out;

void main (void)
{
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  gl_TessLevelOuter[0] = 30;
  gl_TessLevelOuter[1] = 47;
  gl_TessLevelOuter[2] = 47;
  gl_TessLevelOuter[3] = 47;
  gl_TessLevelInner[0] = 47;
  gl_TessLevelInner[1] = 47;
}