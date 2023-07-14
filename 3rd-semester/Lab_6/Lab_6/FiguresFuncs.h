#ifndef FIGURESFUNCS_H_
#define FIGURESFUNCS_H_

#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"
#include "class_Container_DynamicArray.h"
#include "class_Container_LynearDynamicList.h"

//Изменение геометрических свойств объектов класса-контейнера на базе динамического массива
void increaseRadiusCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseRadiusCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseSemiMajorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseSemiMajorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseSemiMinorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseSemiMinorAxisCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void rotateEllipseCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseLengthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseLengthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseWidthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseWidthRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void rotateRectCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseDimensionsQuadrilateralCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseDimensionsQuadrilateralCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseLengthRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseLengthRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseDegreeRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseDegreeRhombCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseTopBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseTopBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseHeightTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseHeightTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void increaseBottomBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);
void decreaseBottomBaseTrapezeCFDA(DynamicArray* ptr_container_figures_dinamic_array, int index_of_element);

//Изменение геометрических свойств объектов класса-контейнера на базе линейного динамического списка
void increaseRadiusCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseRadiusCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseSemiMajorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseSemiMajorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseSemiMinorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseSemiMinorAxisCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void rotateEllipseCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseLengthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseLengthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseWidthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseWidthRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void rotateRectCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseDimensionsQuadrilateralCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseDimensionsQuadrilateralCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseLengthRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseLengthRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseDegreeRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseDegreeRhombCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseTopBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseTopBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseHeightTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseHeightTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void increaseBottomBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);
void decreaseBottomBaseTrapezeCFLDL(LynearDynamicList* ptr_container_figures_lynear_dinamic_list, TFigure* ptr_current_data);


#endif /* FIGURESFUNCS_H_*/