#define GL_SILENCE_DEPRECATION
#if __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "NeighborSearch.h"
#include "Computations.h"

void Keyboard(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
	if (key == 27)
		exit(0);
}

void Update(void)
{
	//NeighborSearch();
	ComputeDensityPressure();
	ComputeForces();
	Integrate();

	glutPostRedisplay();
}

void InitGL(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(SPACING / 2.f);
	glMatrixMode(GL_PROJECTION);
}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, VIEW_WIDTH, 0, VIEW_HEIGHT, 0, 1);

	glColor4f(0.2f, 0.6f, 1.f, 1);
	glBegin(GL_POINTS);
	for (auto& p : particles)
	{
		glVertex2f(p.x(0), p.x(1));

	}
	glEnd();

	glColor4f(0.8f, 0.6f, .3f, 1);
	glBegin(GL_POINTS);
	for (auto& b : boundaries)
	{
		glVertex2f(b.x(0), b.x(1));
	}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInit(&argc, argv);
	glutCreateWindow("2D SPH solver");
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutKeyboardFunc(Keyboard);

	InitGL();
	InitSPH();
	InitBoundaries();

	glutMainLoop();
	return 0;
}