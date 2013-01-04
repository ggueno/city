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
uniform float SobelCoef;

out vec4  OutColor;

void main(void)
{
    vec3 color = texelFetch(Color, ivec2(gl_FragCoord.xy), 0).rgb;
    OutColor = vec4(color, 1.0);
}

#endif
