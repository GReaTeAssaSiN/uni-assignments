#include <iostream>
#include <string>
#include "class_Street.h"
#include "class_House.h"

Street::Street()
{
	head_house_ptr = new House();
}

bool Street::theStreetIsEmpty()
{
	return (this->getHeadHousePtr()->getPNext() == this->getHeadHousePtr()) ? true : false;
}

void Street::addNewHouseToTheStreet(const int& house_number, const std::string& building_type)
{
	House* new_house_ptr = new House(house_number, building_type);
	if (this->theStreetIsEmpty())
	{
		this->getHeadHousePtr()->setPNext(new_house_ptr);
		new_house_ptr->setPNext(this->getHeadHousePtr());
	}
	else
	{
		House* temp_ptr{ this->getHeadHousePtr() };
		while (temp_ptr->getPNext() != this->getHeadHousePtr())
		{
			if (temp_ptr->getPNext()->getHouseNumber() <= house_number)
				temp_ptr = temp_ptr->getPNext();
			else
				break;
		}
		House* temp_next_ptr{ temp_ptr->getPNext() };
		temp_ptr->setPNext(new_house_ptr);
		new_house_ptr->setPNext(temp_next_ptr);
	}
}

int Street::removeTheHouseFromTheStreet(const int& house_number)
{
	House* prev_removed_house_ptr{ this->houseSearchOnTheStreet(house_number) };
	if (prev_removed_house_ptr != nullptr)
	{
		House* removed_house_ptr{ prev_removed_house_ptr->getPNext() };
		prev_removed_house_ptr->setPNext(removed_house_ptr->getPNext());
		delete removed_house_ptr;
		return house_number;
	}
	return -1;
}

House* Street::houseSearchOnTheStreet(const int& house_number)
{
	if (!this->theStreetIsEmpty())
	{
		House* prev_searched_house_ptr{ this->getHeadHousePtr() };
		while (prev_searched_house_ptr->getPNext() != this->getHeadHousePtr())
		{
			if (prev_searched_house_ptr->getPNext()->getHouseNumber() == house_number)
				return prev_searched_house_ptr;
			prev_searched_house_ptr = prev_searched_house_ptr->getPNext();
		}
	}
	return nullptr;
}

void Street::showHousesOnTheStreet()
{
	if (!this->theStreetIsEmpty())
	{
		std::cout << "\t* Улица " << this->getStreetName() << ". На ней расположены следующие дома:" << std::endl;
		House* temp_ptr{ this->getHeadHousePtr()->getPNext() };
		while (temp_ptr != this->getHeadHousePtr())
		{
			std::cout << "\t\tДом номер " << temp_ptr->getHouseNumber() << ", тип строения: " << temp_ptr->getBuildingType() << "." << std::endl;
			temp_ptr = temp_ptr->getPNext();
		}
		std::cout << "\t\t* Больше домов нет." << std::endl;
	}
	else
		std::cout << "\t* Улица " << this->getStreetName() << ". На ней пока нет домов." << std::endl;
}

std::string Street::getStreetName()
{
	return street_name;
}
void Street::setStreetName(const std::string& street_name)
{
	this->street_name = street_name;
}
House* Street::getHeadHousePtr()
{
	return head_house_ptr;
}
Street* Street::getPNext()
{
	return pNext;
}
void Street::setPNext(Street* pNext)
{
	this->pNext = pNext;
}

Street::~Street()
{
	if (this->getStreetName().empty())
		std::cout << "\t* Заголовочный элемент улиц был успешно удален." << std::endl;
	else
		std::cout << "\t* Улица " << this->getStreetName() << " была успешна удалена со всеми существующими на ней домами.." << std::endl;
}