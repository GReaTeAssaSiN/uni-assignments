#include "MovieButtonForMovieCatalog.h"

MovieButtonForMovieCatalog::MovieButtonForMovieCatalog(SqlDataReader^ reader, Panel^ main_movie_btn_panel, Int32^ cinemaID, String^ userName, Label^ update_inf_label)
{
	this->add_new_review_btn = (gcnew System::Windows::Forms::Button());
	this->movie_btn = (gcnew System::Windows::Forms::Button());
	this->submain_movie_btn_panel = (gcnew System::Windows::Forms::Panel());
	this->movie = gcnew MovieTableDBElement(reader);
	this->main_movie_btn_panel = main_movie_btn_panel;
	this->movie = gcnew MovieTableDBElement(reader);
	this->cinemaID = cinemaID;
	this->userName = userName;
	this->update_inf_label = update_inf_label;
	//
	// add_new_review_button 
	//
	this->add_new_review_btn->BackColor = System::Drawing::Color::FromArgb(128, 128, 128);
	this->add_new_review_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(42, 52, 57);
	this->add_new_review_btn->FlatAppearance->BorderSize = 2;
	this->add_new_review_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(105, 105, 105);
	this->add_new_review_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(112, 128, 144);
	this->add_new_review_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->add_new_review_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->add_new_review_btn->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->add_new_review_btn->ForeColor = System::Drawing::Color::Black;
	this->add_new_review_btn->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
	this->add_new_review_btn->Size = System::Drawing::Size(860, 50);
	this->add_new_review_btn->MaximumSize = System::Drawing::Size(860, 50);
	this->add_new_review_btn->MinimumSize = System::Drawing::Size(860, 50);
	this->add_new_review_btn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->add_new_review_btn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->add_new_review_btn->Image = Image->FromFile("D:\\КАИ\\Базы Данных\\Курсовая\\Images\\add_new_data.bmp");
	this->add_new_review_btn->Text = L"Добавить отзыв о фильме в кинотеатре";
	this->add_new_review_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieButtonForMovieCatalog::add_new_review_btn_MouseClick);
	//
	// movie_btn
	//
	this->movie_btn->BackColor = System::Drawing::Color::FromArgb(80, 172, 118);
	this->movie_btn->Cursor = System::Windows::Forms::Cursors::Hand;
	this->movie_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(24, 77, 42);
	this->movie_btn->FlatAppearance->BorderSize = 3;
	this->movie_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(0, 66, 37);
	this->movie_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(124, 250, 202);
	this->movie_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->movie_btn->ForeColor = System::Drawing::Color::Black;
	this->movie_btn->Image = Image->FromFile(L"D:\\КАИ\\Базы данных\\Курсовая\\Images\\Movie_Icon.bmp");
	this->movie_btn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->movie_btn->Size = System::Drawing::Size(421, 123);
	this->movie_btn->MaximumSize = System::Drawing::Size(421, 123);
	this->movie_btn->MinimumSize = System::Drawing::Size(421, 123);;
	String^ descr_str = "Название фильма: " + this->movie->getMovieName() + "\r\nВозрастное ограничение: " + this->movie->getAgeLimit() + "\r\nЖанр: " +
		this->movie->getGenre() + "\r\nДлительность: " + this->movie->getDuration();
	this->movie_btn->Text = descr_str;
	this->movie_btn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->movie_btn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->movie_btn->Click += gcnew System::EventHandler(this, &MovieButtonForMovieCatalog::movie_btn_Click);
	//
	// submain_movie_btn_panel
	//
	this->submain_movie_btn_panel->AutoScroll = true;
	this->submain_movie_btn_panel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(140)),
		static_cast<System::Int32>(static_cast<System::Byte>(146)), static_cast<System::Int32>(static_cast<System::Byte>(172)));
	this->submain_movie_btn_panel->Location = System::Drawing::Point(0, 50);
	this->submain_movie_btn_panel->MaximumSize = System::Drawing::Size(860, 650);
	this->submain_movie_btn_panel->MinimumSize = System::Drawing::Size(860, 620);
	this->submain_movie_btn_panel->Size = System::Drawing::Size(860, 620);
}
Button^ MovieButtonForMovieCatalog::getMovieBtn()
{
	return movie_btn;
}
System::Void MovieButtonForMovieCatalog::movie_btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->update_inf_label->Text = L"Выберите кинотеатр или добавьте свой комментарий к фильму";
	this->main_movie_btn_panel->Controls->Clear();
	this->main_movie_btn_panel->SuspendLayout();
	this->submain_movie_btn_panel->SuspendLayout();
	this->main_movie_btn_panel->Controls->Add(add_new_review_btn);
	//Запрос каталога комментариев соответствующего фильма соответствующего кинотеатра.
	DataBaseQueries^ queryDB = gcnew DataBaseQueries();
	queryDB->ConnectToDB();
	queryDB->openConnection();
	SqlDataReader^ reader = queryDB->getReaderReviewCatalog(cinemaID, movie->getMovieID());
	Int32 ddx{}, ddy{};
	while (reader->Read())
	{
		ReviewButtonForReviewCatalog^ review_btn = gcnew ReviewButtonForReviewCatalog(reader);
		review_btn->getReviewPanel()->Location = System::Drawing::Point(ddx, ddy);
		this->submain_movie_btn_panel->Controls->Add(review_btn->getReviewPanel());
		if (ddx + 425 > 840)
		{
			ddx = 0;
			ddy += 260;
		}
		else
			ddx += 425;
	}
	queryDB->closeConnection();
	this->main_movie_btn_panel->Controls->Add(this->submain_movie_btn_panel);
	this->submain_movie_btn_panel->ResumeLayout();
	this->main_movie_btn_panel->ResumeLayout();
}
System::Void MovieButtonForMovieCatalog::add_new_review_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->update_inf_label->Text = L"Заполните форму для создания комментария";
	this->main_movie_btn_panel->Controls->Clear();
	this->main_movie_btn_panel->SuspendLayout();
	AddNewReviewToDB^ new_review = gcnew AddNewReviewToDB(this->userName);
	this->main_movie_btn_panel->Controls->Add(new_review->getAddNewReviewPanel());
	this->main_movie_btn_panel->ResumeLayout();
}