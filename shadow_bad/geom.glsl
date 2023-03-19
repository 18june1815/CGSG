uniform float Time;

out vec2 DrawTexCoord;

void main( void )
{
  float s = 0.3;
  mat4 m = 
    mat4(vec4(s, 0, 0, 0),
         vec4(0, s, 0, 0),
         vec4(0, 0, s, 0),
         vec4(1 - s, 1 - s, 0, 1));
  
  gl_Position = m * vec4(-1, 1, 0, 1);
  DrawTexCoord = vec2(0, 1);
  EmitVertex();

  gl_Position = m * vec4(-1, -1, 0, 1);
  DrawTexCoord = vec2(0, 0);
  EmitVertex();  

  gl_Position = m * vec4(1, 1, 0, 1);
  DrawTexCoord = vec2(1, 1);
  EmitVertex();

  gl_Position = m * vec4(1, -1, 0, 1);
  DrawTexCoord = vec2(1, 0);
  EmitVertex();

  EndPrimitive();
}