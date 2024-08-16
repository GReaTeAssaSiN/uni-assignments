#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class DataBaseQueries
{
	private: SqlConnection^ conn{};
	private: SqlConnectionStringBuilder^ connStringBuilder{};
	private: SqlDataReader^ reader{};
	private: SqlDataAdapter^ adapter{};
	public: void ConnectToDB();
	public: void openConnection();
	public: void closeConnection();
	public: Boolean logInUserAccount(String^ userLogin, String^ userPswd);
	public: Boolean checkLogInAdminAccount(String^ userLogin, String^ userPswd);
	public: Boolean checkNewUserAccount(String^ userLogin);
	public: Boolean addNewUserAccountData(String^ userLogin, String^ userPswd);
	public: SqlDataReader^ getReaderSearchedCinemaCatalog(String^ cinemaNamePart);
	public: SqlDataReader^ getReaderCinemaCatalog();
	public: SqlDataReader^ getReaderSearchedMovieCatalog(String^ movieNamePart, Int32^ cinemaID);
	public: SqlDataReader^ getReaderMovieCatalog(Int32^ cinemaID);
	public: SqlDataReader^ getReaderReviewCatalog(Int32^ cinemaID, Int32^ movieID);
	public: SqlDataReader^ getReaderCinemaNameBox();
	public: SqlDataReader^ getReaderMovieNameBox(Int32^ cinemaID);
	public: void addNewReviewToDB(Int32^ CinemaID, Int32^ MovieID, String^ TranscriptID, String^ UserLogin, String^ Comment);
	public: Int32^ getCinemaIDbyCinemaName(String^ cinemaName);
	public: Int32^ getMovieIDbyMovieName(Int32^ cinemaID, String^ movieName);
	public: String^ getMainAdminLogin();
	public: void userInformationShow(DataGridView^ data);
	public: void userInfromationShowForNotMainAdmin(DataGridView^ data);
	public: void cinemaShow(DataGridView^ data);
	public: void movieShow(DataGridView^ data);
	public: void commentShow(DataGridView^ data);
	public: Boolean addNewUserAccountFromAdmin(String^ userLogin, String^ userPswd, String^ userRole, String^ adminLogin);
	public: Boolean updateUserAccountFromAdmin(String^ userID, String^ userLogin, String^ userPswd, String^ userRole, String^ adminLogin);
	public: Boolean deleteUserAccountFromAdmin(String^ userID, String^ adminLogin);
	public: Boolean deleteCinemaFromAdmin(String^ cinemaID);
	public: Boolean addNewCinemaFromAdmin(String^ CinemaPicturePath, String^ CinemaName, String^ City, String^ Street, String^ HouseNumber, String^ HouseLetter, String^ HouseDescr, String^ OpeningTime, String^ ClosingTime, String^ ContactInf);
	public: Boolean updateCinemaFromAdmin(String^ cinemaID, String^ CinemaPicturePath, String^ CinemaName, String^ City, String^ Street, String^ HouseNumber, String^ HouseLetter, String^ HouseDescr, String^ OpeningTime, String^ ClosingTime, String^ ContactInf);
	public: Boolean deleteMovieFromAdmin(String^ movieID, String^ cinemaName);
	public: Boolean addMovieFromAdmin(String^ movieName, String^ release, String^ genre, String^ ageLimit, String^ duration, String^ movieFormat, String^ cinemaName);
	public: Boolean updateMovieFromAdmin(String^ movieID, String^ movieName, String^ release, String^ genre, String^ ageLimit, String^ duration, String^ movieFormat, String^ cinemaName);
	public: Boolean deleteReviewFromAdmin(String^ reviewID);
	public: Boolean addReviewFromAdmin(String^ reviewID, TextBox^ comment);
	public: Boolean updateReviewFromAdmin(String^ reviewID, String^ comment);
};