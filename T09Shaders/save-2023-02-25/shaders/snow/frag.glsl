#version 420

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform float Time;
uniform float Trans;

layout(binding = 0) uniform sampler2D Tex;
uniform bool IsTexture0;

void main( void )
{                
  OutColor = DrawColor;
  OutColor = vec4(1, 1, 0, 0.3);
                                                                    
  vec4 tc = texture(Tex, DrawTexCoord);
  if (tc.a < 0.5)
    discard;
  OutColor = vec4(tc.rgb, 1);	
}