#ifndef CLASS_CITY_H
#define CLASS_CITY_H

class City
{
private:
	std::string city_name{};
	Street* pFirst{}, * pLast{};

public:
	City(const std::string& city_name)
	{
		this->city_name = city_name;
		this->pFirst = new Street();
		this->pLast = this->pFirst;
	}

	bool theCityIsEmpty()
	{
		return (this->pFirst == this->pLast) ? true : false;
	}

	void addNewStreetToTheCity(const std::string& street_name)
	{
		Street* new_street{ new Street(street_name, this->pFirst) };
		this->pLast->setPNext(new_street);
		this->pLast = new_street;
	}

	std::string removeTheFirstStreetOfTheCity()
	{
		std::string removed_street_name{};
		if (!this->theCityIsEmpty())
		{
			Street* removed_street_ptr{ this->pFirst->getPNext() };
			this->pFirst->setPNext(removed_street_ptr->getPNext());
			if (removed_street_ptr == this->pLast)
				this->pLast = this->pFirst;
			removed_street_name = removed_street_ptr->getStreetName();
			delete removed_street_ptr;
		}
		return removed_street_name;
	}

	Street* transitionToTheStreetInTheCity(const std::string& searched_street_name)
	{
		if (!this->theCityIsEmpty())
		{
			Street* temp_ptr{ pFirst->getPNext() };
			while (temp_ptr != pFirst)
			{
				if (temp_ptr->getStreetName() == searched_street_name)
					return temp_ptr;
				else
					temp_ptr = temp_ptr->getPNext();
			}
		}
		return nullptr;
	}

	void showTheCity()
	{
		if (this->theCityIsEmpty())
			std::cout << "Город пуст (не содержит ни улиц, ни домов)." << std::endl;
		else
		{
			std::cout << "Город содержит следующие улицы:" << std::endl;
			Street* temp_ptr{ this->pFirst->getPNext() };
			while (temp_ptr != this->pFirst)
			{
				temp_ptr->showHousesOnTheStreet();
				temp_ptr = temp_ptr->getPNext();
			}
			std::cout << "Больше улиц в данном городе пока нет." << std::endl;
		}
	}

	void setCityName(const std::string& city_name)
	{
		this->city_name = city_name;
	}

	std::string getCityName()
	{
		return city_name;
	}

	Street* getPFirst()
	{
		return this->pFirst;
	}

	Street* getPLast()
	{
		return this->pLast;
	}

	~City()
	{
		std::string removed_street_name{ this->removeTheFirstStreetOfTheCity() };
		while (!removed_street_name.empty())
			removed_street_name = this->removeTheFirstStreetOfTheCity();
		delete this->pFirst;
		this->pFirst = nullptr;
		this->pLast = nullptr;
		std::cout << "Город " << this->getCityName() << " был успешно полностью удален." << std::endl;
	}
};

#endif /* CLASS_CITY_H */