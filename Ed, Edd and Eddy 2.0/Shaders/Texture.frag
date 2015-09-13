varying vec3 N;
varying vec3 v;

uniform sampler2D myTexture;
varying vec2 vTextCoord;

void main() {

	vec3 lightDir = normalize(gl_LightSource[0].position.xyz - v);
	vec3 eyeVec = normalize(-v);
	vec3 R = reflect(-lightDir,N);

	vec4 colorTexture = texture2D(myTexture, vTextCoord); 

	if (colorTexture.rgb == vec3(1.0,0.0,0.0))
		discard;

	vec4 AmbientTexture = colorTexture * gl_LightSource[0].ambient;
	vec4 DiffuseTexture = clamp(colorTexture * gl_LightSource[0].diffuse * max(dot(N,lightDir),0.0), 0.0, 1.0);
	vec4 SpecularTexture = colorTexture * gl_LightSource[0].specular * pow(max(dot(R,eyeVec), 0.0), gl_FrontMaterial.shininess);

	gl_FragColor = AmbientTexture + DiffuseTexture + SpecularTexture;
}