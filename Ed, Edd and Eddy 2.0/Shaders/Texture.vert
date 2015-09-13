varying vec3 N;
varying vec3 v; 
varying vec2 vTextCoord;


void main() {

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	N = normalize(gl_NormalMatrix * gl_Normal);

	v = vec3(gl_ModelViewMatrix * gl_Vertex);
	
	vTextCoord = gl_MultiTexCoord0.xy;
}