#include "AddNewReviewToDB.h"

AddNewReviewToDB::AddNewReviewToDB(String^ userName)
{
	this->add_new_review_panel = (gcnew System::Windows::Forms::Panel());
	this->post_review_btn = (gcnew System::Windows::Forms::Button());
	this->userLogin_DateTime_label = (gcnew System::Windows::Forms::Label());
	this->cinema_label = (gcnew System::Windows::Forms::Label());
	this->movie_label = (gcnew System::Windows::Forms::Label());
	this->assmnt_label = (gcnew System::Windows::Forms::Label());
	this->cinema_comboBox = (gcnew System::Windows::Forms::ComboBox());
	this->movie_comboBox = (gcnew System::Windows::Forms::ComboBox());
	this->assmnt_comboBox = (gcnew System::Windows::Forms::ComboBox());
	this->comment_textBox = (gcnew System::Windows::Forms::TextBox());
	this->clear_btn = (gcnew System::Windows::Forms::Button());
	this->userName = userName;
	this->add_new_review_panel->SuspendLayout();
	//
	// post_review_btn
	//
	this->post_review_btn->BackColor = System::Drawing::Color::FromArgb(136, 132, 140);
	this->post_review_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->post_review_btn->Text = "POST A REVIEW";
	this->post_review_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
	this->post_review_btn->FlatAppearance->BorderSize = 2;
	this->post_review_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->post_review_btn->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Bold,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->post_review_btn->ForeColor = System::Drawing::Color::FromArgb(193, 202, 224);
	this->post_review_btn->Size = System::Drawing::Size(478, 50);
	this->post_review_btn->MaximumSize = System::Drawing::Size(478, 50);
	this->post_review_btn->MinimumSize = System::Drawing::Size(478, 50);
	this->post_review_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AddNewReviewToDB::post_review_btn_MouseClick);
	//
	// userLogin_DateTime_label
	//
	this->userLogin_DateTime_label->BackColor = System::Drawing::Color::FromArgb(122, 106, 138);
	this->userLogin_DateTime_label->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 20.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->userLogin_DateTime_label->Location = System::Drawing::Point(0, 50);
	this->userLogin_DateTime_label->Size = System::Drawing::Size(550, 50);
	this->userLogin_DateTime_label->MaximumSize = System::Drawing::Size(550, 50);
	this->userLogin_DateTime_label->MinimumSize = System::Drawing::Size(550, 50);
	this->userLogin_DateTime_label->Text = L"UserLogin: " + userName;
	this->userLogin_DateTime_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// cinema_label
	//
	this->cinema_label->BackColor = System::Drawing::Color::Turquoise;
	this->cinema_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->cinema_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->cinema_label->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->cinema_label->Location = System::Drawing::Point(0, 100);
	this->cinema_label->Size = System::Drawing::Size(275, 50);
	this->cinema_label->MaximumSize = System::Drawing::Size(275, 50);
	this->cinema_label->MinimumSize = System::Drawing::Size(275, 50);
	this->cinema_label->Text = L"CINEMA:";
	this->cinema_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// movie_label
	//
	this->movie_label->BackColor = System::Drawing::Color::Teal;
	this->movie_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->movie_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->movie_label->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Bold));
	this->movie_label->Location = System::Drawing::Point(0, 150);
	this->movie_label->Size = System::Drawing::Size(275, 50);
	this->movie_label->MaximumSize = System::Drawing::Size(275, 50);
	this->movie_label->MinimumSize = System::Drawing::Size(275, 50);
	this->movie_label->Text = L"MOVIE:";
	this->movie_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// assmnt_label
	//
	this->assmnt_label->BackColor = System::Drawing::Color::SteelBlue;
	this->assmnt_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->assmnt_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->assmnt_label->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Bold));
	this->assmnt_label->Location = System::Drawing::Point(0, 200);
	this->assmnt_label->Size = System::Drawing::Size(275, 50);
	this->assmnt_label->MaximumSize = System::Drawing::Size(275, 50);
	this->assmnt_label->MinimumSize = System::Drawing::Size(275, 50);
	this->assmnt_label->Text = L"ASSESSMENT:";
	this->assmnt_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// cinema_comboBox
	//
	this->cinema_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->cinema_comboBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->cinema_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	this->cinema_comboBox->FormattingEnabled = true;
	this->cinema_comboBox->ItemHeight = 31;
	this->cinema_comboBox->Location = System::Drawing::Point(275, 108);
	this->cinema_comboBox->Size = System::Drawing::Size(275, 33);
	this->cinema_comboBox->MaximumSize = System::Drawing::Size(275, 33);
	this->cinema_comboBox->MinimumSize = System::Drawing::Size(275, 33);
	this->cinema_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->cinema_comboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	DataBaseQueries^ queryDB = gcnew DataBaseQueries();
	queryDB->ConnectToDB();
	queryDB->openConnection();
	SqlDataReader^ reader = queryDB->getReaderCinemaNameBox();
	while (reader->Read())
		this->cinema_comboBox->Items->Add(reader->GetString(0));
	queryDB->closeConnection();
	this->cinema_comboBox->DropDown += gcnew System::EventHandler(this, &AddNewReviewToDB::cinema_comboBox_DropDown);
	this->cinema_comboBox->DropDownClosed += gcnew System::EventHandler(this, &AddNewReviewToDB::cinema_comboBox_DropDownClosed);
	this->cinema_comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &AddNewReviewToDB::cinema_comboBox_SelectedIndexChanged);
	//
	// movie_comboBox
	//
	this->movie_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->movie_comboBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->movie_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	this->movie_comboBox->FormattingEnabled = true;
	this->movie_comboBox->ItemHeight = 31;
	this->movie_comboBox->Location = System::Drawing::Point(275, 158);
	this->movie_comboBox->Size = System::Drawing::Size(275, 33);
	this->movie_comboBox->MaximumSize = System::Drawing::Size(275, 33);
	this->movie_comboBox->MinimumSize = System::Drawing::Size(275, 33);
	this->movie_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->movie_comboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->movie_comboBox->Items->Add(L"Выберите кинотеатр");
	this->movie_comboBox->SelectedIndex = 0;
	this->movie_comboBox->DropDown += gcnew System::EventHandler(this, &AddNewReviewToDB::movie_comboBox_DropDown);
	this->movie_comboBox->DropDownClosed += gcnew System::EventHandler(this, &AddNewReviewToDB::movie_comboBox_DropDownClosed);
	//
	// assmnt_comboBox
	//
	this->assmnt_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->assmnt_comboBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->assmnt_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	this->assmnt_comboBox->FormattingEnabled = true;
	this->assmnt_comboBox->ItemHeight = 31;
	this->assmnt_comboBox->Location = System::Drawing::Point(275, 208);
	this->assmnt_comboBox->Size = System::Drawing::Size(275, 33);
	this->assmnt_comboBox->MaximumSize = System::Drawing::Size(275, 33);
	this->assmnt_comboBox->MinimumSize = System::Drawing::Size(275, 33);
	this->assmnt_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->assmnt_comboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	for (int i{ 1 }; i <= 5; i++)
		this->assmnt_comboBox->Items->Add(i);
	this->assmnt_comboBox->DropDown += gcnew System::EventHandler(this, &AddNewReviewToDB::assmnt_comboBox_DropDown);
	this->assmnt_comboBox->DropDownClosed += gcnew System::EventHandler(this, &AddNewReviewToDB::assmnt_comboBox_DropDownClosed);
	// 
	// comment_textBox
	//
	this->comment_textBox->BackColor = System::Drawing::Color::White;
	this->comment_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->comment_textBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->comment_textBox->ForeColor = System::Drawing::Color::Black;
	this->comment_textBox->Location = System::Drawing::Point(0, 250);
	this->comment_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	this->comment_textBox->WordWrap = true;
	this->comment_textBox->Multiline = true;
	this->comment_textBox->Size = System::Drawing::Size(550, 410);
	this->comment_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	//
	// clear_btn
	// 
	this->clear_btn->BackColor = System::Drawing::Color::DodgerBlue;
	this->clear_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->clear_btn->FlatAppearance->BorderColor = System::Drawing::Color::Navy;
	this->clear_btn->FlatAppearance->BorderSize = 2;
	this->clear_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DodgerBlue;
	this->clear_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
		static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
	this->clear_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->clear_btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Bold));
	this->clear_btn->ForeColor = System::Drawing::Color::White;
	this->clear_btn->Location = System::Drawing::Point(479, 0);
	this->clear_btn->MaximumSize = System::Drawing::Size(69, 50);
	this->clear_btn->MinimumSize = System::Drawing::Size(69, 50);
	this->clear_btn->Size = System::Drawing::Size(69, 50);
	this->clear_btn->Text = L"CLEAR";
	this->clear_btn->UseVisualStyleBackColor = false;
	this->clear_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AddNewReviewToDB::clear_btn_MouseClick);
	//
	// add_new_review_panel
	//
	this->add_new_review_panel->BackColor = System::Drawing::Color::FromArgb(140, 160, 172);
	this->add_new_review_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->add_new_review_panel->Controls->Add(this->post_review_btn);
	this->add_new_review_panel->Controls->Add(this->userLogin_DateTime_label);
	this->add_new_review_panel->Controls->Add(this->cinema_label);
	this->add_new_review_panel->Controls->Add(this->movie_label);
	this->add_new_review_panel->Controls->Add(this->assmnt_label);
	this->add_new_review_panel->Controls->Add(this->cinema_comboBox);
	this->add_new_review_panel->Controls->Add(this->movie_comboBox);
	this->add_new_review_panel->Controls->Add(this->assmnt_comboBox);
	this->add_new_review_panel->Controls->Add(this->comment_textBox);
	this->add_new_review_panel->Controls->Add(this->clear_btn);
	this->add_new_review_panel->Location = System::Drawing::Point(0, 0);
	this->add_new_review_panel->Size = System::Drawing::Size(550, 690);
	this->add_new_review_panel->MaximumSize = System::Drawing::Size(550, 690);
	this->add_new_review_panel->MinimumSize = System::Drawing::Size(550, 690);
	this->add_new_review_panel->ResumeLayout();
}
Panel^ AddNewReviewToDB::getAddNewReviewPanel()
{
	return this->add_new_review_panel;
}
System::Void AddNewReviewToDB::clear_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->cinema_comboBox->SelectedIndex = -1;
	this->movie_comboBox->Items->Clear();
	this->movie_comboBox->Items->Add(L"Выберите кинотеатр");
	this->movie_comboBox->SelectedIndex = 0;
	this->assmnt_comboBox->SelectedIndex = -1;
	this->comment_textBox->Text = "";
	//Окрас.
	this->cinema_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->cinema_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	this->movie_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->movie_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	this->assmnt_comboBox->BackColor = System::Drawing::Color::LightPink;
	this->assmnt_comboBox->ForeColor = System::Drawing::Color::DarkRed;
}
System::Void AddNewReviewToDB::cinema_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e)
{
	this->cinema_comboBox->BackColor = System::Drawing::Color::AliceBlue;
	this->cinema_comboBox->ForeColor = System::Drawing::Color::RoyalBlue;
}
System::Void AddNewReviewToDB::cinema_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e)
{
	if (this->cinema_comboBox->SelectedIndex == -1)
	{
		this->cinema_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->cinema_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	}
}
System::Void AddNewReviewToDB::cinema_comboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (this->cinema_comboBox->SelectedIndex != -1)
	{
		this->cinema_comboBox->BackColor = System::Drawing::Color::AliceBlue;
		this->cinema_comboBox->ForeColor = System::Drawing::Color::RoyalBlue;
		this->movie_comboBox->Items->Clear();
		DataBaseQueries^ queryDB = gcnew DataBaseQueries();
		queryDB->ConnectToDB();
		queryDB->openConnection();
		Int32^ cinemaID = queryDB->getCinemaIDbyCinemaName(this->cinema_comboBox->SelectedItem->ToString());
		SqlDataReader^ reader = queryDB->getReaderMovieNameBox(cinemaID);
		while (reader->Read())
			this->movie_comboBox->Items->Add(reader->GetString(0));
		queryDB->closeConnection();
	}
}
System::Void AddNewReviewToDB::movie_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e)
{
	this->movie_comboBox->BackColor = System::Drawing::Color::AliceBlue;
	this->movie_comboBox->ForeColor = System::Drawing::Color::RoyalBlue;
}
System::Void AddNewReviewToDB::movie_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e)
{
	if ((this->movie_comboBox->SelectedIndex == 0 && this->movie_comboBox->SelectedItem == "Выберите кинотеатр") || (this->movie_comboBox->SelectedIndex == -1 && this->movie_comboBox->SelectedItem != "Выберите кинотеатр"))
	{
		this->movie_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->movie_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	}
}
System::Void AddNewReviewToDB::assmnt_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e)
{
	this->assmnt_comboBox->BackColor = System::Drawing::Color::AliceBlue;
	this->assmnt_comboBox->ForeColor = System::Drawing::Color::RoyalBlue;
}
System::Void AddNewReviewToDB::assmnt_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e)
{
	if (this->assmnt_comboBox->SelectedIndex == -1)
	{
		this->assmnt_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->assmnt_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	}
}
System::Void AddNewReviewToDB::post_review_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	String^ comment_text{ this->comment_textBox->Text->ToString() };
	Boolean^ forbidden_symbol{};
	for (int i{}; i < comment_text->Length; i++)
		if (comment_text[i] == '\'')
		{
			forbidden_symbol = true;
			break;
		}
	if (this->cinema_comboBox->SelectedIndex == -1 || this->assmnt_comboBox->SelectedIndex == -1 || (this->movie_comboBox->SelectedIndex == 0 && this->movie_comboBox->SelectedItem == "Выберите кинотеатр") || (this->movie_comboBox->SelectedIndex == -1 && this->movie_comboBox->SelectedItem != "Выберите кинотеатр"))
		MessageBox::Show("Заполните все отмеченные поля формы!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
	else if (forbidden_symbol)
		MessageBox::Show("Не используйте символ ' (используйте символ \" вместо него)!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
	else
	{
		DataBaseQueries^ queryDB = gcnew DataBaseQueries();
		queryDB->ConnectToDB();
		queryDB->openConnection();
		Int32^ cinemaID = queryDB->getCinemaIDbyCinemaName(this->cinema_comboBox->SelectedItem->ToString());
		Int32^ movieID = queryDB->getMovieIDbyMovieName(cinemaID, this->movie_comboBox->SelectedItem->ToString());
		queryDB->addNewReviewToDB(cinemaID, movieID, this->assmnt_comboBox->SelectedItem->ToString(), this->userName, this->comment_textBox->Text);
		queryDB->closeConnection();
		this->cinema_comboBox->SelectedIndex = -1;
		this->movie_comboBox->Items->Clear();
		this->movie_comboBox->Items->Add(L"Выберите кинотеатр");
		this->movie_comboBox->SelectedIndex = 0;
		this->assmnt_comboBox->SelectedIndex = -1;
		this->comment_textBox->Text = "";
		//Окрас.
		this->cinema_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->cinema_comboBox->ForeColor = System::Drawing::Color::DarkRed;
		this->movie_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->movie_comboBox->ForeColor = System::Drawing::Color::DarkRed;
		this->assmnt_comboBox->BackColor = System::Drawing::Color::LightPink;
		this->assmnt_comboBox->ForeColor = System::Drawing::Color::DarkRed;
	}
}