// "varying" to zmienna przekazana z poprzedniego etapu, czyli Vertex Shadera.
// Jej wartosc jest interpolowana pomiedzy wierzcholkami.
varying vec3 N;

void main() {

	vec4 color = vec4(0.0);

	// Komponent Ambient
	color += gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	
	// Ustawienie wynikowego koloru fragmentu
	gl_FragColor = color;

}