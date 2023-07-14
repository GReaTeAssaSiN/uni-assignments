#include <gl\glut.h>
#include <iostream>
//Переменные для вращения объекта/камеры на определенное число градусов.
GLfloat angle_object{}, angle_light{};
//Переменные для начала вращения объекта/камеры.
GLboolean object_rotate{ false }, light_rotate{ false };

void init(void)
{
	glClearColor(0.5, 0.5, 0.71, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Функция для "отлова" событий клавиатуры (клавиатурных событий).
void KeyboardEvents(unsigned char key, int x, int y)
{
	if (key == static_cast<unsigned char>('o'))
	{
		object_rotate = true;
		light_rotate = false;
	}
	else if (key == static_cast<unsigned char>('l'))
	{
		light_rotate = true;
		object_rotate = false;
	}
	else if (key == static_cast<unsigned char>('f'))
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else if (key == static_cast<unsigned char>('b'))
	{
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
}
void myDisplay()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//Включаем тестовую глубину для реализации изображения.
	//Задание положения камеры.
	gluLookAt(0, 3, 3, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	//Задание освещения.
	glRotatef(angle_light, 0.0, 1.0, 0.0);
	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	//Включаем источник света.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle_object, 0.0, 1.0, 0.0);
	//Рисование тетраэдра.
	//грань f0
	glBegin(GL_POLYGON);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	//грань f1
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	//грань f2
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);
	glEnd();
	//грань f3
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_LIGHTING);//Выключаем освещение для рисования линий и прочего в цвете.
	//Рисование координатных осей.
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();
	//Рисование источника освещения 
	//Расположение источника света для наглядности.
	glRotatef(angle_light, 0.0, 1.0, 0.0);
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 2.0, 2.0);
	glEnd();
	//Рисование направление к источнику света.
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(0.0, 0.0, 0.0); glVertex3f(1.0, 2.0, 2.0);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}
void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}
void myIdle()
{
	if (light_rotate)
	{
		angle_light += 0.005;
		if (angle_light >= 360) angle_light = 0;
	}
	else if (object_rotate)
	{
		angle_object += 0.01;
		if (angle_object >= 360) angle_object = 0;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGl_Lab4_Prog1");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(KeyboardEvents);
	init();
	glutMainLoop();
}