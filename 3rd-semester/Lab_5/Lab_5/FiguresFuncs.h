#ifndef FIGURESFUNCS_H_
#define FIGURESFUNCS_H_

#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"

//����������� ���� ������
int getChoiceFigure(TFigure** figures_array, int index_of_element);
//�����������
void figuresMoveW(TFigure** figures_array, int index_of_element);
void figuresMoveA(TFigure** figures_array, int index_of_element);
void figuresMoveS(TFigure** figures_array, int index_of_element);
void figuresMoveD(TFigure** figures_array, int index_of_element);
//��������
void deleteFigure(TFigure**& figures_array, int& size_figures_array);
//��������� �������������� �������
void increaseRadius(TFigure** figures_array, int index_of_element);
void decreaseRadius(TFigure** figures_array, int index_of_element);
void increaseSemiMajorAxis(TFigure** figures_array, int index_of_element);
void decreaseSemiMajorAxis(TFigure** figures_array, int index_of_element);
void increaseSemiMinorAxis(TFigure** figures_array, int index_of_element);
void decreaseSemiMinorAxis(TFigure** figures_array, int index_of_element);
void rotateEllipse(TFigure** figures_array, int index_of_element);
void increaseLengthRect(TFigure** figures_array, int index_of_element);
void decreaseLengthRect(TFigure** figures_array, int index_of_element);
void increaseWidthRect(TFigure** figures_array, int index_of_element);
void decreaseWidthRect(TFigure** figures_array, int index_of_element);
void rotateRect(TFigure** figures_array, int index_of_element);
void increaseDimensionsQuadrilateral(TFigure** figures_array, int index_of_element);
void decreaseDimensionsQuadrilateral(TFigure** figures_array, int index_of_element);
void increaseLengthRhomb(TFigure** figures_array, int index_of_element);
void decreaseLengthRhomb(TFigure** figures_array, int index_of_element);
void increaseDegreeRhomb(TFigure** figures_array, int index_of_element);
void decreaseDegreeRhomb(TFigure** figures_array, int index_of_element);
void increaseTopBaseTrapeze(TFigure** figures_array, int index_of_element);
void decreaseTopBaseTrapeze(TFigure** figures_array, int index_of_element);
void increaseHeightTrapeze(TFigure** figures_array, int index_of_element);
void decreaseHeightTrapeze(TFigure** figures_array, int index_of_element);
void increaseBottomBaseTrapeze(TFigure** figures_array, int index_of_element);
void decreaseBottomBaseTrapeze(TFigure** figures_array, int index_of_element);


#endif /* FIGURESFUNCS_H_*/