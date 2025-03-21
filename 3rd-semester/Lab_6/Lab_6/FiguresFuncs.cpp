#include "FiguresFuncs.h"

//Изменение геометрических свойств объектов класса-контейнера на базе динамического массива
void increaseRadiusCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseRadiusCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseSemiMajorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseSemiMajorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseSemiMinorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseSemiMinorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void rotateEllipseCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseLengthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseLengthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseWidthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseWidthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void rotateRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseDimensionsQuadrilateralCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseDimensionsQuadrilateralCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseLengthRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseLengthRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseDegreeRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseDegreeRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseTopBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseTopBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseHeightTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseHeightTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void increaseBottomBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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
void decreaseBottomBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element)
{
	int figures_choice{ ptr_container_figures_dinamic_array->getChoiceFigureElem(index_of_element) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_figures_dinamic_array->getElem(index_of_element)) };
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

//Изменение геометрических свойств объектов класса-контейнера на базе линейного динамического списка
void increaseRadiusCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
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
void decreaseRadiusCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
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
void increaseSemiMajorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
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
void decreaseSemiMajorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
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
void increaseSemiMinorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
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
void decreaseSemiMinorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
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
void rotateEllipseCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
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
void increaseLengthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
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
void decreaseLengthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
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
void increaseWidthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
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
void decreaseWidthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
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
void rotateRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
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
void increaseDimensionsQuadrilateralCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
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
void decreaseDimensionsQuadrilateralCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
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
void increaseLengthRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
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
void decreaseLengthRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
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
void increaseDegreeRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
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
void decreaseDegreeRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
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
void increaseTopBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void decreaseTopBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void increaseHeightTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void decreaseHeightTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void increaseBottomBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void decreaseBottomBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dynamic_list, TFigure* ptr_current_data)
{
	int figures_choice{ ptr_container_figures_lynear_dynamic_list->getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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