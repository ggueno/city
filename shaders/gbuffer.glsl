#if defined(VERTEX)
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Object;

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec2 uv;
out vec3 normal;
out vec3 position;
out vec4 vEyeSpacePos;

void main(void)
{	
	uv = VertexTexCoord;
	normal = vec3(Object * vec4(VertexNormal, 1.0));; 
	position = vec3(Object * vec4(VertexPosition, 1.0));
	//position.x += (gl_InstanceID % 8) * 1.5; 
	//position.y += (gl_InstanceID % 4) * 1.5; 
	//position.z += (int(gl_InstanceID / 8) * 1.5); 

	vEyeSpacePos = View * Object * vec4(VertexPosition,1.0);
    
	gl_Position = Projection * View * vec4(position, 1.0);
}

#endif

#if defined(FRAGMENT)
uniform vec3 CameraPosition;
uniform float Time;

in vec2 uv;
in vec3 position;
in vec3 normal;
in vec4 vEyeSpacePos;

uniform sampler2D Diffuse;
uniform sampler2D Spec;

uniform float fogStart;
uniform float fogEnd;
uniform float fogDensity;

out vec4  Color;
out vec4  Normal;
out vec4  Fog;

struct FogParameters
{
   vec4 vFogColor; // Fog color
   float fStart; // This is only for linear fog
   float fEnd; // This is only for linear fog
   float fDensity; // For exp and exp2 equation
   int iEquation; // 0 = linear, 1 = exp, 2 = exp2
} fogParams;

float getFogFactor(FogParameters params, float fFogCoord)
{
   float fResult = 0.0;
   if(params.iEquation == 0)
      fResult = (params.fEnd-fFogCoord)/(params.fEnd-params.fStart);
   else if(params.iEquation == 1)
      fResult = exp(-params.fDensity*fFogCoord);
   else if(params.iEquation == 2)
      fResult = exp(-pow(params.fDensity*fFogCoord, 2.0));

   fResult = 1.0-clamp(fResult, 0.0, 1.0);

   return fResult;
}

void main(void)
{
	vec3 diffuse = texture(Diffuse, uv).rgb;
	float spec = texture(Spec, uv).r;

	
  	float fFogCoord = abs(vEyeSpacePos.z/vEyeSpacePos.w);

    FogParameters fparams;
    fparams.vFogColor = vec4(167f/255.f, 194/255f, 1.0f, 0.9f);
    fparams.fStart = fogStart;
    fparams.fEnd = fogEnd;
    fparams.fDensity = fogDensity;
    fparams.iEquation = 2;

	Color = vec4(diffuse, spec);
	Normal = vec4(normal, spec);
	Fog = mix(vec4(0.0,0.0,0.0,0.0),fparams.vFogColor, getFogFactor(fparams,fFogCoord));
}

#endif
