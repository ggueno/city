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

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;
uniform sampler2D Fog;

uniform vec3 CameraPosition;
uniform vec3  LightPosition;
uniform vec3  LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;

out vec4  Color;

vec3 directionalLight(vec3 position, in vec3 lcolor, in float intensity, in vec3 ldir, in vec3 n, in vec3 fpos, vec3 diffuse, float spec, vec3 cpos)
{
	vec3 l =  ldir;
	vec3 v = fpos - cpos;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(n, -l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);
	float d = distance(l, position);
	vec3 color = lcolor * intensity * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * 100.0));
	return color;
}

vec3 pointLight(vec3 position, in vec3 lcolor, in float intensity, in vec3 lpos, in vec3 n, in vec3 fpos, vec3 diffuse, float spec, vec3 cpos)
{
	vec3 l =  lpos - fpos;
	vec3 v = fpos - cpos;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);
	float d = distance(l, position);
	float att = clamp(  1.0 /  ( 1 + 0.1 * (d*d)), 0.0, 1.0);
	vec3 color = lcolor * intensity * att * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * 100.0));
	return color;
}

void main(void)
{
	vec4  material = texture(Material, uv).rgba;
	vec4  fog = texture(Fog, uv).rgba;
	vec3  normal = texture(Normal, uv).rgb;
	float depth = texture(Depth, uv).r;
	
	vec2  xy = uv * 2.0 -1.0;
	vec4  wPosition =  vec4(xy, depth * 2.0 -1.0, 1.0) * InverseViewProjection;
	vec3  position = vec3(wPosition/wPosition.w);

	vec3 diffuse = material.rgb;
	float spec = clamp(material.a, 0.01, 1.0);

	vec3 n = normalize(normal);
	vec3 l =  LightPosition - position;

	vec3 v = position - CameraPosition;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);

	float d = distance(LightPosition, position);
	float att = clamp(  1.0 / ( 1.0 + 1.0 * (d*d)), 0.0, 1.0);

	vec3 color = LightColor * LightIntensity * att * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * 100.0));



	vec3 cdirlight1 = directionalLight(vec3(0.2, 0.5, 1.0),vec3(1.0, 1.0, 0.8), 0.1, vec3(0.0, -1.0, 2.0), n, position, diffuse, spec, CameraPosition );
    vec3 cdirlight2 = directionalLight(vec3(1.0, 0.0, 0.0),vec3(1.0, 0.8, 0.5), 0.1, vec3(0.0, -1.0, -2.0), n, position, diffuse, spec, CameraPosition );
    vec3 cpointlight1 = pointLight(position,vec3(1.0, 0.5, 0.0), 0.8, vec3(0.0, -5.0, -5.0), n, position, diffuse, spec, CameraPosition );
    vec3 cpointlight2 = pointLight(position,vec3(1.0, 0.3, 0.1), 2.8, vec3(12.0, -5.0, 13.0), n, position, diffuse, spec, CameraPosition );
    vec3 cpointlight3 = pointLight(position,vec3(0.8, 0.4, 0.1), 1.0, vec3(-28.0, -5.0, -20.0), n, position, diffuse, spec, CameraPosition );
    vec3 cpointlight4 = pointLight(position,vec3(0.5, 0.7, 0.2), 2.0, vec3(-14.0, -3.0, 36.0), n, position, diffuse, spec, CameraPosition );
	Color = fog+vec4(color+cdirlight1+cpointlight1+cdirlight2, 1.0);


	//Color = vec4(color, 1.0) + fog;
	//Color = fog;
	//Color = material;
	//Color = vec4(depth, 0.0 , 0.0, 1.0);
	//Color = vec4(normal, 1.0);
}

#endif
