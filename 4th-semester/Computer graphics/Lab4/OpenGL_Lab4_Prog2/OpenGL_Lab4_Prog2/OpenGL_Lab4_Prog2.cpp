#include <gl\glut.h>
#include <iostream>
//Переменные для вращения объекта/камеры на определенное число градусов.
GLfloat angle_object{}, angle_light{};
//Переменные для начала вращения объекта/камеры.
GLboolean object_rotate{ false }, light_rotate{ false };

void init(void)
{
	glClearColor(0.04, 0.215, 0.11, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 50);
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
	//Задаем положение камеры.
	gluLookAt(10, 12, 20, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	//Задание освещения.
	glRotatef(angle_light, 0.0, 1.0, 0.0);
	GLfloat myLightPosition[] = { 10.0, 2.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	//Включаем источник света.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	glPushMatrix();
	//Задание материала объекта.
	GLfloat myAmbient[] = { 0.19125, 0.0735, 0.0225, 1 };
	GLfloat myDiffuse[] = { 0.7038, 0.27048, 0.0828, 1 };
	GLfloat mySpecular[] = { 0.256777, 0.137622, 0.086014, 1 };
	GLfloat myShininess[] = { 12.8 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	glRotatef(angle_object, 0.0, 1.0, 0.0);
	//Рисование усеченной пирамиды.
	//грань f0
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(8, 0, -4);
	glVertex3f(6, 0, 2);
	glEnd();
	//грань f1
	glBegin(GL_POLYGON);
	glNormal3f(-12, 9, 8);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 4, 0);
	glVertex3f(5, 4, -3);
	glVertex3f(8, 0, -4);
	glEnd();
	//грань f2
	glBegin(GL_POLYGON);
	glNormal3f(4, 3, -8);
	glVertex3f(8, 0, -4);
	glVertex3f(5, 4, -3);
	glVertex3f(5, 4, 1);
	glVertex3f(6, 0, 2);
	glEnd();
	//грань f3
	glBegin(GL_POLYGON);
	glNormal3f(3, 1, 1);
	glVertex3f(6, 0, 2);
	glVertex3f(5, 4, 1);
	glVertex3f(3, 4, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	//грань f4
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 4);
	glVertex3f(3, 4, 0);
	glVertex3f(5, 4, 1);
	glVertex3f(5, 4, -3);
	glEnd();
	glEnable(GL_NORMALIZE);
	glPopMatrix();

	glDisable(GL_LIGHTING);//Выключаем освещение для рисования линий и прочего в цвете.
	//Рисование координатных осей.
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
	glEnd();
	//Рисование источника освещения 
	//Расположение источника света для наглядности.
	glRotatef(angle_light, 0.0, 1.0, 0.0);
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(10.0, 2.0, 5.0);
	glEnd();
	//Рисование направление к источнику света.
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(0.0, 0.0, 0.0); glVertex3f(10.0, 2.0, 5.0);
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
		angle_light += 0.05;
		if (angle_light >= 360) angle_light = 0;
	}
	else if (object_rotate)
	{
		angle_object += 0.03;
		if (angle_object >= 360) angle_object = 0;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGl_Lab4_Prog2");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(KeyboardEvents);
	init();
	glutMainLoop();
}