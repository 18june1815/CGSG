#version 430

//layout(isolines) in;
layout(quads) in;

uniform mat4 MatrWVP;

void main (void)
{
  //gl_Position = MatrWVP * (gl_in[0].gl_Position * gl_TessCoord.x); 
  gl_Position = MatrWVP * (mix(vec4(-1, -gl_TessCoord.y, 0, 1), vec4(1, -gl_TessCoord.y, 0, 1), gl_TessCoord.x)); 
}
