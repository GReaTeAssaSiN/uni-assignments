#include <iostream>
#include <string>
#include "class_City.h"
#include "class_Street.h"
#include "class_House.h"

City::City(const std::string& city_name)
{
	this->city_name = city_name;
	this->pFirst = new Street();
	this->pFirst->setPNext(pFirst);
	this->pLast = pFirst;
}

bool City::theCityIsEmpty()
{
	return (this->pFirst == this->pLast) ? true : false;
}

void City::addNewStreetToTheCity(const std::string& street_name)
{
	Street* new_street{ new Street{} };
	this->pLast->setPNext(new_street);
	this->pLast = new_street;
	this->pLast->setPNext(pFirst);
	new_street->setStreetName(street_name);
}

std::string City::removeTheFirstStreetOfTheCity()
{
	if (!this->theCityIsEmpty())
	{
		Street* removed_street_ptr{ this->pFirst->getPNext() };
		std::string removed_street_name{ removed_street_ptr->getStreetName() };
		House* removed_house_ptr{ removed_street_ptr->getHeadHousePtr()->getPNext() };
		int removed_house_number{ removed_house_ptr->getHouseNumber() };
		std::string removed_house_type_building{ removed_house_ptr->getBuildingType() };
		while (removed_street_ptr->removeTheHouseFromTheStreet(removed_house_number) != -1)
		{
			removed_house_ptr = removed_street_ptr->getHeadHousePtr()->getPNext();
			removed_house_number = removed_house_ptr->getHouseNumber();
			removed_house_type_building = removed_house_ptr->getBuildingType();
		}
		delete removed_street_ptr->getHeadHousePtr();
		this->pFirst->setPNext(removed_street_ptr->getPNext());
		if (removed_street_ptr == this->pLast)
			this->pLast = this->pFirst;
		delete removed_street_ptr;
		return removed_street_name;
	}
	else
		return "\0";
}

Street* City::streetSearchInTheCity(const std::string& searched_street_name)
{
	if (!this->theCityIsEmpty())
	{
		Street* temp{ pFirst->getPNext() };
		while (temp != pFirst)
		{
			if (temp->getStreetName() == searched_street_name)
				return temp;
			else
				temp = temp->getPNext();
		}
	}
	return nullptr;
}

void City::showTheCity()
{
	if (this->theCityIsEmpty())
		std::cout << "Город не содержит улиц." << std::endl;
	else
	{
		std::cout << "Город содержит следующие улицы:" << std::endl;
		Street* temp_ptr{ this->pFirst->getPNext() };
		while (temp_ptr != this->pFirst)
		{
			temp_ptr->showHousesOnTheStreet();
			temp_ptr = temp_ptr->getPNext();
		}
		std::cout << "* Больше улиц в данном городе пока нет." << std::endl;
	}
}

void City::setCityName(const std::string& city_name)
{
	this->setCityName
}

std::string City::getCityName()
{
	return city_name;
}


std::string getCityName();
void setPFirst(Street* pFirst);
Street* getPFirst();
void setPLast(Street* pLast);
Street* getPLast();

City::~City()
{
	std::string removed_street_name{ this->removeTheFirstStreetOfTheCity() };
	while (!removed_street_name.empty())
		removed_street_name = this->removeTheFirstStreetOfTheCity();
	delete pFirst->getHeadHousePtr();
	delete pFirst;
	this->pFirst = nullptr;
	this->pLast = nullptr;
	std::cout << "Город " << this->getCityName() << " был полностью успешно удален." << std::endl;
}