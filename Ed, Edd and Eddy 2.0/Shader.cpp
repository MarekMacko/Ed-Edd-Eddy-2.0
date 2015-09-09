#include "stdafx.h"

CShader::CShader()
{
}

CShader::~CShader()
{
	if (shadingProgramId) {
		glDeleteProgram(shadingProgramId);
	}
}

// Funkcja, ktora ma za zadanie utworzyc shader danego typu (GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
// na podstawie kodu zrodlowego odczytanego z pliku o zadanej sciezce. Zwraca id shadera,
// ktore pozniej jest uzywane w celu podlaczenia shadera do programu cieniujacego.
GLuint CShader::CreateShader(GLenum type, char path[]) {

	// Odczytanie kodu �r�owego z pliku
	ifstream shaderFile;
	string * shaderCodeStr;
	shaderFile.open(path, ifstream::in);
	if (!shaderFile) {
		cerr << "Error while reading shader file (" << path << ").\n";
		return -1;
	}
	shaderCodeStr = new string(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());
	shaderFile.close();
	*shaderCodeStr += "\0";
	const char * shaderCode = shaderCodeStr->c_str();

	// Utworzenie shadera, przekazanie sterownikowi kodu �r�d�owego oraz jego kompilacja
	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);

	// Kod shadera ju� nie jest nam potrzebny w pami�ci
	delete shaderCode;

	// Sprawdzenie czy wyst�pi�y b��dy kompilacji i ich wypisanie
	int status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		cerr << "Error while compiling shader code (" << path << ").\n";
			GLchar * buf = new GLchar[512];
			glGetShaderInfoLog(shaderId, 512, NULL, buf);
			cerr << buf << "\n";
			delete[] buf;
			glDeleteShader(shaderId);
			return -1;
	}

	// Zwr�cenie id shadera
	return shaderId;
}

// Utworzenie programu cieniujacego skladajacego sie z Vertex i Fragment shaderow o zrodlach
// odczytanych z zadanych plikow. Zwraca id programu cieniujacego, ktore pozniej jest uzywane
// do jego wlaczenia.
void CShader::CreateShadingProgram(char vsPath[], char fsPath[]) {

	// Stworzenie shader�w na podstawie �r�de� z zadanych plik�w
	GLuint vs = CreateShader(GL_VERTEX_SHADER, vsPath);
	GLuint fs = CreateShader(GL_FRAGMENT_SHADER, fsPath);
	
	// Utworzenie nowego programu cieniuj�cego, OpenGL zwr�ci jego identyfikator
	shadingProgramId = glCreateProgram();

	// Pod��czenie Vertex i Fragment shader�w do naszego nowegu programu, korzystaj�� z id shader�w 
	glAttachShader(shadingProgramId, vs);
	glAttachShader(shadingProgramId, fs);

	// Linkowanie programu po pod��czeniu shader�w
	glLinkProgram(shadingProgramId);

	// Sprawdzenie czy wyst�pi�y b��dy linkowania i ich wypisanie
	int status;
	glGetProgramiv(shadingProgramId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		cerr << "Error while linking shader program (" << shadingProgramId << ").\n";
		GLchar * buf = new GLchar[512];
		glGetShaderInfoLog(shadingProgramId, 512, NULL, buf);
		cerr << buf << "\n";
		delete[] buf;
		return;
	}

}

GLuint CShader::GetShadingProgram(void) {
	return shadingProgramId;
}


