#version 420

layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutColor1;

in vec3 DrawPos;
in vec2 DrawTexCoord;

layout(binding = 0) uniform sampler2D Tex;
uniform bool IsTexture0;

void main( void )
{           
  vec4 tc = texture(Tex, DrawTexCoord);                                                      
  if (tc.a < 0.5)
    discard;
  OutColor = tc;
  OutColor1 = vec4(1, 0, 0, 1);

}
