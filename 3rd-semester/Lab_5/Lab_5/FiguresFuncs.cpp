#include "FiguresFuncs.h"

//ѕолучение типа фигурыы
int getChoiceFigure(TFigure** figures_array, int index_of_element)
{
	int figures_choice{};
	TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
	if (ptr_circle)
	{
		figures_choice = 1;
	}
	TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
	if (ptr_ellipse)
	{
		figures_choice = 2;
	}
	TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
	if (ptr_quadrilateral)
	{
		figures_choice = 3;
	}
	TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
	if (ptr_rectangle)
	{
		figures_choice = 4;
	}
	TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
	if (ptr_rhomb)
	{
		figures_choice = 5;
	}
	TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
	if (ptr_trapeze)
	{
		figures_choice = 6;
	}
	return figures_choice;
}
//ѕеремещение
void figuresMoveW(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle->getYPoint() - ptr_circle->getRadius() - 10 >= 100)
			ptr_circle->MoveTo(0, -10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getYPoint() - ptr_ellipse->getSemiMinorAxis() - 10 >= 100)
			ptr_ellipse->MoveTo(0, -10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getYPoint() - 10 >= 100) && (ptr_quadrilateral->getY2Point() - 10 >= 100))
		{
			ptr_quadrilateral->MoveTo(0, -10);
			ptr_quadrilateral->changeBasePoints234(0, -10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getYPoint() - 10 >= 100)
		{
			ptr_rectangle->MoveTo(0, -10);
			ptr_rectangle->changeBasePoints234(0, -10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb->getY2Point() - 10 >= 100)
		{
			ptr_rhomb->MoveTo(0, -10);
			ptr_rhomb->changeBasePoints234(0, -10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if ((ptr_trapeze->getY2Point() - 10 >= 100) && (ptr_trapeze->getY3Point() - 10 >= 100))
		{
			ptr_trapeze->MoveTo(0, -10);
			ptr_trapeze->changeBasePoints234(0, -10);
		}
		break;
	}
	default:
	{
		std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
		break;
	}
	}
}
void figuresMoveA(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle->getXPoint() - ptr_circle->getRadius() - 10 >= 710)
			ptr_circle->MoveTo(-10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getXPoint() - ptr_ellipse->getRadius() - 10 >= 710)
			ptr_ellipse->MoveTo(-10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getXPoint() - 10 >= 710) && (ptr_quadrilateral->getX4Point() - 10 >= 710))
		{
			ptr_quadrilateral->MoveTo(-10, 0);
			ptr_quadrilateral->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getXPoint() - 10 >= 710)
		{
			ptr_rectangle->MoveTo(-10, 0);
			ptr_rectangle->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb->getXPoint() - 10 >= 710)
		{
			ptr_rhomb->MoveTo(-10, 0);
			ptr_rhomb->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze->getXPoint() - 10 >= 710)
		{
			ptr_trapeze->MoveTo(-10, 0);
			ptr_trapeze->changeBasePoints234(-10, 0);
		}
		break;
	}
	default:
	{
		std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
		break;
	}
	}
}
void figuresMoveS(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle->getYPoint() + ptr_circle->getRadius() + 10 <= 895)
			ptr_circle->MoveTo(0, 10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getYPoint() + ptr_ellipse->getSemiMinorAxis() + 10 <= 895)
			ptr_ellipse->MoveTo(0, 10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getY3Point() + 10 <= 895) && (ptr_quadrilateral->getY4Point() + 10 <= 895))
		{
			ptr_quadrilateral->MoveTo(0, 10);
			ptr_quadrilateral->changeBasePoints234(0, 10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getYPoint() + ptr_rectangle->getWidth() + 10 <= 895)
		{
			ptr_rectangle->MoveTo(0, 10);
			ptr_rectangle->changeBasePoints234(0, 10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb->getY4Point() + 10 <= 895)
		{
			ptr_rhomb->MoveTo(0, 10);
			ptr_rhomb->changeBasePoints234(0, 10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if ((ptr_trapeze->getYPoint() + 10 <= 895) && (ptr_trapeze->getY4Point() + 10 <= 895))
		{
			ptr_trapeze->MoveTo(0, 10);
			ptr_trapeze->changeBasePoints234(0, 10);
		}
		break;
	}
	default:
	{
		std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
		break;
	}
	}
}
void figuresMoveD(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle->getXPoint() + ptr_circle->getRadius() + 10 <= 1495)
			ptr_circle->MoveTo(10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getXPoint() + ptr_ellipse->getRadius() + 10 <= 1495)
			ptr_ellipse->MoveTo(10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getX2Point() + 10 <= 1495) && (ptr_quadrilateral->getX3Point() + 10 <= 1495))
		{
			ptr_quadrilateral->MoveTo(10, 0);
			ptr_quadrilateral->changeBasePoints234(10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getXPoint() + ptr_rectangle->getLength() + 10 <= 1495)
		{
			ptr_rectangle->MoveTo(10, 0);
			ptr_rectangle->changeBasePoints234(10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb->getX3Point() + 10 <= 1495)
		{
			ptr_rhomb->MoveTo(10, 0);
			ptr_rhomb->changeBasePoints234(10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if ((ptr_trapeze->getX4Point() + 10 <= 1495) && (ptr_trapeze->getX3Point() + 10 <= 1495))
		{
			ptr_trapeze->MoveTo(10, 0);
			ptr_trapeze->changeBasePoints234(10, 0);
		}
		break;
	}
	default:
	{
		std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
		break;
	}
	}
}
//”даление
void deleteFigure(TFigure**& figures_array, int& size_figures_array)
{
	TFigure** new_array_shapes = new TFigure * [size_figures_array - 1];
	for (int i{}; i < size_figures_array - 1; i++)
	{
		new_array_shapes[i] = figures_array[i];
	}

	int index_of_element{ size_figures_array - 1 };
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle)
			ptr_circle->Free(figures_array[index_of_element]);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse)
			ptr_ellipse->Free(figures_array[index_of_element]);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if (ptr_quadrilateral)
			ptr_quadrilateral->Free(figures_array[index_of_element]);
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle)
			ptr_rectangle->Free(figures_array[index_of_element]);
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb)
			ptr_rhomb->Free(figures_array[index_of_element]);
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze)
			ptr_trapeze->Free(figures_array[index_of_element]);
		break;
	}
	default:
	{
		std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
		break;
	}
	}

	delete[] figures_array;
	size_figures_array -= 1;
	figures_array = new_array_shapes;
}
//»зменение геометрических свойств
void increaseRadius(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if ((ptr_circle->getYPoint() + ptr_circle->getRadius() + 2 <= 895)
			&& (ptr_circle->getXPoint() + ptr_circle->getRadius() + 2 <= 1495)
			&& (ptr_circle->getYPoint() - ptr_circle->getRadius() - 2 >= 100)
			&& (ptr_circle->getXPoint() - ptr_circle->getRadius() - 2 >= 710))
		{
			ptr_circle->changeRadius(2);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseRadius(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(figures_array[index_of_element]) };
		if (ptr_circle->getRadius() >= 10)
		{
			ptr_circle->changeRadius(-2);
			break;
		}
	}
	default:
		break;
	}
}
void increaseSemiMajorAxis(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if ((ptr_ellipse->getXPoint() + ptr_ellipse->getRadius() + 2 <= 1495)
			&& (ptr_ellipse->getXPoint() - ptr_ellipse->getRadius() - 2 >= 710))
		{
			ptr_ellipse->changeRadius(2);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseSemiMajorAxis(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getRadius() - 2 >= 50)
		{
			ptr_ellipse->changeRadius(-2);
			break;
		}
	}
	default:
		break;
	}
}
void increaseSemiMinorAxis(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if ((ptr_ellipse->getYPoint() + ptr_ellipse->getSemiMinorAxis() + 2 <= 895) &&
			(ptr_ellipse->getYPoint() - ptr_ellipse->getSemiMinorAxis() - 2 >= 100))
		{
			ptr_ellipse->changeSemiMinorAxis(2);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseSemiMinorAxis(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if (ptr_ellipse->getSemiMinorAxis() - 2 >= 25)
		{
			ptr_ellipse->changeSemiMinorAxis(-2);
			break;
		}
	}
	default:
		break;
	}
}
void rotateEllipse(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(figures_array[index_of_element]) };
		if ((ptr_ellipse->getXPoint() - ptr_ellipse->getSemiMinorAxis() >= 710) &&
			(ptr_ellipse->getXPoint() + ptr_ellipse->getSemiMinorAxis() <= 1495) &&
			(ptr_ellipse->getYPoint() - ptr_ellipse->getRadius() >= 100) &&
			(ptr_ellipse->getYPoint() + ptr_ellipse->getRadius() <= 895))
		{
			ptr_ellipse->rotateEllipse();
			break;
		}
	}
	default:
		break;
	}
}
void increaseLengthRect(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getXPoint() + ptr_rectangle->getLength() + 5 <= 1495)
		{
			ptr_rectangle->changeDimensions(5, 0);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseLengthRect(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getLength() >= 50)
		{
			ptr_rectangle->changeDimensions(-5, 0);
			break;
		}
	}
	default:
		break;
	}
}
void increaseWidthRect(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getYPoint() + ptr_rectangle->getWidth() + 5 <= 895)
		{
			ptr_rectangle->changeDimensions(0, 5);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseWidthRect(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getWidth() >= 25)
		{
			ptr_rectangle->changeDimensions(0, -5);
			break;
		}
	}
	default:
		break;
	}
}
void rotateRect(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(figures_array[index_of_element]) };
		if (ptr_rectangle->getLength() > ptr_rectangle->getWidth())
		{
			if ((ptr_rectangle->getYPoint() - (ptr_rectangle->getLength() - ptr_rectangle->getWidth()) / 2 >= 100) &&
				(ptr_rectangle->getYPoint() - (ptr_rectangle->getLength() - ptr_rectangle->getWidth()) / 2 + ptr_rectangle->getLength() <= 895))
			{
				ptr_rectangle->rotateRect();
			}
		}
		else if ((ptr_rectangle->getXPoint() - (ptr_rectangle->getWidth() - ptr_rectangle->getLength()) / 2 >= 710) &&
			(ptr_rectangle->getXPoint() - (ptr_rectangle->getWidth() - ptr_rectangle->getLength()) / 2 + ptr_rectangle->getWidth() <= 1495))
		{
			ptr_rectangle->rotateRect();
		}
		break;
	}
	default:
		break;
	}
}
void increaseDimensionsQuadrilateral(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getXPoint() - 1) >= 710 &&
			(ptr_quadrilateral->getYPoint() - 1) >= 100 &&
			(ptr_quadrilateral->getX2Point() + 1) <= 1495 &&
			(ptr_quadrilateral->getY2Point() - 1) >= 100 &&
			(ptr_quadrilateral->getX3Point() + 1) <= 1495 &&
			(ptr_quadrilateral->getY3Point() + 1) <= 895 &&
			(ptr_quadrilateral->getX4Point() - 1) >= 710 &&
			(ptr_quadrilateral->getY4Point() + 1) <= 895)
		{
			ptr_quadrilateral->changeSize(1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseDimensionsQuadrilateral(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(figures_array[index_of_element]) };
		if ((ptr_quadrilateral->getX2Point() - ptr_quadrilateral->getXPoint() - 2 >= 50) &&
			(ptr_quadrilateral->getY3Point() - ptr_quadrilateral->getY2Point() - 2 >= 50))
		{
			ptr_quadrilateral->changeSize(-1);
			break;
		}
	}
	default:
		break;
	}
}
void increaseLengthRhomb(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if ((ptr_rhomb->getY2Point() >= 100) &&
			(ptr_rhomb->getY4Point() <= 900) &&
			(ptr_rhomb->getX3Point() <= 1495))
		{
			ptr_rhomb->changeLength(1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseLengthRhomb(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if (ptr_rhomb->getLength() - 1 >= 30)
		{
			ptr_rhomb->changeLength(-1);
			break;
		}
	}
	default:
		break;
	}
}
void increaseDegreeRhomb(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if ((ptr_rhomb->getDegree() + 1 <= 60) &&
			(ptr_rhomb->getY2Point() >= 100) &&
			(ptr_rhomb->getY4Point() <= 895))
		{
			ptr_rhomb->changeDegree(1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseDegreeRhomb(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(figures_array[index_of_element]) };
		if ((ptr_rhomb->getDegree() - 1 >= 15) &&
			(ptr_rhomb->getX3Point() <= 1495))
		{
			ptr_rhomb->changeDegree(-1);
			break;
		}
	}
	default:
		break;
	}
}
void increaseTopBaseTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze->getX3Point() <= ptr_trapeze->getX4Point())
		{
			ptr_trapeze->changeTopBase(1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseTopBaseTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze->getX4Point() - ptr_trapeze->getX3Point() - 1 <= 50)
		{
			ptr_trapeze->changeTopBase(-1);
			break;
		}
	}
	default:
		break;
	}
}
void increaseHeightTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if ((ptr_trapeze->getY2Point() - 1 >= 100) && (ptr_trapeze->getYPoint() - ptr_trapeze->getY2Point() + 1 <= 100))
		{
			ptr_trapeze->changeHeight(-1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseHeightTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze->getYPoint() - ptr_trapeze->getY2Point() - 1 >= 30)
		{
			ptr_trapeze->changeHeight(1);
			break;
		}
	}
	default:
		break;
	}
}
void increaseBottomBaseTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if ((ptr_trapeze->getX4Point() + 1 <= 1495) && ((ptr_trapeze->getX4Point() + 1) <= (ptr_trapeze->getX3Point() + 60)))
		{
			ptr_trapeze->changeBottomBase(1);
			break;
		}
	}
	default:
		break;
	}
}
void decreaseBottomBaseTrapeze(TFigure** figures_array, int index_of_element)
{
	int figures_choice{ getChoiceFigure(figures_array, index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(figures_array[index_of_element]) };
		if (ptr_trapeze->getX4Point() - 1 >= ptr_trapeze->getX3Point())
		{
			ptr_trapeze->changeBottomBase(-1);
			break;
		}
	}
	default:
		break;
	}
}
