#version 430

layout(quads) in;

uniform mat4 MatrWVP;

out vec3 DrawNormal;
out vec3 DrawPos;

void main (void)
{
  float R = 3.0;
       
  float x = gl_TessCoord.x * 3.14 * 2;
  float y = gl_TessCoord.y * 3.14;

  vec4 p = vec4(sin(y) * sin(x), cos(y), sin(y) * cos(x), 0);
  
 
  gl_Position = MatrWVP * (gl_in[0].gl_Position); 
  //gl_Position = MatrWVP * (gl_in[0].gl_Position + vec4(gl_TessCoord.x, gl_TessCoord.y, 0, 0)); 
  gl_Position = MatrWVP * (gl_in[0].gl_Position + p * R);                   
  DrawNormal = p.xyz;
  DrawPos = p.xyz * R;
  //gl_Position = MatrWVP * (mix(vec4(-1, -gl_TessCoord.y, 0, 1), vec4(1, -gl_TessCoord.y, 0, 1), gl_TessCoord.x)); 
}
