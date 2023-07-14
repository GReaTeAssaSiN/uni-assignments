#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h> //Для sleep()

GLfloat R{ 640.0 / 480.0 }; //Форматное соотношение.
GLfloat w{40}; //Ширина мирового окна.
GLfloat h{}; //Высота мирового окна.
GLfloat l{}, r{}, b{}, t{}; //Параметры мирового окна.
GLfloat pulsing{1.0}; //Переменная для пульсации (масштабирование).
bool flag{ false }; //Переменная для пульсирования в ту или иную сторону.
bool rectDivision{ false }; //Переменная для разделения прямоугольников первоначального и масштабированного (отображаемого) (рисуются одной и той же процедурой).

void init(void)
{
	//h = 30, l = - 20, r = 20, b = 15, t = 15.
	h = w / R; l = -w / 2; r = w / 2; b = -h / 2; t = h / 2; //Расчет параметров мирового окна.
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

void showAxis(void)//Прорисовка осей МСК (СК0) первоначального прямоугольника.
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t);
	glVertex2f(0, 0);
	glVertex2f(r, 0);
	glEnd();
}

void showAxisFig0Scaled(void) //Прорисовка осей СК (СКL) прямоугольника, отображенного относительно произвольно заданной прямой.
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t / pulsing);
	glVertex2f(0, 0);
	glVertex2f(r / pulsing, 0);
	glEnd();
}

void fig0(void)//Прорисовка прямоугольников.
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	if (!rectDivision)//Прорисовка первоначального прямоугольника.
	{
		glVertex2f(2.0, 3.0);
		glVertex2f(2.0, 9.0);
		glVertex2f(6.0, 9.0);
		glVertex2f(6.0, 3.0);
	}
	else//Прорисовка масштабируемого (пульсирующего, отображаемого) прямоугольника в зависимости от масштаба с соответствующими координатами.
	{
		if (pulsing <= 1.0)
		{
			glVertex2f(2.0 / pulsing, 3.0 / pulsing);
			glVertex2f(2.0 / pulsing, 9.0 / pulsing);
			glVertex2f(6.0 / pulsing, 9.0 / pulsing);
			glVertex2f(6.0 / pulsing, 3.0 / pulsing);
		}
		else if ((pulsing >= 1.2) && (pulsing <= 1.4))
		{
			glVertex2f(1.6 / pulsing, 2.4 / pulsing);
			glVertex2f(1.6 / pulsing, 9.6 / pulsing);
			glVertex2f(6.4 / pulsing, 9.6 / pulsing);
			glVertex2f(6.4 / pulsing, 2.4 / pulsing);
		}
		else
		{
			glVertex2f(1.2 / pulsing, 1.8 / pulsing);
			glVertex2f(1.2 / pulsing, 10.2 / pulsing);
			glVertex2f(6.8 / pulsing, 10.2 / pulsing);
			glVertex2f(6.8 / pulsing, 1.8 / pulsing);
		}
	}
	glEnd();
}

void line(void)//Прорисовка линии, относительно которой отображается первоначальный прямоугольник.
{
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2f(-14, 14);
	glVertex2f(14, -14);
	glEnd();
}

void scene(void)//Сцена, прорисовка фигур с соответственными преобразованиями СК (МСК(СК0) -> СКL).
{
	glClear(GL_COLOR_BUFFER_BIT);
	showAxis();
	rectDivision = false;
	fig0();
	line();
	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	glScalef(pulsing, pulsing, 0.0);
	showAxisFig0Scaled();
	rectDivision = true;
	fig0();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	if (!flag)
	{
		pulsing += 0.2;
		if (pulsing >= 1.4)
			flag = true;
	}
	else
	{
		pulsing -= 0.2;
		if (pulsing <= 1.0)
			flag = false;
	}
	Sleep(300);
}

void main(int argc, char** argv)//Главная функция.
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Lab2_Prog1");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}
