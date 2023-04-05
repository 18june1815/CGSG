#version 420

layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutColor1;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform vec3 CamRight, CamUp, CamDir;
uniform float FrameW, FrameH, ProjDist;
uniform float Time;

layout(binding = 0) uniform sampler2D Tex;
uniform bool IsTexture0;

void main( void )
{            
  float Wp = ProjDist, Hp = ProjDist;
  if (FrameW > FrameH)
    Wp *= FrameW / FrameH;
  else
    Hp *= FrameH / FrameW;
   
  vec3 Fwd = 
    normalize(CamDir * ProjDist + 
              CamRight * (gl_FragCoord.x * Wp / FrameW - Wp /2) +
              CamUp * (gl_FragCoord.y * Hp / FrameH - Hp /2));
  float pi = acos(-1);
  vec2
    thephi = vec2(atan(Fwd.x, Fwd.z) / (2 * pi) + Time * 0.01,
                  1 - acos(Fwd.y) / pi);
   
  vec4 tc = texture(Tex, thephi);
  OutColor = tc;                                                                    
  OutColor1 = vec4(Fwd, 1);                                                                    
}