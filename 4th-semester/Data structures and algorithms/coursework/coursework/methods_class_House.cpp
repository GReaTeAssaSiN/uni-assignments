#include <iostream>
#include <string>
#include "class_House.h"

House::House()
{
	pNext = this;
}
House::House(const int& house_number, const std::string& building_type)
{
	this->house_number = house_number;
	this->building_type = building_type;
}
int House::getHouseNumber()
{
	return house_number;
}
std::string House::getBuildingType()
{
	return building_type;
}
void House::setPNext(House* pNext)
{
	this->pNext = pNext;
}
House* House::getPNext()
{
	return pNext;
}
House::~House()
{
	if (this->getHouseNumber() == -1)
		std::cout << "\t\t* Заголовочный элемент списка домов был успешно удален." << std::endl;
	else
		std::cout << "\t\t* Дом с номером " << this->getHouseNumber() << " и типом строения " << this->getBuildingType() << " был успешно удален." << std::endl;
};