#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class CinemaTableDBElement
{
	private: Int32^ CinemaID{};
	private: array<Byte>^ CinemaPicture{};
	private: String^ CinemaName{};
	private: String^ City{};
	private: String^ Street{};
	private: String^ HouseNumber{};
	private: String^ HouseLetter{};
	private: String^ HouseDesc{};
	private: TimeSpan^ OpeningTime{};
	private: TimeSpan^ ClosingTime{};
	private: String^ ContactInformation{};
	public: CinemaTableDBElement(SqlDataReader^ reader);
	public: Int32^ getCinemaID();
	public: String^ getCinemaName();
	public: String^ getCity();
	public: String^ getStreet();
	public: String^ getHouseNumber();
	public: String^ getHouseLetter();
	public: String^ getHouseDesc();
	public: TimeSpan^ getOpeningTime();
	public: TimeSpan^ getClosingTime();
	public: String^ getContactInformation();
	public: array<Byte>^ getImage();
};

