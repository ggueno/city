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

uniform sampler2D Depth;
uniform mat4 InverseProjection;
uniform vec3 Focus;

out vec4  Color;

void main(void)
{
    float depth = texture(Depth, uv).r;
    vec2  xy = uv * 2.0 -1.0;
    vec4  wViewPos =  vec4(xy, depth * 2.0 -1.0, 1.0) * InverseProjection;
    vec3  viewPos = vec3(wViewPos/wViewPos.w);
    float viewDepth = -viewPos.z;
    if( viewDepth < Focus.x )
        Color = vec4( clamp( abs( (viewDepth - Focus.x) / Focus.y ), 0.0, 1.0), 0.0, 0.0, 1.0 );
    else
        Color = vec4( clamp( abs( (viewDepth - Focus.x) / Focus.z ), 0.0, 1.0), 0.0, 0.0, 1.0 );
    //Color = vec4(depth, 0.0, 0.0, 1.0);
    //Color = vec4(-viewDepth, 0.0, 0.0, 1.0);
}

#endif
