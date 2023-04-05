#version 420
layout(location = 0) out vec4 OutColor;

in vec2 DrawTexCoord;

uniform float Time;

layout(binding = 0) uniform sampler2D Texture0;
uniform bool IsTexture0;

void main( void )
{
  if (IsTexture0)
  {
    vec4 tc = texture(Texture0, DrawTexCoord);
    float s = tc.r, b = 0.1;
    
    s = (s - (1 - b)) / b;
//    s = 1 - s;
    OutColor = vec4(s, s, s, 1);
    return;
  } 
  OutColor = vec4(1, 1, 1, 0.47);
}
