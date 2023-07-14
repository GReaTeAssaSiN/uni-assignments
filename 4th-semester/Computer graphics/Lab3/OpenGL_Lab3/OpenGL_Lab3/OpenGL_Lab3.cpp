#include <gl\glut.h>
#include <math.h>
#include <iostream>
#include <windows.h>
//Переменные для вращения наблюдателя.
GLfloat angle_rotate{};
GLboolean no_rotate{ true }, clockwise{ false };
//Переменные для масштабирования объекта.
GLfloat scale_last{ 1.0 }, scale_next{ 1.0 };
GLboolean flag_scale_up{ false }, flag_scale_down{ false };
	
void init(void)
{
	glClearColor(0.5, 0.5, 0.71, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 15);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Функция для "отлова" событий мыши ("мышиных" событий).
void MouseClickEvents(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && (scale_next + 0.1) <= 1.6)
	{
		flag_scale_up = true;
		flag_scale_down = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP && (scale_next - 0.1) >= 0.4)
	{
		flag_scale_down = true;
		flag_scale_up = false;
	}
}
//Функция для "отлова" событий клавиатуры (клавиатурных событий).
void KeyBoardEvents(unsigned char key, int x, int y)
{
	if (key == static_cast<unsigned char>('X'))
	{
		no_rotate = false;
		clockwise = true;
	}
	else if (key == static_cast<unsigned char>('Y'))
	{
		no_rotate = false;
		clockwise = false;
	}
}
void myDisplay()
{
	glPushMatrix(); //Сохраняем VM = 1.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//Включаем тестовую глубину для реализации изображения.
	// Задаем VM = Fwe * (матрицу для движения по окружности наблюдателя).
	gluLookAt(5*sin(angle_rotate), 2, 6*cos(angle_rotate), 0, 0, 0, 0, 1, 0);

	GLfloat myLightPosition[] = { 3.0, 0.0, 4.0, 1.0};// Источник света в CKw.
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*Позиция источника света будет преобразована в CKe.*/
	//Включаем источник света.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glPushMatrix(); //Сохраняем VM=Fwe или преобразованную в результате движения по окружности наблюдателя.
	glScalef(scale_next, scale_next, 1.0);//Сохранение масштабности сохранённой и не изменённой VM = Fwe.
	//Масштабирование по Х и У VM=Fwe по нажатию кнопок мыши.
	if (flag_scale_up)
	{
		scale_last = scale_next;
		scale_next += 0.1;
		glScalef(scale_next / scale_last, scale_next / scale_last, 1.0);
		flag_scale_up = false;
	}
	else if (flag_scale_down)
	{
		scale_last = scale_next;
		scale_next -= 0.1;
		glScalef(scale_next / scale_last, scale_next / scale_last, 1.0);
		flag_scale_down = false;
	}
	glutSolidOctahedron();//Создание октаэдра.
	glPopMatrix(); // Восстанавливаем VM=Fwe или преобразованную в результате движения по окружности наблюдателя.

	glDisable(GL_LIGHTING); //Выключаем освещение для рисования линий и прочего в цвете.
	//Рисуем координатные оси разного цвета в CKe.
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
	glEnd();
	//Расположение источника света для наглядности в СКе.
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(3.0, 0.0, 4.0);
	glEnd();
	//Рисуем направление к источнику света в CKe.
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0); glVertex3f(3.0, 0.0, 4.0); glVertex3f(0.0, 0.0, 0.0);
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
	if (!no_rotate)
	{
		if (clockwise)
			angle_rotate -= 0.0025;
		else
			angle_rotate += 0.0025;
		Sleep(15);
	}
	if (angle_rotate >= 360 || angle_rotate <= -360) angle_rotate = 0;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGl_Lab3");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(KeyBoardEvents);
	glutMouseFunc(MouseClickEvents);
	init();
	glutMainLoop();
}