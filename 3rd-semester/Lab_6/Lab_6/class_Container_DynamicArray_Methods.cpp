#include "class_TFigure.h"
#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"
#include "class_Container_DynamicArray.h"

void DynamicArray::MoveElemsW(int index_of_elem)
{
	int figures_choice{ getChoiceFigureElem(index_of_elem) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[index_of_elem]) };
		if (ptr_circle->getYPoint() - ptr_circle->getRadius() - 10 >= 100)
			ptr_circle->MoveTo(0, -10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[index_of_elem]) };
		if (ptr_ellipse->getYPoint() - ptr_ellipse->getSemiMinorAxis() - 10 >= 100)
			ptr_ellipse->MoveTo(0, -10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[index_of_elem]) };
		if ((ptr_quadrilateral->getYPoint() - 10 >= 100) && (ptr_quadrilateral->getY2Point() - 10 >= 100))
		{
			ptr_quadrilateral->MoveTo(0, -10);
			ptr_quadrilateral->changeBasePoints234(0, -10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[index_of_elem]) };
		if (ptr_rectangle->getYPoint() - 10 >= 100)
		{
			ptr_rectangle->MoveTo(0, -10);
			ptr_rectangle->changeBasePoints234(0, -10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[index_of_elem]) };
		if (ptr_rhomb->getY2Point() - 10 >= 100)
		{
			ptr_rhomb->MoveTo(0, -10);
			ptr_rhomb->changeBasePoints234(0, -10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[index_of_elem]) };
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
void DynamicArray::MoveElemsA(int index_of_elem)
{
	int figures_choice{ getChoiceFigureElem(index_of_elem) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[index_of_elem]) };
		if (ptr_circle->getXPoint() - ptr_circle->getRadius() - 10 >= 710)
			ptr_circle->MoveTo(-10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[index_of_elem]) };
		if (ptr_ellipse->getXPoint() - ptr_ellipse->getRadius() - 10 >= 710)
			ptr_ellipse->MoveTo(-10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[index_of_elem]) };
		if ((ptr_quadrilateral->getXPoint() - 10 >= 710) && (ptr_quadrilateral->getX4Point() - 10 >= 710))
		{
			ptr_quadrilateral->MoveTo(-10, 0);
			ptr_quadrilateral->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[index_of_elem]) };
		if (ptr_rectangle->getXPoint() - 10 >= 710)
		{
			ptr_rectangle->MoveTo(-10, 0);
			ptr_rectangle->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[index_of_elem]) };
		if (ptr_rhomb->getXPoint() - 10 >= 710)
		{
			ptr_rhomb->MoveTo(-10, 0);
			ptr_rhomb->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[index_of_elem]) };
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
void DynamicArray::MoveElemsS(int index_of_elem)
{
	int figures_choice{ getChoiceFigureElem(index_of_elem) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[index_of_elem]) };
		if (ptr_circle->getYPoint() + ptr_circle->getRadius() + 10 <= 895)
			ptr_circle->MoveTo(0, 10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[index_of_elem]) };
		if (ptr_ellipse->getYPoint() + ptr_ellipse->getSemiMinorAxis() + 10 <= 895)
			ptr_ellipse->MoveTo(0, 10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[index_of_elem]) };
		if ((ptr_quadrilateral->getY3Point() + 10 <= 895) && (ptr_quadrilateral->getY4Point() + 10 <= 895))
		{
			ptr_quadrilateral->MoveTo(0, 10);
			ptr_quadrilateral->changeBasePoints234(0, 10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[index_of_elem]) };
		if (ptr_rectangle->getYPoint() + ptr_rectangle->getWidth() + 10 <= 895)
		{
			ptr_rectangle->MoveTo(0, 10);
			ptr_rectangle->changeBasePoints234(0, 10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[index_of_elem]) };
		if (ptr_rhomb->getY4Point() + 10 <= 895)
		{
			ptr_rhomb->MoveTo(0, 10);
			ptr_rhomb->changeBasePoints234(0, 10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[index_of_elem]) };
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
void DynamicArray::MoveElemsD(int index_of_elem)
{
	int figures_choice{ getChoiceFigureElem(index_of_elem) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[index_of_elem]) };
		if (ptr_circle->getXPoint() + ptr_circle->getRadius() + 10 <= 1495)
			ptr_circle->MoveTo(10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[index_of_elem]) };
		if (ptr_ellipse->getXPoint() + ptr_ellipse->getRadius() + 10 <= 1495)
			ptr_ellipse->MoveTo(10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[index_of_elem]) };
		if ((ptr_quadrilateral->getX2Point() + 10 <= 1495) && (ptr_quadrilateral->getX3Point() + 10 <= 1495))
		{
			ptr_quadrilateral->MoveTo(10, 0);
			ptr_quadrilateral->changeBasePoints234(10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[index_of_elem]) };
		if (ptr_rectangle->getXPoint() + ptr_rectangle->getLength() + 10 <= 1495)
		{
			ptr_rectangle->MoveTo(10, 0);
			ptr_rectangle->changeBasePoints234(10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[index_of_elem]) };
		if (ptr_rhomb->getX3Point() + 10 <= 1495)
		{
			ptr_rhomb->MoveTo(10, 0);
			ptr_rhomb->changeBasePoints234(10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[index_of_elem]) };
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

