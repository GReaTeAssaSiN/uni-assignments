#ifndef CONTAINER_DYNAMICARRAY_H_
#define CONTAINER_DYNAMICARRAY_H_

#include "SFML//Graphics.hpp"

class DynamicArray
{
private:
	int m_size{};
	TFigure** m_data{};

	void MoveElemsW(int index_of_elem);
	void MoveElemsA(int index_of_elem);
	void MoveElemsS(int index_of_elem);
	void MoveElemsD(int index_of_elem);

public:
	DynamicArray(int size);

	void addNewElem(int index_of_elem, TFigure*& new_graphic_primitive);

	int getChoiceFigureElem(int index_of_elem);

	int getSize();

	TFigure* getElem(int index_of_elem);

	void Iterator(int attribute, int& size_container_figures_dinamic_array, sf::RenderWindow& window);

	void Free();

	~DynamicArray();
};

#endif /* DYNAMICARRAY_H_ */