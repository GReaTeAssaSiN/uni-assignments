#include "class_TFigure.h"
#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"
#include "class_Container_LynearDynamicList.h"

void LynearDynamicList::MoveElemsW(TFigure* ptr_current_data)
{
	int figures_choice{ getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
		if (ptr_circle->getYPoint() - ptr_circle->getRadius() - 10 >= 100)
			ptr_circle->MoveTo(0, -10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
		if (ptr_ellipse->getYPoint() - ptr_ellipse->getSemiMinorAxis() - 10 >= 100)
			ptr_ellipse->MoveTo(0, -10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
		if ((ptr_quadrilateral->getYPoint() - 10 >= 100) && (ptr_quadrilateral->getY2Point() - 10 >= 100))
		{
			ptr_quadrilateral->MoveTo(0, -10);
			ptr_quadrilateral->changeBasePoints234(0, -10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
		if (ptr_rectangle->getYPoint() - 10 >= 100)
		{
			ptr_rectangle->MoveTo(0, -10);
			ptr_rectangle->changeBasePoints234(0, -10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
		if (ptr_rhomb->getY2Point() - 10 >= 100)
		{
			ptr_rhomb->MoveTo(0, -10);
			ptr_rhomb->changeBasePoints234(0, -10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void LynearDynamicList::MoveElemsA(TFigure* ptr_current_data)
{
	int figures_choice{ getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
		if (ptr_circle->getXPoint() - ptr_circle->getRadius() - 10 >= 710)
			ptr_circle->MoveTo(-10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
		if (ptr_ellipse->getXPoint() - ptr_ellipse->getRadius() - 10 >= 710)
			ptr_ellipse->MoveTo(-10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
		if ((ptr_quadrilateral->getXPoint() - 10 >= 710) && (ptr_quadrilateral->getX4Point() - 10 >= 710))
		{
			ptr_quadrilateral->MoveTo(-10, 0);
			ptr_quadrilateral->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
		if (ptr_rectangle->getXPoint() - 10 >= 710)
		{
			ptr_rectangle->MoveTo(-10, 0);
			ptr_rectangle->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
		if (ptr_rhomb->getXPoint() - 10 >= 710)
		{
			ptr_rhomb->MoveTo(-10, 0);
			ptr_rhomb->changeBasePoints234(-10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void LynearDynamicList::MoveElemsS(TFigure* ptr_current_data)
{
	int figures_choice{ getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
		if (ptr_circle->getYPoint() + ptr_circle->getRadius() + 10 <= 895)
			ptr_circle->MoveTo(0, 10);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
		if (ptr_ellipse->getYPoint() + ptr_ellipse->getSemiMinorAxis() + 10 <= 895)
			ptr_ellipse->MoveTo(0, 10);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
		if ((ptr_quadrilateral->getY3Point() + 10 <= 895) && (ptr_quadrilateral->getY4Point() + 10 <= 895))
		{
			ptr_quadrilateral->MoveTo(0, 10);
			ptr_quadrilateral->changeBasePoints234(0, 10);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
		if (ptr_rectangle->getYPoint() + ptr_rectangle->getWidth() + 10 <= 895)
		{
			ptr_rectangle->MoveTo(0, 10);
			ptr_rectangle->changeBasePoints234(0, 10);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
		if (ptr_rhomb->getY4Point() + 10 <= 895)
		{
			ptr_rhomb->MoveTo(0, 10);
			ptr_rhomb->changeBasePoints234(0, 10);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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
void LynearDynamicList::MoveElemsD(TFigure* ptr_current_data)
{
	int figures_choice{ getChoiceFigure(ptr_current_data) };
	switch (figures_choice)
	{
	case 1:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
		if (ptr_circle->getXPoint() + ptr_circle->getRadius() + 10 <= 1495)
			ptr_circle->MoveTo(10, 0);
		break;
	}
	case 2:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
		if (ptr_ellipse->getXPoint() + ptr_ellipse->getRadius() + 10 <= 1495)
			ptr_ellipse->MoveTo(10, 0);
		break;
	}
	case 3:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
		if ((ptr_quadrilateral->getX2Point() + 10 <= 1495) && (ptr_quadrilateral->getX3Point() + 10 <= 1495))
		{
			ptr_quadrilateral->MoveTo(10, 0);
			ptr_quadrilateral->changeBasePoints234(10, 0);
		}
		break;
	}
	case 4:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
		if (ptr_rectangle->getXPoint() + ptr_rectangle->getLength() + 10 <= 1495)
		{
			ptr_rectangle->MoveTo(10, 0);
			ptr_rectangle->changeBasePoints234(10, 0);
		}
		break;
	}
	case 5:
	{
		TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
		if (ptr_rhomb->getX3Point() + 10 <= 1495)
		{
			ptr_rhomb->MoveTo(10, 0);
			ptr_rhomb->changeBasePoints234(10, 0);
		}
		break;
	}
	case 6:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
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

LynearDynamicList::LynearDynamicList(int number_of_nodes)
{
	std::cout << "Создан контейнер на базе линейного динамического списка, рассчитанный на " << number_of_nodes << " узлов(-а)." << std::endl;
}

void LynearDynamicList::addNewElem(TFigure* ptr_current_data)
{
	if (head == nullptr)
	{
		head = new Node(ptr_current_data);
	}
	else
	{
		Node* current{ head };
		while (current->m_next != nullptr)
		{
			current = current->m_next;
		}
		current->m_next = new Node(ptr_current_data);
	}

	m_size++;
}

int LynearDynamicList::getChoiceFigure(TFigure* ptr_current_data)
{
	int figures_choice{};
	TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_current_data) };
	if (ptr_circle)
	{
		figures_choice = 1;
	}
	TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_current_data) };
	if (ptr_ellipse)
	{
		figures_choice = 2;
	}
	TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_current_data) };
	if (ptr_quadrilateral)
	{
		figures_choice = 3;
	}
	TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_current_data) };
	if (ptr_rectangle)
	{
		figures_choice = 4;
	}
	TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(ptr_current_data) };
	if (ptr_rhomb)
	{
		figures_choice = 5;
	}
	TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_current_data) };
	if (ptr_trapeze)
	{
		figures_choice = 6;
	}
	return figures_choice;
}

TFigure* LynearDynamicList::getNodeData(int i)
{
	int count = 0;
	Node* temp{ head };
	while (count != i)
	{
		temp = temp->m_next;
		count++;
	}
	return temp->ptr_data;
}

int LynearDynamicList::getSize()
{
	return m_size;
}

void LynearDynamicList::Iterator(int attribute, sf::RenderWindow& window)
{
	Node* temp{ head };
	for (int i{}; i < m_size; i++)
	{
		switch (attribute)
		{
		case 1:
		{
			Node* temp{ head };
			head = head->m_next;

			int figures_choice{ getChoiceFigure(temp->ptr_data) };
			switch (figures_choice)
			{
			case 1:
			{
				TCircle* ptr_circle{ dynamic_cast<TCircle*>(temp->ptr_data) };
				if (ptr_circle)
					ptr_circle->Free(temp->ptr_data);
				break;
			}
			case 2:
			{
				TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(temp->ptr_data) };
				if (ptr_ellipse)
					ptr_ellipse->Free(temp->ptr_data);
				break;
			}
			case 3:
			{
				TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(temp->ptr_data) };
				if (ptr_quadrilateral)
					ptr_quadrilateral->Free(temp->ptr_data);
				break;
			}
			case 4:
			{
				TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(temp->ptr_data) };
				if (ptr_rectangle)
					ptr_rectangle->Free(temp->ptr_data);
				break;
			}
			case 5:
			{
				TRhomb* ptr_rhomb{ dynamic_cast<TRhomb*>(temp->ptr_data) };
				if (ptr_rhomb)
					ptr_rhomb->Free(temp->ptr_data);
				break;
			}
			case 6:
			{
				TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(temp->ptr_data) };
				if (ptr_trapeze)
					ptr_trapeze->Free(temp->ptr_data);
				break;
			}
			default:
			{
				std::cout << "Error! figures_choice не совпадает ни с одним типом." << std::endl;
				break;
			}
			}
			delete temp;
			std::cout << "Удален " << i + 1 << "-й узел." << std::endl;

			break;
		}
		case 2:
		{
			MoveElemsW(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 3:
		{
			MoveElemsA(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 4:
		{
			MoveElemsS(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 5:
		{
			MoveElemsD(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 6:
		{
			if ((getChoiceFigure(temp->ptr_data) == 1) || (getChoiceFigure(temp->ptr_data) == 2))
				MoveElemsW(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 7:
		{
			if ((getChoiceFigure(temp->ptr_data) == 1) || (getChoiceFigure(temp->ptr_data) == 2))
				MoveElemsA(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 8:
		{
			if ((getChoiceFigure(temp->ptr_data) == 1) || (getChoiceFigure(temp->ptr_data) == 2))
				MoveElemsS(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 9:
		{
			if ((getChoiceFigure(temp->ptr_data) == 1) || (getChoiceFigure(temp->ptr_data) == 2))
				MoveElemsD(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 10:
		{
			if ((getChoiceFigure(temp->ptr_data) >= 3) && (getChoiceFigure(temp->ptr_data) <= 6))
				MoveElemsW(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 11:
		{
			if ((getChoiceFigure(temp->ptr_data) >= 3) && (getChoiceFigure(temp->ptr_data) <= 6))
				MoveElemsA(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 12:
		{
			if ((getChoiceFigure(temp->ptr_data) >= 3) && (getChoiceFigure(temp->ptr_data) <= 6))
				MoveElemsS(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 13:
		{
			if ((getChoiceFigure(temp->ptr_data) >= 3) && (getChoiceFigure(temp->ptr_data) <= 6))
				MoveElemsD(temp->ptr_data);
			temp = temp->m_next;
			break;
		}
		case 14:
		{
			temp->ptr_data->Show(window);
			temp = temp->m_next;

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

void LynearDynamicList::Free(LynearDynamicList*& pointer_to_delete_a_linear_dynamic_list_object)
{
	delete pointer_to_delete_a_linear_dynamic_list_object;
	pointer_to_delete_a_linear_dynamic_list_object = nullptr;
}

LynearDynamicList::~LynearDynamicList()
{
	for (int i{}; i < m_size; i++)
	{
		if (head != nullptr)
		{
			Node* temp{ head };
			head = head->m_next;
			delete temp->ptr_data;
			delete temp;
		}
	}
	std::cout << "Контейнер на базе линейного динамического списка был зачищен и уничтожен." << std::endl;
	m_size = 0;
}