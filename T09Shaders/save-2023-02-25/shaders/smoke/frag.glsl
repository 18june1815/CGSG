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
  vec4 tc = texture(Tex, DrawTexCoord);
  OutColor = DrawColor * tc;                                                                    
}