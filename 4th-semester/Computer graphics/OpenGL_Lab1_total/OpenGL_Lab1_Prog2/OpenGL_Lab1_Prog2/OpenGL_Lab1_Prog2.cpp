#include <GL/glut.h>
#include <math.h>
#include <cstdlib>//Для rand() и srand()
#include <ctime>//Для time()

void init();
void draw();
float getRandomNumber(float min, float max);

void main(int argc, char** argv) //Главная функция
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1080, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MyGlutLab1Prog2");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() //Функция инициализации
{
	glClearColor(0.5, 0.5, 0.71, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0 , -1.0, 1.0);
}
void draw() //Функция рисования
{
	//Привязка rand() к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	//Экран
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.71, 0.0);

	//Создание портов просмотра, организующие мозаику
	GLint x{}, y{}, w{ 120 }, h{ 120 };

	for (x = 0; x <= 720; x += w)
		for (y = 0; y <= 720; y += h)
		{
			glViewport(x, y, w, h);

			glBegin(GL_TRIANGLE_FAN);
			for (GLdouble point_x{-1}; point_x <= 1; point_x += 0.5)
			{
				glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				glVertex2f(point_x, sqrt(1.0 - pow(point_x, 2))), glVertex2f(point_x, -sqrt(1.0 - pow(point_x, 2)));
			}
			glEnd();
		}
	glFlush();
}

float getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}