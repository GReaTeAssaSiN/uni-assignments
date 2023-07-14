#include <gl\glut.h>
#include <stdio.h>
#include <iostream>

#include <C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\include\\GL\\glaux.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\lib\\x64\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

/*Структура для хранения заголовка файла изображения*/
struct Zagolovok
{
	GLint shirina{}; /*Ширина*/
	GLint vysota{}; /*Высота*/
	GLenum formatCveta{}; /*Формат представления цвета*/
	GLenum formatKomponenty{}; /*Формат данных компоненты цвета*/
	int kol_voKomponent{}; /*Количество компонент цвета*/
};
/*Структура для хранения изображения*/
struct Izobrajenie
{
	unsigned char* pikseli{};
	Zagolovok zagolovok{};
};
Izobrajenie* izobr{};//Текущее изображение.
Izobrajenie* izobr_bmp{};//Изображение из файла .bmp.
Izobrajenie* izobr_gb{};//Изображение с зеленым и синим компонентами.
AUX_RGBImageRec* pImage = NULL; //Изображение AUX_RGB.
bool mirror_image_X{};//Переменная для учета отзеркаленности изображения от-но оси X.
static GLint rejim{-1};//Переменная для хранения режима рисования.
//Должным образом обновляем флаги в ответ на выбор позиции из меню.
void ObrabotkaMenu(int punktMenu)
{
	//Меняем индекс режима визуализации на индекс, соответствующий позиции меню
	rejim = punktMenu;
	//Активизируем перерисовывание изображения glutPostRedisplay().
	glutPostRedisplay();
}
void Pererisovka(void)
{
	GLint iViewport[4]{};
	//GLbyte *pModifiedBytes = NULL.
	GLfloat invertMap[256]{};//Инверсная карта цветов.
	GLfloat defaultMap[256]{};//Стандартная карта цветов.
	GLint i{};
	//Очищаем окно текущим цветом очистки.
	glClear(GL_COLOR_BUFFER_BIT);
	//Текущее растровое положение всегда соответствует левому нижнему углу окна.
	glRasterPos2i(0, 0);
	//В зависимости от индекса режима визуализации выполняются необходимые операции с изображением.
	switch (rejim)
	{
	case 0: /*Загрузка изображения из файла *.bmp*/
		if (!izobr)
		{
			pImage = auxDIBImageLoad(L"space.bmp");
			izobr_bmp = (Izobrajenie*)malloc(sizeof(Izobrajenie));
			if (izobr_bmp)
			{
				izobr_bmp->zagolovok.shirina = pImage->sizeX*3/2;
				izobr_bmp->zagolovok.vysota = pImage->sizeY;
				izobr_bmp->pikseli = pImage->data;
				izobr_bmp->zagolovok.formatCveta = GL_LUMINANCE;
				izobr_bmp->zagolovok.formatKomponenty = GL_SHORT;
				izobr_bmp->zagolovok.kol_voKomponent = 1;
				izobr = izobr_bmp;
			}
			else
			{
				std::cout << "Не удалось выделить динамическую память из кучи! Куча переполнена." << std::endl;
				free(izobr);
				free(izobr_bmp);
				free(pImage);
				exit(-1);
			}
		}
		break;
	case 1: /*Очистка экрана*/
		// Сброс преобразованного изображения до первоначального с освобождением соответствующей динамической памяти
		if (izobr)
		{
			defaultMap[0] = 0.0f;
			for (i = 1; i < 256; i++)
				defaultMap[i] = 1.0f / 255.0f * (GLfloat)i;
			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, defaultMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
			glPixelZoom(1, 1);
			free(izobr);
			free(pImage);
			izobr = nullptr;
			mirror_image_X = false;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 2: /*Отражение изображения относительно оси X*/
		if (izobr != nullptr)
			mirror_image_X = true;
		break;
	case 3:/*Отображение только компонент G и B*/
		if (izobr)
		{
			if (mirror_image_X)
				glPixelZoom(1, 1);
			//Вначале рисуем изображение в буфере цвета.
			glDrawPixels(izobr->zagolovok.shirina, izobr->zagolovok.vysota, izobr->zagolovok.formatCveta, izobr->zagolovok.formatKomponenty, izobr->pikseli);
			//Распределяем память для карты яркости.
			izobr_gb = (Izobrajenie*)malloc(sizeof(Izobrajenie));
			if (izobr_gb != nullptr)
			{
				izobr_gb->zagolovok.shirina = izobr->zagolovok.shirina;
				izobr_gb->zagolovok.vysota = izobr->zagolovok.vysota;
				izobr_gb->zagolovok.formatCveta = GL_LUMINANCE;
				izobr_gb->zagolovok.formatKomponenty = GL_SHORT;
				izobr_gb->zagolovok.kol_voKomponent = 1;
				izobr_gb->pikseli = (unsigned char*)malloc(izobr_gb->zagolovok.shirina * izobr_gb->zagolovok.vysota * izobr_gb->zagolovok.kol_voKomponent * 2);
				//Масштабируем цвета согласно заданному условию.
				glPixelTransferf(GL_RED_SCALE, 0.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
				//Считываем пиксели в буфер.
				glReadPixels(0, 400, izobr_gb->zagolovok.shirina, izobr_gb->zagolovok.vysota, izobr_gb->zagolovok.formatCveta, izobr_gb->zagolovok.formatKomponenty, izobr_gb->pikseli);
				if (mirror_image_X)
					glClear(GL_COLOR_BUFFER_BIT);
				izobr = izobr_gb;
				//Масштабирование цвета возвращается в норму.
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
			}
			else
			{
				std::cout << "Не удалось выделить динамическую память из кучи! Куча переполнена." << std::endl;
				free(izobr);
				free(izobr_gb);
				free(pImage);
				exit(-1);
			}
		}
		break;
	case 4: /*Инверсия компонент G и B*/
		if (izobr)
		{
			defaultMap[0] = 0.0f;
			invertMap[0] = 1.0f;
			for (i = 1; i < 256; i++)
			{
				defaultMap[i] = 1.0f / 255.0f * (GLfloat)i;
				invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
			}
			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
			glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
		}
		break;
	case 5:/*Выход*/
		std::cout << "Завершение программы . . ." << std::endl;
		if (izobr != nullptr)
		{
			free(izobr);
			free(pImage);
		}	
exit(0);
		break;
	default:
		break;
	}
	if (rejim != 1 && izobr != nullptr)
	//Рисуются пиксели
	{
		if (mirror_image_X)
			glPixelZoom(1, -1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glDrawPixels(izobr->zagolovok.shirina, izobr->zagolovok.vysota, izobr->zagolovok.formatCveta, izobr->zagolovok.formatKomponenty, izobr->pikseli);
	}
	//Переключает буферы
	glutSwapBuffers();
}
void IzmenenieRazmera(int w, int h)
{
	//Предотвращает деление на ноль, когда окно слишком маленькое
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	//Система координат обновляется перед модификацией
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
//Точка входа основной программы
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("OpenGL_Lab6");
	glutReshapeFunc(IzmenenieRazmera);
	glutDisplayFunc(Pererisovka);
	//Создается меню и добавляются опции выбора
	GLint submenu = glutCreateMenu(ObrabotkaMenu);
	glutAddMenuEntry("Чтение изображения", 0);
	glutAddMenuEntry("Очистить экран", 1);
	glutCreateMenu(ObrabotkaMenu);
	glutAddSubMenu("Загрузить изображение .bmp", submenu);
	glutAddMenuEntry("Отобразить изображение относительно оси X", 2);
	glutAddMenuEntry("Отображение только компонент G и B", 3);
	glutAddMenuEntry("Инверсия компонент G и B", 4);
	glutAddMenuEntry("Выход", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluOrtho2D(0, 512, -512, 512);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	rejim = 1;
	glutMainLoop();
	// Освобождаем исходные данные изображений
	free(izobr);
	free(izobr_bmp);
	free(izobr_gb);
	free(pImage);
	return 0;
}
