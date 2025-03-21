#ifndef CLASS_HOUSE_H_
#define CLASS_HOUSE_H_

class House
{
private:
	int house_number{};
	std::string building_type{};
	House* pNext{};

public:
	House()
	{
		this->house_number = -1;
		this->pNext = this;
	}
	House(const int& house_number, const std::string& building_type)
	{
		this->house_number = house_number;
		this->building_type = building_type;
	}
	int getHouseNumber()
	{
		return house_number;
	}
	std::string getBuildingType()
	{
		return building_type;
	}
	void setPNext(House* pNext)
	{
		this->pNext = pNext;
	}
	House* getPNext()
	{
		return pNext;
	}
	~House() 
	{
		this->pNext = nullptr;
		if (this->getHouseNumber() == -1)
			std::cout << "\t* Дом (заголовочный элемент) успешно удален." << std::endl;
		else
			std::cout << "\t* Дом с номером " << this->getHouseNumber() << ", типом строения: " << this->getBuildingType() << ", был успешно удален." << std::endl;
	};
};

#endif /* CLASS_HOUSE_H */