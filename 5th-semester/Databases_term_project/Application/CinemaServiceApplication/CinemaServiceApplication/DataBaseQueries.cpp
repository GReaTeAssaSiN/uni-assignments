#include "DataBaseQueries.h"

//����������� ��� ���������� ���������� � ��.
void DataBaseQueries::ConnectToDB()
{
	//Data Source=GORSHKOVALOPC;Initial Catalog=CinemaService;Integrated Security=True.
	connStringBuilder = gcnew SqlConnectionStringBuilder();
	connStringBuilder->DataSource = "GORSHKOVALOPC";
	connStringBuilder->InitialCatalog = "CinemaService";
	connStringBuilder->IntegratedSecurity = true;
	conn = gcnew SqlConnection(Convert::ToString(connStringBuilder));
}
void DataBaseQueries::openConnection()
{
	conn->Open();
}
void DataBaseQueries::closeConnection()
{
	if (conn != nullptr)
		conn->Close();
}
//���������������� �������.
SqlDataReader^ DataBaseQueries::getReaderSearchedCinemaCatalog(String^ cinemaNamePart)
{
	String^ query = "SELECT * FROM Cinema WHERE CinemaName LIKE '%" + cinemaNamePart->ToLower() + "%'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
SqlDataReader^ DataBaseQueries::getReaderSearchedMovieCatalog(String^ movieNamePart, Int32^ cinemaID)
{
	String^ query = "SELECT Movie.MovieID, Movie.MovieName, Movie.Release, Movie.Genre, Movie.AgeLimit, Movie.Duration, Movie.MovieFormat FROM " +
		"(Movie JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE CinemaMovie.CinemaID = " + cinemaID->ToString() + " AND MovieName LIKE '%" + movieNamePart->ToLower() + "%'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
Boolean DataBaseQueries::logInUserAccount(String^ userLogin, String^ userPswd)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT UserLogin, UserPswd FROM UserInformation WHERE UserLogin = '" + userLogin + "' AND UserPswd = '" + userPswd + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 1)
	{
		MessageBox::Show("�� ������� �����!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return true;
	}
	else
	{
		MessageBox::Show("������ �������� �� ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
}
Boolean DataBaseQueries::checkLogInAdminAccount(String^ userLogin, String^ userPswd)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT UserLogin, UserPswd, UserRole FROM UserInformation WHERE UserLogin = '" + userLogin + "' AND UserPswd = '" + userPswd + "' AND UserRole = 'Admin'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
		return false;
	else
		return true;
}
Boolean DataBaseQueries::checkNewUserAccount(String^ userLogin)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT UserLogin FROM UserInformation WHERE UserLogin = '" + userLogin + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
		return true;
	else
	{
		MessageBox::Show("������������ ��� ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
}
Boolean DataBaseQueries::addNewUserAccountData(String^ userLogin, String^ userPswd)
{
	this->ConnectToDB();
	this->openConnection();

	Boolean succesful{};
	String^ query = "INSERT INTO UserInformation (UserLogin, UserPswd) VALUES ('" + userLogin + "', '" + userPswd + "')";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	if (SQL_command->ExecuteNonQuery())
	{
		MessageBox::Show("�� ������� ������������������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		succesful = true;
	}
	else
	{
		MessageBox::Show("������� �� ������. ������ �� ������� �������!");
		succesful = false;
	}

	this->closeConnection();
	return succesful;
}
SqlDataReader^ DataBaseQueries::getReaderCinemaCatalog()
{
	String^ query = "SELECT * FROM Cinema";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
SqlDataReader^ DataBaseQueries::getReaderMovieCatalog(Int32^ cinemaID)
{
	String^ query = "SELECT * FROM (Movie JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE CinemaMovie.CinemaID = " + cinemaID->ToString();
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
SqlDataReader^ DataBaseQueries::getReaderReviewCatalog(Int32^ cinemaID, Int32^ movieID)
{
	String^ query = "SELECT UserInformation.UserLogin, Review.CommentDateTime, Cinema.CinemaName, Movie.MovieName, AssessmentTranscript.TranscriptPicture, Review.Comment FROM " +
		"(((((Review JOIN UserInformation ON Review.UserID = UserInformation.UserID) " +
		"JOIN Assessment ON Review.AssessmentID = Assessment.AssessmentID) " +
		"JOIN Cinema ON Assessment.CinemaID = Cinema.CinemaID) " +
		"JOIN Movie ON Assessment.MovieID = Movie.MovieID) " +
		"JOIN AssessmentTranscript ON Assessment.TranscriptID = AssessmentTranscript.PictureID) WHERE Assessment.CinemaID = " + cinemaID + " AND Assessment.MovieID = " + movieID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
SqlDataReader^ DataBaseQueries::getReaderCinemaNameBox()
{
	String^ query = "SELECT CinemaName FROM Cinema";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
SqlDataReader^ DataBaseQueries::getReaderMovieNameBox(Int32^ cinemaID)
{
	String^ query = "SELECT MovieName FROM (Movie JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE CinemaMovie.CinemaID = " + cinemaID->ToString();
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	return reader;
}
void DataBaseQueries::addNewReviewToDB(Int32^ CinemaID, Int32^ MovieID, String^ TranscriptID, String^ UserLogin, String^ Comment)
{
	String^ query = "INSERT INTO Assessment (CinemaID, MovieID, TranscriptID) VALUES (" + CinemaID + ", " + MovieID + ", " + TranscriptID + ")";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	if (SQL_command->ExecuteNonQuery())
	{
		//�������� UserID.
		Int32^ UserID{};
		query = "SELECT UserID FROM UserInformation WHERE UserLogin = '" + UserLogin + "'";
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (reader->Read())
			UserID = reader->GetInt32(0);
		reader->Close();
		//��������� AssessmentID.
		Int32^ AssessmentID{};
		query = "SELECT TOP(1) AssessmentID FROM Assessment ORDER BY AssessmentID DESC";
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (reader->Read())
			AssessmentID = reader->GetInt32(0);
		reader->Close();
		//������� ������.
		query = "INSERT INTO Review (UserID, Comment, AssessmentID) VALUES (" + UserID + ", '" + Comment + "', " + AssessmentID + ")";
		SQL_command = gcnew SqlCommand(query, conn);
		if (SQL_command->ExecuteNonQuery())
		{
			MessageBox::Show("��� ����������� ������� ��������!", "�������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("��� ����������� �� ��� ��������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	else
	{
		MessageBox::Show("��� ����������� �� ��� ��������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
//��������������� �������.
Int32^ DataBaseQueries::getCinemaIDbyCinemaName(String^ cinemaName)
{
	Int32^ cinemaID{};
	String^ query = "SELECT CinemaID FROM Cinema WHERE CinemaName = '" + cinemaName + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	while (reader->Read())
		cinemaID = reader->GetInt32(0);
	reader->Close();
	return cinemaID;
}
Int32^ DataBaseQueries::getMovieIDbyMovieName(Int32^ cinemaID, String^ movieName)
{
	Int32^ movieID{};
	String^ query = "SELECT Movie.MovieID FROM (Movie JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE CinemaMovie.CinemaID = "  + cinemaID->ToString() + " AND Movie.MovieName = '" + movieName + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	while (reader->Read())
		movieID = reader->GetInt32(0);
	reader->Close();
	return movieID;
}
//������� �� ������.
String^ DataBaseQueries::getMainAdminLogin()
{
	String^ mainUserLogin{};
	String^ query = "SELECT UserLogin FROM UserInformation WHERE UserID = 1";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
	this->reader = SQL_command->ExecuteReader();
	while (reader->Read())
		mainUserLogin = reader->GetString(0);
	reader->Close();
	return mainUserLogin;
}
//�����.
void DataBaseQueries::userInformationShow(DataGridView^ data)
{
	this->ConnectToDB();
	
	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM UserInformation";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);
	
	data->DataSource = table;
}
void DataBaseQueries::userInfromationShowForNotMainAdmin(DataGridView^ data)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM UserInformation WHERE UserRole = 'User'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	data->DataSource = table;
}
void DataBaseQueries::cinemaShow(DataGridView^ data)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Cinema";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	data->DataSource = table;
}
void DataBaseQueries::movieShow(DataGridView^ data)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT Movie.MovieID, MovieName, CinemaName, Release, Genre, AgeLimit, Duration, MovieFormat FROM ((Movie LEFT JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) LEFT JOIN Cinema ON Cinema.CinemaID = CinemaMovie.CinemaID)";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	data->DataSource = table;
}
void DataBaseQueries::commentShow(DataGridView^ data)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT ReviewID, CommentDateTime, UserLogin, CinemaName, MovieName, PictureID, Comment FROM ((((Review JOIN Assessment ON Review.AssessmentID = Assessment.AssessmentID)" + 
		" JOIN UserInformation ON Review.UserID = UserInformation.UserID) JOIN Cinema ON Assessment.CinemaID = Cinema.CinemaID) JOIN Movie ON Assessment.MovieID = Movie.MovieID) " + 
		"JOIN AssessmentTranscript ON Assessment.TranscriptID = AssessmentTranscript.PictureID";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	data->DataSource = table;
}
//��������� ������ ��.
Boolean DataBaseQueries::addNewUserAccountFromAdmin(String^ userLogin, String^ userPswd, String^ userRole, String^ adminLogin)
{
	this->ConnectToDB();
	this->openConnection();
	String^ mainAdminLogin{ this->getMainAdminLogin() };
	if (adminLogin->ToLower() != mainAdminLogin->ToLower() && userRole != "User")
	{
		MessageBox::Show("�������� ���������� �� ������� ����� ������ ������� �����!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		this->closeConnection();
		return false;
	}
	else
	{
		String^ query = "INSERT INTO UserInformation (UserLogin, UserPswd, UserRole) VALUES ('" + userLogin + "', '" + userPswd + "', '" + userRole + "')";
		SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

		if (SQL_command->ExecuteNonQuery())
		{
			MessageBox::Show("�� ������� ���������������� �������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->closeConnection();
			return true;
		}
		else
		{
			MessageBox::Show("������� �� ������. ������ �� ������� �������!");
			this->closeConnection();
			return false;
		}
	}
}
Boolean DataBaseQueries::updateUserAccountFromAdmin(String^ userID, String^ userLogin, String^ userPswd, String^ userRole, String^ adminLogin)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM UserInformation WHERE UserID = " + userID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		String^ changedUserLogin, ^ changedUserRole{}, ^ mainAdminLogin{ this->getMainAdminLogin() };
		query = "SELECT UserLogin, UserRole FROM UserInformation WHERE UserID = " + userID;
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (this->reader->Read())
		{
			changedUserLogin = this->reader->GetString(0);
			changedUserRole = this->reader->GetString(1);
		}
		this->reader->Close();
		if (adminLogin->ToLower() == mainAdminLogin->ToLower() && adminLogin->ToLower() == changedUserLogin->ToLower() && changedUserRole != "Admin")
		{
			MessageBox::Show("�� �� ������ �������� ���� ���� �� ������������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->closeConnection();
			return false;
		}
		else if (adminLogin->ToLower() != mainAdminLogin->ToLower() && (changedUserRole != "User" || userRole != "User"))
		{
			MessageBox::Show("�������� ���������� �� ������� ����� ������ ������� �����!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->closeConnection();
			return false;
		}
		else
		{
			if (userLogin == changedUserLogin)
				query = "UPDATE UserInformation SET UserPswd = '" + userPswd + "', UserRole = '" + userRole + "' WHERE UserID = '" + userID + "'";
			else
				query = "UPDATE UserInformation SET UserLogin = '" + userLogin + "', UserPswd = '" + userPswd + "', UserRole = '" + userRole + "' WHERE UserID = " + userID;
			SQL_command = gcnew SqlCommand(query, conn);
			if (SQL_command->ExecuteNonQuery())
			{
				this->closeConnection();
				return true;
			}	
			else
			{
				MessageBox::Show("������ �� ��������� ������������ �� ���� ��������. ������ �� ������� �������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
		}
	}
}
Boolean DataBaseQueries::deleteUserAccountFromAdmin(String^ userID, String^ adminLogin)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM UserInformation WHERE UserID = " + userID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		String^ changedUserLogin, ^ changedUserRole{}, ^ mainAdminLogin{ this->getMainAdminLogin() };
		query = "SELECT UserLogin, UserRole FROM UserInformation WHERE UserID = " + userID;
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (this->reader->Read())
		{
			changedUserLogin = this->reader->GetString(0);
			changedUserRole = this->reader->GetString(1);
		}
		this->reader->Close();
		if (changedUserLogin->ToLower() == adminLogin->ToLower())
		{
			MessageBox::Show("�� �� ������ ������� ����!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->closeConnection();
			return false;
		}
		else
		{
			Int32^ assessmentID{};
			query = "SELECT AssessmentID FROM Review WHERE UserID = " + userID;
			SQL_command = gcnew SqlCommand(query, conn);
			this->reader = SQL_command->ExecuteReader();
			while (this->reader->Read())
				assessmentID = this->reader->GetInt32(0);
			this->reader->Close();
			if (adminLogin->ToLower() != mainAdminLogin->ToLower() && changedUserRole != "User")
			{
				MessageBox::Show("� ��� ��� ���� �� �������� �������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
			else
			{
				DialogResult result = MessageBox::Show("����������? ����� ������� ��� ������, ��������� � ������ �������������, ��� � ��� ������������!", "��������������!", MessageBoxButtons::YesNo, MessageBoxIcon::Information);
				if (result == DialogResult::Yes)
				{
					if (assessmentID == nullptr)
					{
						query = "DELETE FROM UserInformation WHERE UserID = " + userID;
						SQL_command = gcnew SqlCommand(query, conn);
						SQL_command->ExecuteNonQuery();
						this->closeConnection();
						return true;
					}
					else
					{
						query = "DELETE FROM Review WHERE UserID = " + userID;
						SQL_command = gcnew SqlCommand(query, conn);
						SQL_command->ExecuteNonQuery();
						query = "DELETE FROM Assessment WHERE AssessmentID = " + assessmentID->ToString();
						SQL_command = gcnew SqlCommand(query, conn);
						SQL_command->ExecuteNonQuery();
						query = "DELETE FROM UserInformation WHERE UserID = " + userID;
						SQL_command = gcnew SqlCommand(query, conn);
						SQL_command->ExecuteNonQuery();
						this->closeConnection();
						return true;
					}
				}
				else
				{
					this->closeConnection();
					return false;
				}
			}
		}
	}
}
Boolean DataBaseQueries::deleteCinemaFromAdmin(String^ cinemaID)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Cinema WHERE cinemaID = " + cinemaID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("���������� � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		DialogResult result = MessageBox::Show("����������? ����� ������� ��� ������ � ������, ��������� � ������ �����������, ��� � ��� ���������!", "��������������!", MessageBoxButtons::YesNo, MessageBoxIcon::Information);
		if (result == DialogResult::Yes)
		{
			this->openConnection();
			//�������� ������ ������� � ������ �����������.
			query = "DELETE FROM CinemaMovie WHERE CinemaID = " + cinemaID;
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			//�������� �������, ��������� � ������ �����������.
			query = "DELETE FROM Review WHERE AssessmentID IN (SELECT AssessmentID FROM Assessment WHERE CinemaID = " + cinemaID + ")";
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			//�������� ������, ��������� � ������ �����������.
			query = "DELETE FROM Assessment WHERE CinemaID = " + cinemaID;
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			//�������� ������� ����������.
			query = "DELETE FROM Cinema WHERE CinemaID = " + cinemaID;
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			//�������� �������, ������� ������ �� ������� �� � ����� �����������.
			query = "DELETE FROM Movie WHERE Movie.MovieID IN (SELECT Movie.MovieID FROM (Movie LEFT JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE CinemaMovie.CinemaID IS NULL)";
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			this->closeConnection();
			return true;
		}
		else
			return false;
	}
}
Boolean DataBaseQueries::addNewCinemaFromAdmin(String^ CinemaPicturePath, String^ CinemaName, String^ City, String^ Street, String^ HouseNumber, String^ HouseLetter, String^ HouseDescr, String^ OpeningTime, String^ ClosingTime, String^ ContactInf)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Cinema WHERE CinemaName = '" + CinemaName + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count != 0)
	{
		MessageBox::Show("��������� � ����� ��������� ��� ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		Boolean isNumericHouseNumber{ true };
		for (int i{}; i < HouseNumber->Length; i++)
			if ((HouseNumber[i] < '0' || HouseNumber[i] > '9') && HouseNumber[i] != '/')
			{
				isNumericHouseNumber = false;
				break;
			}
		if (!isNumericHouseNumber)
		{
			MessageBox::Show("����� ���� ������ �������� ������ �� ���� ��� ������� /!", "������ ������ ����!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return false;
		}
		else
		{
			if (HouseLetter == "")
				HouseLetter = L"";
			else
			{
				if (!(HouseLetter[0] >= 'a' && HouseLetter[0] <= 'z' || HouseLetter[0] >= 'A' && HouseLetter[0] <= 'Z' ))
				{
					MessageBox::Show("������ ���� ������ ������������ �� ���� ����� ���������� ��������!", "������ ������ ����!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return false;
				}
			}
			if (HouseDescr == "")
				HouseDescr = L"-";
			if (ContactInf == "")
				ContactInf = L"no contact information";
			this->openConnection();
			try
			{
				query = "INSERT INTO Cinema VALUES (NULL, '" + CinemaName + "', '" + City + "', '" + Street + "', '" + HouseNumber + "', '" + HouseLetter + "', '" + HouseDescr + "', '" + OpeningTime + "', '" + ClosingTime
					+ "', '" + ContactInf + "')";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
			}
			catch (System::Data::SqlClient::SqlException^ exception)
			{
				MessageBox::Show("����� �������� �/��� �������� ������� �����������. ��������� ��� �������� ��� ������� ���������� �����!", "������ ������� �������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
			try
			{
				query = "UPDATE Cinema SET CinemaPicture = (SELECT * FROM OPENROWSET(BULK N'" + CinemaPicturePath + "', SINGLE_BLOB) AS IMAGE) WHERE CinemaName = '" + CinemaName + "'";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				this->closeConnection();
				return true;
			}
			catch (System::Data::SqlClient::SqlException^ exception)
			{
				MessageBox::Show("��������� ���� � ����� � �� �������� ������� ������ ����� (.jpg, .png)!", "������ �������� ����� � ������������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return true;
			}
		}
	}
}
Boolean DataBaseQueries::updateCinemaFromAdmin(String^ cinemaID, String^ CinemaPicturePath, String^ CinemaName, String^ City, String^ Street, String^ HouseNumber, String^ HouseLetter, String^ HouseDescr, String^ OpeningTime, String^ ClosingTime, String^ ContactInf)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Cinema WHERE CinemaID = '" + cinemaID + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ �������� ���������, ������� ��� �� ��� ��������. ��������� ID ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		Boolean isNumericHouseNumber{ true };
		for (int i{}; i < HouseNumber->Length; i++)
			if ((HouseNumber[i] < '0' || HouseNumber[i] > '9') && HouseNumber[i] != '/')
			{
				isNumericHouseNumber = false;
				break;
			}
		if (isNumericHouseNumber)
		{
			if (HouseLetter == "")
				HouseLetter = L"";
			else
			{
				if (!(HouseLetter[0] >= 'a' && HouseLetter[0] <= 'z' || HouseLetter[0] >= 'A' && HouseLetter[0] <= 'Z'))
				{
					MessageBox::Show("������ ���� ������ ������������ �� ���� ����� ���������� ��������!", "������ ������ ����!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return false;
				}
			}
			if (HouseDescr == "")
				HouseDescr = L"-";
			if (ContactInf == "")
				ContactInf = L"no contact information";
			this->openConnection();
			String^ changedCinemaName{};
			query = "SELECT CinemaName FROM Cinema WHERE CinemaID = " + cinemaID;
			SQL_command = gcnew SqlCommand(query, conn);
			this->reader = SQL_command->ExecuteReader();
			while (this->reader->Read())
				changedCinemaName = this->reader->GetString(0);
			this->reader->Close();
			if (CinemaName->ToLower() == changedCinemaName->ToLower())
				query = "UPDATE Cinema SET CinemaPicture = NULL, City = '" + City + "', Street = '" + Street + "', HouseNumber = '" + HouseNumber +
				"', HouseLetter = '" + HouseLetter + "', HouseDescr = '" + HouseDescr + "', OpeningTime = '" + OpeningTime + "', ClosingTime = '" + ClosingTime + "', ContactInformation = '" + ContactInf + "' WHERE CinemaID = " + cinemaID;
			else
			{
				DataTable^ table = gcnew DataTable();
				String^ query = "SELECT CinemaID FROM Cinema WHERE CinemaName = '" + CinemaName + "'";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

				this->adapter = gcnew SqlDataAdapter();
				adapter->SelectCommand = SQL_command;
				adapter->Fill(table);

				if (table->Rows->Count == 0)
				{
					query = "UPDATE Cinema SET CinemaPicture = NULL, CinemaName = '" + CinemaName + "', City = '" + City + "', Street = '" + Street + "', HouseNumber = '" + HouseNumber +
						"', HouseLetter = '" + HouseLetter + "', HouseDescr = '" + HouseDescr + "', OpeningTime = '" + OpeningTime + "', ClosingTime = '" + ClosingTime + "', ContactInformation = '" + ContactInf + "' WHERE CinemaID = " + cinemaID;
				}
				else
				{
					MessageBox::Show("��������� � ����� ��������� ��� ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					this->closeConnection();
					return false;
				}
			}
			try
			{
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
			}
			catch (System::Data::SqlClient::SqlException ^ exception)
			{
				MessageBox::Show("����� �������� �/��� �������� ������� �����������. ��������� ��� �������� ��� ������� ���������� �����!", "������ ������� �������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
			try
			{
				query = "UPDATE Cinema SET CinemaPicture = (SELECT * FROM OPENROWSET(BULK N'" + CinemaPicturePath + "', SINGLE_BLOB) AS IMAGE) WHERE CinemaID = '" + cinemaID + "'";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				this->closeConnection();
				return true;
			}
			catch (System::Data::SqlClient::SqlException^ exception)
			{
				MessageBox::Show("��������� ���� � ����� � �� �������� ������� ������ ����� (.jpg, .png)!", "������ �������� ����� � ������������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return true;
			}
		}
		else
		{
			MessageBox::Show("����� ���� ������ �������� ������ �� ���� ��� ������� /!", "������ ������ ����!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return false;
		}
	}
}
Boolean DataBaseQueries::deleteMovieFromAdmin(String^ movieID, String^ cinemaName)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Movie WHERE MovieID = " + movieID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		//������ �������� ������.
		if (cinemaName == "None")
		{
			DialogResult result = MessageBox::Show("����������? ��������� ����� ����� ������ �� ����� �������� ��� ���� �����������!", "��������������!", MessageBoxButtons::YesNo, MessageBoxIcon::Information);
			if (result == DialogResult::Yes)
			{
				//�������� ������ ����������� � ������ �������.
				query = "DELETE FROM CinemaMovie WHERE MovieID = " + movieID;
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				//�������� �������, ��������� � ������ �������.
				query = "DELETE FROM Review WHERE AssessmentID IN (SELECT AssessmentID FROM Assessment WHERE MovieID = " + movieID + ")";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				//�������� ������, ��������� � ������ �������.
				query = "DELETE FROM Assessment WHERE MovieID = " + movieID;
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				//�������� ������� ������.
				query = "DELETE FROM Movie WHERE MovieID = " + movieID;
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
			}
			else
			{
				this->closeConnection();
				return false;
			}
		}																   
		//�������� ������ �� ���������� ����������.
		else
		{
			DialogResult result = MessageBox::Show("����������? ��������� ����� ����� ������ �� ����� �������� �� ������� ����������. ���� ����� ��� ������ � ������ ����������, �� �� ����� ��������� ������!", "��������������!", MessageBoxButtons::YesNo, MessageBoxIcon::Information);
			if (result == DialogResult::Yes)
			{
				//��������� ID ���������� �� ��� ��������.
				Int32^ cinemaID{};
				query = "SELECT CinemaID FROM Cinema WHERE CinemaName = '" + cinemaName + "'";
				SQL_command = gcnew SqlCommand(query, conn);
				this->reader = SQL_command->ExecuteReader();
				while (this->reader->Read())
					cinemaID = reader->GetInt32(0);
				this->reader->Close();
				//�������� ������� ��������� ������ � ������ ����������.
				table = gcnew DataTable();
				query = "SELECT * FROM CinemaMovie WHERE MovieID = " + movieID + " AND CinemaID = " + cinemaID;
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

				this->adapter = gcnew SqlDataAdapter();
				adapter->SelectCommand = SQL_command;
				adapter->Fill(table);

				if (table->Rows->Count == 0)
				{
					MessageBox::Show("������ ����� ����������� � ��������� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					this->closeConnection();
					return false;
				}
				else
				{
					//�������� ����� ���������� � ������ �������.
					query = "DELETE FROM CinemaMovie WHERE CinemaID = " + cinemaID->ToString() + " AND MovieID = " + movieID;
					SQL_command = gcnew SqlCommand(query, conn);
					SQL_command->ExecuteNonQuery();
					//�������� �������, ��������� � ������ ������� � ��������� ����������.
					query = "DELETE FROM Review WHERE AssessmentID IN (SELECT AssessmentID FROM Assessment WHERE CinemaID = " + cinemaID->ToString() + "AND MovieID = " + movieID + ")";
					SQL_command = gcnew SqlCommand(query, conn);
					SQL_command->ExecuteNonQuery();
					//�������� ������, ��������� � ������ ������� � ��������� ����������.
					query = "DELETE FROM Assessment WHERE CinemaID = " + cinemaID->ToString() + " AND MovieID = " + movieID;
					SQL_command = gcnew SqlCommand(query, conn);
					SQL_command->ExecuteNonQuery();
					//�������� ������� ������, ���� �� ������ �� ���� �� � ����� ����������.
					query = "DELETE FROM Movie WHERE Movie.MovieID = (SELECT Movie.MovieID FROM (Movie LEFT JOIN CinemaMovie ON Movie.MovieID = CinemaMovie.MovieID) WHERE Movie.MovieID = " + movieID + " AND CinemaMovie.CinemaID IS NULL)";
					SQL_command = gcnew SqlCommand(query, conn);
					SQL_command->ExecuteNonQuery();
				}
			}
			else
			{
				this->closeConnection();
				return false;
			}
		}
		this->closeConnection();
		return true;
	}
}
Boolean DataBaseQueries::addMovieFromAdmin(String^ movieName, String^ release, String^ genre, String^ ageLimit, String^ duration, String^ movieFormat, String^ cinemaName)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Movie WHERE MovieName = '" + movieName + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count != 0)
	{
		if (cinemaName == "None")
		{
			MessageBox::Show("�������� ��������������� ������ ������ ���� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return false;
		}
		//���������� ������ � ���������.
		else
		{
			//��������� ID ������������ ������ � ���������������� ����������.
			this->openConnection();
			Int32^ addedMovieID{}, ^ changedCinemaID{};
			query = "SELECT MovieID FROM Movie WHERE MovieName = '" + movieName + "'";
			SQL_command = gcnew SqlCommand(query, conn);
			this->reader = SQL_command->ExecuteReader();
			while (this->reader->Read())
				addedMovieID = reader->GetInt32(0);
			this->reader->Close();
			query = "SELECT CinemaID FROM Cinema WHERE CinemaName = '" + cinemaName + "'";
			SQL_command = gcnew SqlCommand(query, conn);
			this->reader = SQL_command->ExecuteReader();
			while (this->reader->Read())
				changedCinemaID = reader->GetInt32(0);
			this->reader->Close();
			//�������� ������� ����������� �����.
			table = gcnew DataTable();
			query = "SELECT * FROM CinemaMovie WHERE CinemaID = " + changedCinemaID->ToString() + " AND MovieID = " + addedMovieID->ToString();
			SQL_command = gcnew SqlCommand(query, conn);
			this->adapter = gcnew SqlDataAdapter();
			adapter->SelectCommand = SQL_command;
			adapter->Fill(table);
			if (table->Rows->Count != 0)
			{
				MessageBox::Show("��������� ����� ��� ��� �������� � ��������� ���������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
			else
			{
				//���������� ����� ������ � �����������.
				query = "INSERT INTO CinemaMovie VALUES (" + changedCinemaID->ToString() + ", " + addedMovieID->ToString() + ")";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				this->closeConnection();
				return true;
			}
		}
	}
	else
	{
		//����������� ������ � �������.
		if (cinemaName == "None")
		{
			Boolean true_ageLimit{ true };
			if (String::IsNullOrEmpty(ageLimit) || String::IsNullOrWhiteSpace(ageLimit))
				ageLimit = L"0+";
			if (movieFormat == "")
				movieFormat = L"2D";
			this->openConnection();
			try
			{
				query = "INSERT INTO Movie VALUES ('" + movieName + "', '" + release + "', '" + genre + "', '" + ageLimit + (ageLimit == L"0+" ? "', '" : "+', '") + duration + "', '" + movieFormat + "')";
				SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->ExecuteNonQuery();
				this->closeConnection();
				return true;
			}
			catch (System::Data::SqlClient::SqlException^ exception)
			{
				this->closeConnection();
				MessageBox::Show("������������� ���� � ���� � ��������. ���������, ����� ���� ��������� ��� �������� � ������������ ����� � ��������, ��� ���� �������� � ����� ���� �����������!", "������ ����� � ��������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return false;
			}
		}
		else
		{
			MessageBox::Show("����� � ��������� ��������� ��� �� ��� ���������������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return false;
		}
	}
}
Boolean DataBaseQueries::updateMovieFromAdmin(String^ movieID, String^ movieName, String^ release, String^ genre, String^ ageLimit, String^ duration, String^ movieFormat, String^ cinemaName)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Movie WHERE MovieID = '" + movieID + "'";
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ �������� �����, ������� ��� �� ��� ��������. ��������� ID ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		if (String::IsNullOrEmpty(ageLimit) || String::IsNullOrWhiteSpace(ageLimit))
			ageLimit = L"0+";
		if (String::IsNullOrEmpty(movieFormat) || String::IsNullOrWhiteSpace(movieFormat))
			movieFormat = L"2D";
		this->openConnection();
		String^ changedMovieName{};
		query = "SELECT MovieName FROM Movie WHERE MovieID = " + movieID;
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (this->reader->Read())
			changedMovieName = this->reader->GetString(0);
		this->reader->Close();
		//��������� ���������� � ������.
		if (movieName->ToLower() == changedMovieName->ToLower())
			query = "UPDATE Movie SET Release = '" + release + "', Genre = '" + genre + "', AgeLimit = '" + ageLimit + (ageLimit == L"0+" ? "', Duration = '" : "+', Duration = '") + duration + "', MovieFormat = '" + movieFormat + "' WHERE MovieID = " + movieID;
		else
		{
			table = gcnew DataTable();
			query = "SELECT MovieID FROM Movie WHERE MovieName = '" + movieName + "'";
			SQL_command = gcnew SqlCommand(query, conn);

			this->adapter = gcnew SqlDataAdapter();
			adapter->SelectCommand = SQL_command;
			adapter->Fill(table);

			if (table->Rows->Count == 0)
				query = "UPDATE Movie SET MovieName = '" + movieName + "', Release = '" + release + "', Genre = '" + genre + "', AgeLimit = '" + ageLimit + (ageLimit == L"0+" ? "', Duration = '" : "+', Duration = '") + duration + "', MovieFormat = '" + movieFormat + "' WHERE MovieID = " + movieID;
			else
			{
				MessageBox::Show("����� � ����� ��������� ��� ����������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->closeConnection();
				return false;
			}
		}
		try
		{
			SQL_command = gcnew SqlCommand(query, conn);
			SQL_command->ExecuteNonQuery();
			return true;
		}
		catch (System::Data::SqlClient::SqlException^ exception)
		{
			MessageBox::Show("������������� ���� � ���� � ��������. ���������, ����� ���� ��������� ��� �������� � ������������ ����� � ��������, ��� ���� �������� � ����� ���� �����������!", "������ ����� � ��������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->closeConnection();
			return false;
		}
	}
}
Boolean DataBaseQueries::deleteReviewFromAdmin(String^ reviewID)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Review WHERE ReviewID = " + reviewID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		//ID ������ ���������� ������.
		Int32^ assessmentID{};
		query = "SELECT AssessmentID FROM Review WHERE ReviewID = " + reviewID;
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (this->reader->Read())
			assessmentID = reader->GetInt32(0);
		this->reader->Close();
		//�������� ������.
		query = "DELETE FROM Review WHERE ReviewID = " + reviewID;
		SQL_command = gcnew SqlCommand(query, conn);
		SQL_command->ExecuteNonQuery();
		//�������� ������.
		query = "DELETE FROM Assessment WHERE AssessmentID = " + assessmentID;
		SQL_command = gcnew SqlCommand(query, conn);
		SQL_command->ExecuteNonQuery();
		this->closeConnection();
		return true;
	}
}
Boolean DataBaseQueries::addReviewFromAdmin(String^ reviewID, TextBox^ comment)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Review WHERE ReviewID = " + reviewID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		//��������� ������ ������������.
		String^ commentText{};
		query = "SELECT comment FROM Review WHERE ReviewID = " + reviewID;
		SQL_command = gcnew SqlCommand(query, conn);
		this->reader = SQL_command->ExecuteReader();
		while (this->reader->Read())
			commentText = reader->GetString(0);
		this->reader->Close();
		comment->Text = commentText;
		this->closeConnection();
		return true;
	}
}
Boolean DataBaseQueries::updateReviewFromAdmin(String^ reviewID, String^ comment)
{
	this->ConnectToDB();

	DataTable^ table = gcnew DataTable();
	String^ query = "SELECT * FROM Review WHERE ReviewID = " + reviewID;
	SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);

	this->adapter = gcnew SqlDataAdapter();
	adapter->SelectCommand = SQL_command;
	adapter->Fill(table);

	if (table->Rows->Count == 0)
	{
		MessageBox::Show("������ � ���������� ������� �� ����������. ��������� ������������ ��������� ������!", "������!", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return false;
	}
	else
	{
		this->openConnection();
		query = "UPDATE Review SET comment = '" + comment + "' WHERE ReviewID = " + reviewID;
		SQL_command = gcnew SqlCommand(query, conn);
		SQL_command->ExecuteNonQuery();
		this->closeConnection();
		return true;
	}
}