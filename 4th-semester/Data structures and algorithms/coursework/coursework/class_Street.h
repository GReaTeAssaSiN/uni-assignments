#ifndef CLASS_STREET_H
#define CLASS_STREET_H_

class Street
{
private:
	std::string street_name{};
	House* head_house_ptr{};
	Street* pNext{};

public:
	Street()
	{
		this->pNext = this;
		this->head_house_ptr = new House();
	}
	Street(const std::string street_name, Street* pFirst) 
	{
		this->street_name = street_name;
		this->pNext = pFirst;
		this->head_house_ptr = new House();
	}
	
	bool theStreetIsEmpty()
	{
		return (this->head_house_ptr->getPNext() == this->head_house_ptr) ? true : false;
	}

	void addNewHouseToTheStreet(const int& house_number, const std::string& building_type)
	{
		House* new_house_ptr = new House(house_number, building_type);
		if (this->theStreetIsEmpty())
		{
			this->head_house_ptr->setPNext(new_house_ptr);
			new_house_ptr->setPNext(this->head_house_ptr);
		}
		else
		{
			House* temp_ptr{ this->head_house_ptr };
			while (temp_ptr->getPNext() != this->head_house_ptr)
			{
				if (temp_ptr->getPNext()->getHouseNumber() > house_number)
					break;
				temp_ptr = temp_ptr->getPNext();
			}
			House* temp_next_ptr{ temp_ptr->getPNext() };
			temp_ptr->setPNext(new_house_ptr);
			new_house_ptr->setPNext(temp_next_ptr);
		}
	}

	int removeTheHouseFromTheStreet(const int& house_number)
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

	House* houseSearchOnTheStreet(const int& house_number)
	{
		if (!this->theStreetIsEmpty())
		{
			House* prev_searched_house_ptr{ this->head_house_ptr };
			while (prev_searched_house_ptr->getPNext() != this->head_house_ptr)
			{
				if (prev_searched_house_ptr->getPNext()->getHouseNumber() == house_number)
					return prev_searched_house_ptr;
				prev_searched_house_ptr = prev_searched_house_ptr->getPNext();
			}
		}
		return nullptr;
	}

	void showHousesOnTheStreet()
	{
		if (!this->theStreetIsEmpty())
		{
			std::cout << "- Улица " << this->getStreetName() << ":" << std::endl;
			House* temp_ptr{ this->head_house_ptr->getPNext()};
			while (temp_ptr != this->head_house_ptr)
			{
				std::cout << "\t* Дом c номером " << temp_ptr->getHouseNumber() << ", тип строения: " << temp_ptr->getBuildingType() << "." << std::endl;
				temp_ptr = temp_ptr->getPNext();
			}
			std::cout << "\tБольше домов на данной улице нет." << std::endl;
		}
		else
			std::cout << "- Улица " << this->getStreetName() << ": дома отсутствуют." << std::endl;
	}

	std::string getStreetName()
	{
		return street_name;
	}

	House* getHeadHousePtr()
	{
		return head_house_ptr;
	}

	Street* getPNext()
	{
		return pNext;
	}
	void setPNext(Street* pNext)
	{
		this->pNext = pNext;
	}

	~Street()
	{
		int removed_house_number{ this->getHeadHousePtr()->getPNext()->getHouseNumber() };
		while (this->removeTheHouseFromTheStreet(removed_house_number) != -1)
			removed_house_number = this->getHeadHousePtr()->getPNext()->getHouseNumber();
		delete this->getHeadHousePtr();
		this->head_house_ptr = nullptr;
		this->pNext = nullptr;
		if (this->getStreetName().empty())
			std::cout << "- Улица (заголовочный элемент) успешно удалена." << std::endl;
		else
			std::cout << "- Улица " << this->getStreetName() << " была успешна удалена со всеми существующими на ней домами." << std::endl;
	}
};

#endif /* CLASS_STREET_H_ */