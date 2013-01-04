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
uniform float Gamma;
uniform float SobelCoef;

out vec4  OutColor;

uniform mat3 G[2] = mat3[](
        mat3( 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 ),
        mat3( 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0 )
);


void main(void)
{
	//vec3 color = texture(Color, uv).rgb;
	vec3 color = texelFetch(Color, ivec2(gl_FragCoord.xy), 0).rgb;

	mat3 I;
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++) {
            vec3 sample  = texelFetch( Color, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;
            I[i][j] = length(sample); 
    }

    /* calculate the convolution values for all the masks */                                                              
	float cnv[2];
    for (int i=0; i<2; i++) {                              
            float dp3 = dot(G[i][0], I[0]) + dot(G[i][1], I[1]) + dot(G[i][2], I[2]);                                     
            cnv[i] = dp3;                            
    }   

    float c =  sqrt(cnv[0]*cnv[0]+cnv[1]*cnv[1]);
    //OutColor = vec4( c, c, c, 1.0);
	//OutColor = vec4(pow(color, vec3(1.0/Gamma)), 1.0);
	OutColor = vec4(pow(color, vec3(1.0/Gamma))- SobelCoef * 0.5 * c, 1.0);

}

#endif
