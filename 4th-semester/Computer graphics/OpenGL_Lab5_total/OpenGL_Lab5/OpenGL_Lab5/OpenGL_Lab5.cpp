#include <iostream>
#include <gl\glut.h>
#include <atlbase.h>
#include <atlconv.h>
#include <string>
#include <cmath>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#include <C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\include\\GL\\glaux.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\lib\\x64\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

//Переменные для вращения объекта/камеры на определенное число градусов.
GLfloat angle_object{}, angle_light{};
//Переменные для начала вращения объекта/камеры.
GLboolean object_rotate{ false }, light_rotate{ false };

GLuint list{};
void figure()
{
	AUX_RGBImageRec* image_1{ auxDIBImageLoad(L"texture_1.bmp") };
	AUX_RGBImageRec* image_2{ auxDIBImageLoad(L"texture_2.bmp") };
	AUX_RGBImageRec* image_3{ auxDIBImageLoad(L"texture_3.bmp") };

	GLuint textures[3]{};
	GLuint texture_1{};
	GLuint texture_2{ 1 };
	GLuint texture_3{ 2 };

	glGenTextures(3, textures);

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_1->sizeX, image_1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1->data);

	glBindTexture(GL_TEXTURE_2D, texture_2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_2->sizeX, image_2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_2->data);

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_3->sizeX, image_3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_3->data);

	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	GLfloat MyAmbient[] = { 0.19125, 0.0735, 0.0225, 1 };
	GLfloat MyDiffuse[] = { 0.7038, 0.27048, 0.0828, 1 };
	GLfloat MySpecular[] = { 0.256777, 0.137622, 0.086014, 1 };
	GLfloat MyShininess[] = { 12.8 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MyAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MySpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MySpecular);

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(4.73, 0, -4.2);
	glTexCoord2f(1, 1); glVertex3f(6, 0, 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glBegin(GL_POLYGON);
	glNormal3f(-0.624722, 0.335006, -0.705332);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(1.99, 2.87, -0.41);
	glTexCoord2f(1, 1); glVertex3f(4.09, 2.87, -2.27);
	glTexCoord2f(1, 0); glVertex3f(4.73, 0, -4.2);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_POLYGON);
	glNormal3f(0.924097, 0.332616, -0.18818);
	glTexCoord2f(0, 0); glVertex3f(4.73, 0, -4.2);
	glTexCoord2f(0, 1); glVertex3f(4.09, 2.87, -2.27);
	glTexCoord2f(1, 1); glVertex3f(4.65, 2.87, 0.48);
	glTexCoord2f(1, 0); glVertex3f(6, 0, 2);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glBegin(GL_POLYGON);
	glNormal3f(0.299203, 0.332868, 0.894246);
	glTexCoord2f(1, 1); glVertex3f(6, 0, 2);
	glTexCoord2f(1, 0); glVertex3f(4.65, 2.87, 0.48);
	glTexCoord2f(0, 0); glVertex3f(1.99, 2.87, -0.41);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(1.99, 2.87, -0.41);
	glTexCoord2f(0, 1); glVertex3f(4.65, 2.87, 0.48);
	glTexCoord2f(1, 1); glVertex3f(4.09, 2.87, -2.27);
	glEnd();

	glEnable(GL_NORMALIZE);
	
	glEndList();
}
void init(void)
{
	glClearColor(0.016, 0.282, 0.259, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	figure();
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
void MouseEvents(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}
void myDisplay()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//Включаем тестовую глубину для реализации изображения.
	//Задаем положение камеры.
	gluLookAt(10, 12, 15, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	//Задание освещения.
	glRotatef(angle_light, 0.0, 1.0, 0.0);
	GLfloat myLightPosition[] = { 8.0, 4.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	//Включаем источник света.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);//Включаем наложение двумерных текстур.
	glRotatef(angle_object, 0.0, 1.0, 0.0);
	glCallList(list);
	glPopMatrix();

	glDisable(GL_LIGHTING);//Выключаем освещение для рисования линий и прочего в цвете.
	glDisable(GL_TEXTURE_2D);//Выключаем наложение двумерных текстур.
	//Рисование координатных осей.
	glLineWidth(2);
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
	glVertex3f(8.0, 4.0, 5.0);
	glEnd();
	//Рисование направления к источнику света.
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(0.0, 0.0, 0.0); glVertex3f(8.0, 4.0, 5.0);
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
		angle_light += 0.03;
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
	glutCreateWindow("OpenGl_Lab5");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(KeyboardEvents);
	glutMouseFunc(MouseEvents);
	init();
	glutMainLoop();
	return 0;
}