DynamicArray::DynamicArray(int size)
	: m_size{ size }
{
	if (size > 0)
	{
		m_data = new TFigure * [size] {};
		std::cout << "Создан контейнер на базе динамического массива из " << m_size << " случайных примитивов." << std::endl;
	}
}

void DynamicArray::addNewElem(int index_of_elem, TFigure*& new_graphic_primitive)
{
	if (index_of_elem + 1 <= m_size)
	{
		m_data[index_of_elem] = new_graphic_primitive;
		std::cout << "В контейнер на базе динамического списка был добавлен новый элемент с индексом: " << index_of_elem << "." << std::endl;
	}
}

int DynamicArray::getChoiceFigureElem(int index_of_elem)
{
	int figures_choice{};
	TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[index_of_elem]) };
	if (ptr_circle)
	{
		figures_choice = 1;
	}
	TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[index_of_elem]) };
	if (ptr_ellipse)
	{
		figures_choice = 2;
	}
	TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[index_of_elem]) };
	if (ptr_quadrilateral)
	{
		figures_choice = 3;
	}
	TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[index_of_elem]) };
	if (ptr_rectangle)
	{
		figures_choice = 4;
	}
	TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[index_of_elem]) };
	if (ptr_rhomb)
	{
		figures_choice = 5;
	}
	TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[index_of_elem]) };
	if (ptr_trapeze)
	{
		figures_choice = 6;
	}
	return figures_choice;
}

int DynamicArray::getSize()
{
	return m_size;
}

TFigure* DynamicArray::getElem(int index_of_elem)
{
	return m_data[index_of_elem];
}

void DynamicArray::Iterator(int attribute, int& size_container_figures_dinamic_array, sf::RenderWindow& window)
{
	for (int i{}; i < size_container_figures_dinamic_array; i++)
	{
		switch (attribute)
		{
		case 1:
		{
			int figures_choice{ getChoiceFigureElem(i) };
			switch (figures_choice)
			{
			case 1:
			{
				TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data[i]) };
				if (ptr_circle)
					ptr_circle->Free(m_data[i]);
				break;
			}
			case 2:
			{
				TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data[i]) };
				if (ptr_ellipse)
					ptr_ellipse->Free(m_data[i]);
				break;
			}
			case 3:
			{
				TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data[i]) };
				if (ptr_quadrilateral)
					ptr_quadrilateral->Free(m_data[i]);
				break;
			}
			case 4:
			{
				TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data[i]) };
				if (ptr_rectangle)
					ptr_rectangle->Free(m_data[i]);
				break;
			}
			case 5:
			{
				TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(m_data[i]) };
				if (ptr_rhomb)
					ptr_rhomb->Free(m_data[i]);
				break;
			}
			case 6:
			{
				TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data[i]) };
				if (ptr_trapeze)
					ptr_trapeze->Free(m_data[i]);
				break;
			}
			default:
			{
				std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
				break;
			}
			}
			std::cout << "Удален " << i << "-ый элемент." << std::endl;
			
			break;
		}
		case 2:
		{
			MoveElemsW(i);
			
			break;
		}
		case 3:
		{
			MoveElemsA(i);
			
			break;
		}
		case 4:
		{
			MoveElemsS(i);
			
			break;
		}
		case 5:
		{
			MoveElemsD(i);
			
			break;
		}
		case 6:
		{
			if ((getChoiceFigureElem(i) == 1) || (getChoiceFigureElem(i) == 2))
			{
				MoveElemsW(i);
			}
			
			break;
		}
		case 7:
		{
			if ((getChoiceFigureElem(i) == 1) || (getChoiceFigureElem(i) == 2))
			{
				MoveElemsA(i);
			}
			
			break;
		}
		case 8:
		{
			if ((getChoiceFigureElem(i) == 1) || (getChoiceFigureElem(i) == 2))
			{
				MoveElemsS(i);
			}
			
			break;
		}
		case 9:
		{
			if ((getChoiceFigureElem(i) == 1) || (getChoiceFigureElem(i) == 2))
			{
				MoveElemsD(i);
			}
			break;
		}
		case 10:
		{
			if ((getChoiceFigureElem(i) >= 3) && (getChoiceFigureElem(i) <= 6))
			{
				MoveElemsW(i);
			}

			break;
		}
		case 11:
		{
			if ((getChoiceFigureElem(i) >= 3) && (getChoiceFigureElem(i) <= 6))
			{
				MoveElemsA(i);
			}
			
			break;
		}
		case 12:
		{
			if ((getChoiceFigureElem(i) >= 3) && (getChoiceFigureElem(i) <= 6))
			{
				MoveElemsS(i);
			}
			
			break;
		}
		case 13:
		{
			if ((getChoiceFigureElem(i) >= 3) && (getChoiceFigureElem(i) <= 6))
			{
				MoveElemsD(i);
			}
			
			break;
		}
		case 14:
		{
			m_data[i]->Show(window);
			
			break;
		}
		default:
		{
			std::cout << "Error! attribute не имеет признака с таким номером." << std::endl;
			break;
		}
		}
	}
}

void DynamicArray::Free()
{
	delete[] m_data;
	m_data = nullptr;
}

DynamicArray::~DynamicArray()
{
	for (int i{}; i < m_size; i++)
	{
		if (m_data)
			delete m_data[i];
	}
	if (m_data)
	{
		delete[] m_data;
		m_data = nullptr;
	}
	std::cout << "Контейнер на базе динамического массива из " << m_size << " случайных примитивов был зачищен и уничтожен." << std::endl;
	m_size = 0;
}