#include "stdafx.h"

#pragma region Zmienne globalne

	CScene * Scene;
	
	bool keystate[256];
	bool keystate_special[256];

#pragma endregion

int main(int argc, char * argv[])
{
	// Inicjalizacja biblioteki GLUT. Nalezy przekazac parametry
	// wywolania programu.
	glutInit(&argc, argv);

	// Ustawienie parametrow okna i kontekstu OpenGL.
	//glutInitWindowPosition(100, 400);
	glutInitWindowPosition(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // bufor klatki w formacie RGBA, double-buffered, z buforem glebokosci
															  														
	glutCreateWindow("Ed, Edd & Eddy 2.0"); // Utworzenie wlasciwego okna i nadanie mu tytulu.

	// Ustawienie funkcji Render() jako tej, ktora jest wykonywana
	// kazdorazowo gdy potrzeba przerysowac zawartosc okna.
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyPress);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	
	// Inicjalizacja GLEW sluzacego do wygodnego korzystania z funkcji rozszerzen OpenGL
	glewInit();
	
	Scene = new CScene();
	Scene->Initialize();

	// Rozpoczecie wykonywania petli glownej. Od tego momentu
	// wplyw na przebieg dzialania programu maja wylacznie zarejestrowane
	// uprzednio callbacki.
	glutMainLoop();

	return 0;
}

void OnRender() {

	Scene->Render();

	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();

	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();

	// Nakaz wyswietlic kolejna klatke.
	glutPostRedisplay();
}

void OnReshape(int width, int height) {
	// Wybor macierzy - macierz Projekcji.
	glMatrixMode(GL_PROJECTION);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Okreslenie obszaru renderowania - caly obszar okna.
	glViewport(0, 0, width, height);

	// Chcemy uzyc kamery perspektywicznej o kacie widzenia 60 stopni
	// i zasiegu renderowania 0.01-100.0 jednostek.
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {		
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnSpecialKeyPress(int key, int x, int y) {
	if (!keystate_special[key]) {
		OnSpecialKeyDown(key, x, y);		
	}
	keystate_special[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	if (key == ' ') {
		Scene->useShaders = !Scene->useShaders;
	}
}

void OnSpecialKeyDown(int key, int x, int y) {
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnSpecialKeyUp(int key, int x, int y) {
	keystate_special[key] = false;
}

void OnTimer(int id) {
	glutTimerFunc(17, OnTimer, 0);

	Scene->Update();
}