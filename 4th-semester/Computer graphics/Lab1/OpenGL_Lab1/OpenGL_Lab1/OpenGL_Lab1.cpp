#include <GL/glut.h>
#include <math.h>

void init();
void draw();

void main(int argc, char** argv) //Главная функция
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1080, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MyGlutLab1Prog1");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() //Функция инициализации
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
}
void draw() //Функция рисования
{
	//Экран
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glViewport(0, 0, 720, 720);

	//Построение клеточек
	glColor3f(0.0, 0.0, 0.5);
	glLineWidth(1.0);
	GLdouble grid_size{ -5.0 };
	glBegin(GL_LINES);
	do
	{
		glVertex2f(grid_size, -5.0); glVertex2f(grid_size, 5.0);
		glVertex2f(-5.0, grid_size); glVertex2f(5.0, grid_size);
		grid_size += 0.5;
	} while (grid_size <= 5.0);
	glEnd();
	
	//Построение координатных осей
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, -5.0); glVertex2f(0.0, 5.0);
	glVertex2f(-5.0, 0.0); glVertex2f(5.0, 0.0);
	glEnd();

	//Построение графика функции
	const GLint w{ 4 };
	GLdouble x{ -5.0 };
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	do
	{
		glVertex2f(x, sin(w * x) / (w * x));
		x += 0.01;
	} while (x <= 5.0);
	glEnd();

	glFlush();
}