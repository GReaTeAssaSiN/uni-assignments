#include "class_TFigure.h"

TFigure::TFigure()
{
	std::cout << "Создан конструктором по умолчанию объект-точка с координатами:\n(" << m_base_point_x << ", " << m_base_point_y << ")" << std::endl;
}

TFigure::TFigure(float x_point, float y_point)
	: m_base_point_x{ x_point }, m_base_point_y{ y_point }
{
	std::cout << "Создан конструктором со случайными параметрами объект-точка с координатами:\n(" << m_base_point_x << ", " << m_base_point_y << ")" << std::endl;
}

float TFigure::getXPoint()
{
	return m_base_point_x;
}

float TFigure::getYPoint()
{
	return m_base_point_y;
}

void TFigure::setXPoint(float x_point)
{
	m_base_point_x = x_point;
}

void TFigure::setYPoint(float y_point)
{
	m_base_point_y = y_point;
}

void TFigure::setFillColor(int red, int green, int blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
}

void TFigure::setOutColor(int out_red, int out_green, int out_blue)
{
	m_out_red = out_red;
	m_out_green = out_green;
	m_out_blue = out_blue;
}

void TFigure::setVisibility(int visibility)
{
	m_visibility = visibility;
}

//TFigure::~TFigure()
//	{
//		std::cout << "Удален объект-точка с координатами:\n(" << m_base_point_x << ", " << m_base_point_y << ")" << std::endl << std::endl;
//	}