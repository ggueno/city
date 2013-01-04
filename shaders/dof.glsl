#if defined(VERTEX)
uniform mat4 Projection;

in vec3 VertexPosition;
in vec3 VertexTexCoord;

out vec2 uv;

void main(void)
{	
	uv = VertexTexCoord.xy;
	gl_Position = Projection * vec4(VertexPosition, 1.0);
}

#endif

#if defined(FRAGMENT)

in vec2 uv;

uniform sampler2D Color;
uniform sampler2D Blur;
uniform sampler2D BlurCoef;


out vec4  OutColor;

void main(void)
{
	float blurCoef = texture(BlurCoef, uv).r;
	OutColor = vec4(mix(texture(Color, uv).rgb, texture(Blur, uv).rgb, blurCoef), 1.0);
	//OutColor = vec4(texture(Color, uv).rgb, 1.0);
	//OutColor = vec4(texture(Blur, uv).rgb, 1.0);
	//OutColor = vec4(texture(BlurCoef, uv).rgb, 1.0);
}

#endif
