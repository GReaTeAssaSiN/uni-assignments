#include "CinemaTableDBElement.h"

CinemaTableDBElement::CinemaTableDBElement(SqlDataReader^ reader)
{
	CinemaID = reader->GetInt32(0);
	CinemaPicture = reader->IsDBNull(1) ? (array<Byte>^)nullptr : (array<Byte>^)reader->GetSqlBinary(1);
	CinemaName = reader->GetString(2);
	City = reader->GetString(3);
	Street = reader->GetString(4);
	HouseNumber = reader->GetString(5);
	(HouseLetter = reader->IsDBNull(6) ? "" : reader->GetString(6));
	(HouseDesc = reader->IsDBNull(7) ? "-" : reader->GetString(7));
	OpeningTime = reader->GetTimeSpan(8);
	ClosingTime = reader->GetTimeSpan(9);
	(ContactInformation = reader->IsDBNull(10) ? "no contact information" : reader->GetString(10));
}
Int32^ CinemaTableDBElement::getCinemaID()
{
	return this->CinemaID;
}
String^ CinemaTableDBElement::getCinemaName()
{
	return this->CinemaName;
}
String^ CinemaTableDBElement::getCity()
{
	return this->City;
}
String^ CinemaTableDBElement::getStreet()
{
	return this->Street;
}
String^ CinemaTableDBElement::getHouseNumber()
{
	return this->HouseNumber;
}
String^ CinemaTableDBElement::getHouseLetter()
{
	return this->HouseLetter;
}
String^ CinemaTableDBElement::getHouseDesc()
{
	return this->HouseDesc;
}
TimeSpan^ CinemaTableDBElement::getOpeningTime()
{
	return this->OpeningTime;
}
TimeSpan^ CinemaTableDBElement::getClosingTime()
{
	return this->ClosingTime;
}
String^ CinemaTableDBElement::getContactInformation()
{
	return ContactInformation;
}
array<Byte>^ CinemaTableDBElement::getImage()
{
	return this->CinemaPicture;
}