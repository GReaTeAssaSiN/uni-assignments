#include <GL/glut.h>
#include <stdlib.h>
#include <Windows.h>

GLfloat R = 640.0 / 480.0; //Форматное соотношение.
GLfloat w = 40; //Ширина мирового окна.
GLfloat h; //Высота мирового окна.
GLfloat l, r, b, t; //Параметры мирового окна.
GLfloat f{}; //Угол поворота фиг.1.
GLfloat scale{ 3.0 / 8.0 }; //Масштабирование прямоугольника (фиг. 1) и его осей СК (СКL) для случая, когда f = 120;
bool flag{ false }; //Для учета scale в размерах осей СК (СКL) фиг. 1.

void init(void)
{
	//h = 30, l = - 30 10/13, r = 30 10/13, b = -23 1/13, t = 23 1/13.
	h = w / R; l = -w / 1.3; r = w / 1.3; b = -h / 1.3; t = h / 1.3; //Расчет параметров мирового окна.
	glClearColor(0.5, 0.5, 0.71, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H)//Сохранение масштаба во время работы программы.
{
	if (R > static_cast<float>(W) / H) glViewport(0, 0, W, W / R);//0, 0, 640, 480.
	else glViewport(0, 0, H * R, H);//0, 0, 640, 480.
}

void showAxis(void)//Прорисовка осей СК (МСК(СК0)), в частности, для треугольника (фиг.0).
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t);
	glVertex2f(0, 0);
	glVertex2f(r, 0);
	glEnd();
}

void showAxisMovingFig1(void)//Прорисовка осей СК (СКL) смещающегося прямоугольника (фиг. 1).
{
	glColor3f(1.0f, 0.7f, 0.0f);
	glBegin(GL_LINES);
	if (!flag)
	{
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glVertex2f(0, 0);
		glVertex2f(12, 0);
	}
	else
	{
		glVertex2f(0 / scale, 0 * scale);
		glVertex2f(0 / scale, 10 * scale);
		glVertex2f(0 / scale, 0 * scale);
		glVertex2f(12 / scale, 0 * scale);
	}
	glEnd();
}

void fig0(void)//Прорисовка треугольника (фиг. 0).
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(20.0, 0.0);
	glVertex2f(10.0, 10.0);
	glEnd();
}

void fig1(void)//Прорисовка смещающегося прямоугольника (фиг. 1).
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(8.0, 0.0);
	glVertex2f(8.0, 3.0);
	glVertex2f(0.0, 3.0);
	glEnd();
}

void scene(void)//Сцена, прорисовка фигур с соответствующим смещением и преобразованием СК МСК(СК0) -> СКL.
{
	glClear(GL_COLOR_BUFFER_BIT);
	showAxis();
	fig0();
	glPushMatrix();
	if (f == 0) glTranslatef(20.0, 0.0, 0.0);
	else if (f == 120) glTranslatef(10.0, 10.0, 0.0);
	glRotatef(f, 0.0, 0.0, 1.0);
	if (f == 120) 
	{ 
		glScalef(scale, 1.0 / scale, 1.0); 
		flag = true; 
	}
	else 
	{ 
		glScalef(1.0, 1.0, 1.0);
		flag = false; 
	}
	showAxisMovingFig1();
	fig1();
	glPopMatrix( );
	glFlush();
	glutSwapBuffers();
	f += 120;
	if (f == 360)
		f = 0;
	Sleep(400);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Lab2_Prog2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}