#include "class_TRhomb.h"
#include "constants.h"

void TRhomb::BalanceSides()
{
	m_base_point_x2 = getXPoint() + m_length * cos(m_degree * PI / 180);
	m_base_point_y2 = getYPoint() - m_length * sin(m_degree * PI / 180);
	m_base_point_x3 = getXPoint() + 2 * m_length * cos(m_degree * PI / 180);
	m_base_point_y3 = getYPoint();
	m_base_point_x4 = m_base_point_x2;
	m_base_point_y4 = getYPoint() + m_length * sin(m_degree * PI / 180);
}

TRhomb::TRhomb()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "Создан конструктором по умолчанию объект-ромб с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")\nи длиной стороны Length = "
		<< getLength() << ", \tуглом между стороной и горизонтальной осью: Alpha = " << getDegree() << std::endl;
}

TRhomb::TRhomb(float base_point_x1, float base_point_y1, float length, int degree)
	:TQuadrilateral(base_point_x1, base_point_y1, base_point_x1 + length * cos(degree * PI / 180), base_point_y1 - length * sin(degree * PI / 180), base_point_x1 + 2 * length * cos(degree * PI / 180),
		base_point_y1, base_point_x1 + length * cos(degree * PI / 180), base_point_y1 + length * sin(degree * PI / 180)), m_length{ length }, m_degree{ degree }
{
	BalanceSides();
	std::cout << "Создан конструктором со случайными параметрами объект-ромб с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")\nи длиной стороны Length = "
		<< getLength() << ", \tуглом между стороной и горизонтальной осью: Alpha = " << getDegree() << std::endl;
}

void TRhomb::Show(sf::RenderWindow& window)
{
	TQuadrilateral::Show(window);
}

void TRhomb::Free(TRhomb*& ptr_obj_rhomb)
{
	delete ptr_obj_rhomb;
	ptr_obj_rhomb = nullptr;
}

float TRhomb::getLength()
{
	return m_length;
}

int TRhomb::getDegree()
{
	return m_degree;
}

void TRhomb::changeLength(int dLength)
{
	m_length += dLength;
	BalanceSides();
}

void TRhomb::changeDegree(int dDegree)
{
	m_degree += dDegree;
	BalanceSides();
}

//TRhomb::~TRhomb()
//{
//	std::cout << "Удален объект-ромб с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
//		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")\nи длиной стороны Length = "
//		<< getLength() << ", \tуглом между стороной и горизонтальной осью: Alpha = " << getDegree() << std::endl;
//}