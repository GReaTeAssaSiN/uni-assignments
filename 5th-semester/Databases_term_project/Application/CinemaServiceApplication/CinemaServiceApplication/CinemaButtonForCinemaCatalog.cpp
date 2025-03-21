#include "CinemaButtonForCinemaCatalog.h"

CinemaButtonForCinemaCatalog::CinemaButtonForCinemaCatalog(SqlDataReader^ reader, Panel^ main_cinema_btn_panel, String^ userName, Label^ update_inf_label)
{
	this->cinema_btn = (gcnew System::Windows::Forms::Button());
	this->cinema_img = (gcnew System::Windows::Forms::PictureBox());
	this->cinema_description = (gcnew System::Windows::Forms::TextBox());
	this->movie_catalog_panel = (gcnew System::Windows::Forms::Panel());
	this->search_textBox = (gcnew System::Windows::Forms::TextBox());
	this->search_btn = (gcnew System::Windows::Forms::Button());
	this->cinema = gcnew CinemaTableDBElement(reader);
	this->main_cinema_btn_panel = main_cinema_btn_panel;
	this->userName = userName;
	this->update_inf_label = update_inf_label;
	//
	// cinema_btn
	//
	this->cinema_btn->BackColor = System::Drawing::Color::WhiteSmoke;
	this->cinema_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->cinema_btn->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
	this->cinema_btn->FlatAppearance->BorderSize = 3;
	this->cinema_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
	this->cinema_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGray;
	this->cinema_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->cinema_btn->ForeColor = System::Drawing::Color::Black;
	this->cinema_btn->Image = Image->FromFile(L"D:\\КАИ\\Базы данных\\Курсовая\\Images\\cinema_icon.bmp");
	this->cinema_btn->ImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
	this->cinema_btn->MaximumSize = System::Drawing::Size(210, 90);
	this->cinema_btn->MinimumSize = System::Drawing::Size(210, 90);;
	this->cinema_btn->Size = System::Drawing::Size(210, 900);
	this->cinema_btn->Text = this->cinema->getCinemaName();
	this->cinema_btn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	this->cinema_btn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->cinema_btn->Click += gcnew System::EventHandler(this, &CinemaButtonForCinemaCatalog::cinema_btn_Click);
	//
	// cinema_img
	//
	this->cinema_img->Size = System::Drawing::Size(421, 300);
	this->cinema_img->MaximumSize = System::Drawing::Size(421, 300);
	this->cinema_img->MinimumSize = System::Drawing::Size(421, 300);
	this->cinema_img->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
	if (this->cinema->getImage())
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->cinema->getImage());
		this->cinema_img->Image = gcnew Bitmap(ms);
	}
	//
	// cinema_description
	//
	this->cinema_description->BackColor = System::Drawing::Color::FromArgb(185, 217, 235);
	this->cinema_description->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->cinema_description->Location = System::Drawing::Point(421, 50);
	this->cinema_description->ReadOnly = true;
	this->cinema_description->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	this->cinema_description->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->cinema_description->Size = System::Drawing::Size(439, 250);
	this->cinema_description->MaximumSize = System::Drawing::Size(439,250);
	this->cinema_description->MinimumSize = System::Drawing::Size(439, 250);
	this->cinema_description->Multiline = true;
	this->cinema_description->Text = L"КИНОТЕАТР \"" + this->cinema->getCinemaName() + "\"\r\n";
	this->cinema_description->AppendText("Город: " + this->cinema->getCity() + "\r\n");
	this->cinema_description->AppendText("Дом:   " + this->cinema->getHouseNumber());
	this->cinema_description->AppendText((this->cinema->getHouseLetter()->ToString() == " " ? "" : this->cinema->getHouseLetter()->ToString()) + "\r\n");
	this->cinema_description->AppendText("Уточнение дома: " + this->cinema->getHouseDesc() + "\r\n");
	this->cinema_description->AppendText("Время открытия: " + this->cinema->getOpeningTime()->ToString() + "\r\n");
	this->cinema_description->AppendText("Время закрытия: " + this->cinema->getClosingTime()->ToString() + "\r\n");
	this->cinema_description->AppendText("Контактная информация:\r\n" + this->cinema->getContactInformation());
	//
	// search_textBox
	//
	this->search_textBox->BackColor = System::Drawing::Color::GhostWhite;
	this->search_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->search_textBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(192, 192, 192);
	this->search_textBox->Location = System::Drawing::Point(421, 12);
	this->search_textBox->MaximumSize = System::Drawing::Size(389, 25);
	this->search_textBox->MaxLength = 30;
	this->search_textBox->MinimumSize = System::Drawing::Size(389, 25);
	this->search_textBox->Size = System::Drawing::Size(389, 25);
	this->search_textBox->Text = L"Поиск фильма в кинотеатре " + this->cinema->getCinemaName();
	this->search_textBox->Enter += gcnew System::EventHandler(this, &CinemaButtonForCinemaCatalog::search_textBox_Enter);
	this->search_textBox->Leave += gcnew System::EventHandler(this, &CinemaButtonForCinemaCatalog::search_textBox_Leave);
	//
	// search_btn
	// 
	this->search_btn->BackColor = System::Drawing::Color::SteelBlue;
	this->search_btn->BackgroundImage = Image->FromFile(L"D:\\КАИ\\Базы данных\\Курсовая\\Images\\search_icon.bmp");
	this->search_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	this->search_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->search_btn->FlatAppearance->BorderColor = System::Drawing::Color::Indigo;
	this->search_btn->FlatAppearance->BorderSize = 2;
	this->search_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::RoyalBlue;
	this->search_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
		static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
	this->search_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->search_btn->Location = System::Drawing::Point(810, 0);
	this->search_btn->MaximumSize = System::Drawing::Size(50, 50);
	this->search_btn->MinimumSize = System::Drawing::Size(50, 50);
	this->search_btn->Name = L"search_btn";
	this->search_btn->Size = System::Drawing::Size(50, 50);
	this->search_btn->TabIndex = 3;
	this->search_btn->UseVisualStyleBackColor = false;
	this->search_btn->Click += gcnew System::EventHandler(this, &CinemaButtonForCinemaCatalog::search_btn_Click);
	//
	// movie_catalog_panel
	//
	this->movie_catalog_panel->Size = System::Drawing::Size(860, 370);
	this->movie_catalog_panel->Location = System::Drawing::Point(0, 300);
	this->movie_catalog_panel->BackColor = System::Drawing::Color::FromArgb(140, 146, 172);
	this->movie_catalog_panel->AutoScroll = true;
}
Button^ CinemaButtonForCinemaCatalog::getCinemaBtn()
{
	return this->cinema_btn;
}
System::Void CinemaButtonForCinemaCatalog::cinema_btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->update_inf_label->Text = L"Выберите кинотеатр или фильм из предложенного списка";
	this->movie_catalog_panel->Controls->Clear();
	this->main_cinema_btn_panel->Controls->Clear();
	this->main_cinema_btn_panel->BackColor = System::Drawing::Color::FromArgb(185, 217, 235);
	this->movie_catalog_panel->SuspendLayout();
	this->main_cinema_btn_panel->SuspendLayout();
	this->main_cinema_btn_panel->Controls->Add(this->cinema_img);
	this->main_cinema_btn_panel->Controls->Add(this->search_textBox);
	this->main_cinema_btn_panel->Controls->Add(this->search_btn);
	this->main_cinema_btn_panel->Controls->Add(this->cinema_description);
	//Запрос каталога комментариев соответствующего фильма соответствующего кинотеатра.
	DataBaseQueries^ queryDB = gcnew DataBaseQueries();
	queryDB->ConnectToDB();
	queryDB->openConnection();
	SqlDataReader^ reader = queryDB->getReaderMovieCatalog(this->cinema->getCinemaID());
	Int32 ddx{ -421 }, ddy{};
	while (reader->Read())
	{
		MovieButtonForMovieCatalog^ movie_btn = gcnew MovieButtonForMovieCatalog(reader, this->main_cinema_btn_panel, cinema->getCinemaID(), this->userName, this->update_inf_label);
		if (ddx + 421 + 421 > 860)
		{
			ddx = 0;
			ddy += 123;
		}
		else
			ddx += 421;
		movie_btn->getMovieBtn()->Location = System::Drawing::Point(ddx, ddy);
		this->movie_catalog_panel->Controls->Add(movie_btn->getMovieBtn());
	}
	queryDB->closeConnection();
	this->main_cinema_btn_panel->Controls->Add(this->movie_catalog_panel);
	this->main_cinema_btn_panel->ResumeLayout();
	this->movie_catalog_panel->ResumeLayout();
}
System::Void CinemaButtonForCinemaCatalog::search_btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->movie_catalog_panel->Controls->Clear();
	this->movie_catalog_panel->SuspendLayout();
	//Запрос каталога комментариев соответствующего фильма соответствующего кинотеатра.
	DataBaseQueries^ queryDB = gcnew DataBaseQueries();
	queryDB->ConnectToDB();
	queryDB->openConnection();
	SqlDataReader^ reader{};
	if (this->search_textBox->Text != "" && this->search_textBox->Text != ("Поиск фильма в кинотеатре " + this->cinema->getCinemaName()))
		reader = queryDB->getReaderSearchedMovieCatalog(this->search_textBox->Text, this->cinema->getCinemaID());
	else
	{
		reader = queryDB->getReaderMovieCatalog(this->cinema->getCinemaID());
		this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(192, 192, 192);
		this->search_textBox->Text = L"Поиск фильма в кинотеатре " + this->cinema->getCinemaName();
	}
	Int32 ddx{ -421 }, ddy{};
	while (reader->Read())
	{
		MovieButtonForMovieCatalog^ movie_btn = gcnew MovieButtonForMovieCatalog(reader, this->main_cinema_btn_panel, cinema->getCinemaID(), this->userName, this->update_inf_label);
		if (ddx + 421 + 421 > 860)
		{
			ddx = 0;
			ddy += 123;
		}
		else
			ddx += 421;
		movie_btn->getMovieBtn()->Location = System::Drawing::Point(ddx, ddy);
		this->movie_catalog_panel->Controls->Add(movie_btn->getMovieBtn());
	}
	queryDB->closeConnection();
	this->movie_catalog_panel->ResumeLayout();
}
System::Void CinemaButtonForCinemaCatalog::search_textBox_Enter(System::Object^ sender, System::EventArgs^ e)
{
	if (this->search_textBox->Text == ("Поиск фильма в кинотеатре " + this->cinema->getCinemaName()))
	{
		this->search_textBox->Text = L"";
		this->search_textBox->ForeColor = System::Drawing::Color::Navy;
	}
}
System::Void CinemaButtonForCinemaCatalog::search_textBox_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (this->search_textBox->Text == "")
	{
		this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(192, 192, 192);
		this->search_textBox->Text = L"Поиск фильма в кинотеатре " + this->cinema->getCinemaName();
	}
}