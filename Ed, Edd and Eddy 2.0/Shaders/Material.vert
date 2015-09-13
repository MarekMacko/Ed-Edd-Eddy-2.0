// "varying" to zmienna, ktora zostanie przekazana do nastepnego etapu (Fragment Shadera).
// Tu wyliczamy jej wartosci dla wierzcholkow, natomiast Fragment Shader
// otrzyma wartosci interpolowane pomiedzy wierzcholkami.
varying vec3 N;
varying vec3 v; 

void main() {

	// Wyliczenie polozenia wierzcholka uwzgledniajacego macierz modelu-widoku-projekcji
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Wyliczenie wektora normalnego w przestrzeni kamery (gl_NormalMatrix to wycinek 3x3 macierzy modelu-widoku)
	N = normalize(gl_NormalMatrix * gl_Normal);

	v = vec3(gl_ModelViewMatrix * gl_Vertex);
}