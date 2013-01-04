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
uniform int SampleCount;
uniform vec2 Direction;
uniform vec2 TexelSize;

out vec4  OutColor;

void main ()
{
    float weight = 1.0 / (SampleCount * 2);
    vec3 color = vec3(0.0, 0.0, 0.0);
    for(int i=-SampleCount;i<=SampleCount;++i)
    {
        vec2 coord = floor(gl_FragCoord.xy * (2.0 - Direction.y)  ) + i*Direction;
        color += texelFetch(Color,ivec2(coord),0).xyz * weight;
        //vec2 coord = uv + (TexelSize * i * Direction);
        //color += texture(Color, coord).rgb * weight;
    }
    OutColor = vec4(color, 1.0);
    //OutColor = vec4(texture(Color, uv).rgb,1.0);
    //OutColor = vec4(gl_FragCoord.x/ 1024, gl_FragCoord.y / 768, 0.0, 1.0);

}
#endif

