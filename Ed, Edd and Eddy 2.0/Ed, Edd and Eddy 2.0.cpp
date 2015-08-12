#include "stdafx.h"

#pragma region Zmienne globalne

	CScene * Scene;

#pragma endregion

int main(int argc, char * argv[])
{
	// Inicjalizacja biblioteki GLUT. Nalezy przekazac parametry
	// wywolania programu.
	glutInit(&argc, argv);

	// Ustawienie parametrow okna i kontekstu OpenGL.
	glutInitWindowPosition(100, 400);
	glutInitWindowPosition(640, 360);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // bufor klatki w formacie RGBA, double-buffered, z buforem glebokosci
															  														
	glutCreateWindow("Ed, Edd & Eddy 2.0"); // Utworzenie wlasciwego okna i nadanie mu tytulu.

	// Ustawienie funkcji Render() jako tej, ktora jest wykonywana
	// kazdorazowo gdy potrzeba przerysowac zawartosc okna.
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);

	// Wlaczenie testu glebokosci.
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);

	//float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	Scene = new CScene();
	Scene->Initialize();

	// Rozpoczecie wykonywania petli glownej. Od tego momentu
	// wplyw na przebieg dzialania programu maja wylacznie zarejestrowane
	// uprzednio callbacki.
	glutMainLoop();

	return 0;
}

void OnRender() {
	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

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
