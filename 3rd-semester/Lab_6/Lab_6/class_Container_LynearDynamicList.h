#ifndef CLASS_CONTAINER_LYNEARDYNAMICLIST_H_
#define CLASS_CONTAINER_LYNEARDYNAMICLIST_H_

#include <SFML/Graphics.hpp>

class LynearDynamicList
{
private:
	class Node
	{
	public:
		TFigure* ptr_data{};
		Node* m_next{};

		Node() = default;

		Node(TFigure* ptr_current_data, Node* ptr_currentNode = nullptr)
			: ptr_data{ ptr_current_data }, m_next{ ptr_currentNode }
		{
			std::cout << "Узел с информацией о только что созданном объекте успешно создан." << std::endl;
		}

		~Node() = default;
	};

	Node* head{};
	int m_size{};

	void MoveElemsW(TFigure* ptr_current_data);
	void MoveElemsA(TFigure* ptr_current_data);
	void MoveElemsS(TFigure* ptr_current_data);
	void MoveElemsD(TFigure* ptr_current_data);

public:
	LynearDynamicList(int number_of_nodes);

	void addNewElem(TFigure* ptr_current_data);

	int getChoiceFigure(TFigure* ptr_current_data);

	TFigure* getNodeData(int i);

	Node* getHead()
	{
		return head;
	}

	int getSize();

	void Iterator(int attribute, sf::RenderWindow& window);

	void Free(LynearDynamicList*& pointer_to_delete_a_linear_dynamic_list_object);

	~LynearDynamicList();
};

#endif /* CLASS_CONTAINER_LYNEARDYNAMICLIST_H_*/