// "varying" to zmienna przekazana z poprzedniego etapu, czyli Vertex Shadera.
// Jej wartosc jest interpolowana pomiedzy wierzcholkami.
varying vec3 N;
varying vec3 v;

uniform sampler2D myTexture;
varying vec2 vTexCoord;

void main() {

	vec3 lightDir = normalize(gl_LightSource[0].position.xyz - v);
	vec3 eyeVec = normalize(-v);
	vec3 R = reflect(-lightDir,N);

	// Komponent Ambient
	vec4 componentAmbient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	
	// Komponent Diffuse	
	vec4 componentDiffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * max(dot(N,lightDir),0.0);
	componentDiffuse = clamp(componentDiffuse, 0.0, 1.0);

	//Komponent Specular
	vec4 componentSpecular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(dot(R,eyeVec), 0.0), gl_FrontMaterial.shininess);
	
	// Ustawienie wynikowego koloru fragmentu
	gl_FragColor = componentAmbient + componentDiffuse + componentSpecular;
}

