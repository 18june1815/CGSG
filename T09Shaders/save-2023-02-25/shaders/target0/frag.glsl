#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D Tex0;
layout(binding = 1) uniform sampler2D Tex1;
uniform float Time;

void main( void )
{ 
  ivec2 screen = ivec2(gl_FragCoord.xy);           
  vec4 tc = texelFetch(Tex0, screen, 0);
  vec4 tc1 = texelFetch(Tex1, screen, 0);

  //OutColor = vec4(pow(tc.xyz, vec3(0.5)), 1);
 
  //OutColor = vec4(pow(tc.xyz, vec3(0.1)), 1);
  OutColor = vec4(tc.xyz + tc1.xyz / 2., 1);
  //OutColor = vec4(1, 0, 0, 1);
}
