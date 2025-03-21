#include "ReviewButtonForReviewCatalog.h"

ReviewButtonForReviewCatalog::ReviewButtonForReviewCatalog(SqlDataReader^ reader)
{
	this->review_panel = (gcnew System::Windows::Forms::Panel());
	this->userLogin_DateTime_label = (gcnew System::Windows::Forms::Label());
	this->cinemaName_label = (gcnew System::Windows::Forms::Label());
	this->movieName_label = (gcnew System::Windows::Forms::Label());
	this->assmnt_movie_pictBox = (gcnew System::Windows::Forms::PictureBox());
	this->comment_textBox = (gcnew System::Windows::Forms::TextBox());
	this->review = gcnew ReviewTableDBElement(reader);
	this->userName_DateTime_string = review->getUserLogin() + " " + review->getCommentDateTime()->ToString();
	this->review_panel->SuspendLayout();
	//
	// userLogin_DateTime_label
	//
	this->userLogin_DateTime_label->BackColor = System::Drawing::Color::Transparent;
	this->userLogin_DateTime_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->userLogin_DateTime_label->Location = System::Drawing::Point(0, 0);
	this->userLogin_DateTime_label->Size = System::Drawing::Size(415, 50);
	this->userLogin_DateTime_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->userLogin_DateTime_label->MaximumSize = System::Drawing::Size(415, 50);
	this->userLogin_DateTime_label->MinimumSize = System::Drawing::Size(415, 50);
	this->userLogin_DateTime_label->Text = userName_DateTime_string;
	this->userLogin_DateTime_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// cinemaName_label
	//
	this->cinemaName_label->BackColor = System::Drawing::Color::Transparent;
	this->cinemaName_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->cinemaName_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->cinemaName_label->Location = System::Drawing::Point(0, 50);
	this->cinemaName_label->Size = System::Drawing::Size(415, 50);
	this->cinemaName_label->MaximumSize = System::Drawing::Size(415, 50);
	this->cinemaName_label->MinimumSize = System::Drawing::Size(415, 50);
	this->cinemaName_label->Text = "КИНОТЕАТР: " + this->review->getCinemaName();
	this->cinemaName_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// movieName_label
	//
	this->movieName_label->BackColor = System::Drawing::Color::Transparent;
	this->movieName_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->movieName_label->Location = System::Drawing::Point(0, 100);
	this->movieName_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->movieName_label->Size = System::Drawing::Size(210, 50);
	this->movieName_label->MaximumSize = System::Drawing::Size(210, 50);
	this->movieName_label->MinimumSize = System::Drawing::Size(210, 50);
	this->movieName_label->Text = "ФИЛЬМ: " + this->review->getMovieName();
	this->movieName_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	//
	// assmnt_movie_pictBox
	//
	if (this->review->getTranscriptPicture())
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->review->getTranscriptPicture());
		this->assmnt_movie_pictBox->BackgroundImage = gcnew Bitmap(ms);
		this->assmnt_movie_pictBox->BackColor = System::Drawing::Color::Transparent;
		this->assmnt_movie_pictBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->assmnt_movie_pictBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->assmnt_movie_pictBox->Location = System::Drawing::Point(210, 100);
		this->assmnt_movie_pictBox->Size = System::Drawing::Size(205, 50);
		this->assmnt_movie_pictBox->MaximumSize = System::Drawing::Size(205, 50);
		this->assmnt_movie_pictBox->MinimumSize = System::Drawing::Size(205, 50);
	}
	//
	// comment_textBox
	//
	this->comment_textBox->BackColor = System::Drawing::Color::FromArgb(194, 194, 194);
	this->comment_textBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->comment_textBox->Cursor = System::Windows::Forms::Cursors::IBeam;
	this->comment_textBox->Location = System::Drawing::Point(0, 150);
	this->comment_textBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
	this->comment_textBox->ReadOnly = true;
	this->comment_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	this->comment_textBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
	this->comment_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->comment_textBox->Size = System::Drawing::Size(415, 125);
	this->comment_textBox->MaximumSize = System::Drawing::Size(415, 125);
	this->comment_textBox->MinimumSize = System::Drawing::Size(415, 125);
	this->comment_textBox->Multiline = true;
	this->comment_textBox->Text = this->review->getComment();
	//
	// review_panel
	//
	this->review_panel->BackColor = System::Drawing::Color::FromArgb(239, 238, 240);
	this->review_panel->Size = System::Drawing::Size(415, 275);
	this->review_panel->MaximumSize = System::Drawing::Size(415, 250);
	this->review_panel->MinimumSize = System::Drawing::Size(415, 250);
	this->review_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->review_panel->Controls->Add(this->userLogin_DateTime_label);
	this->review_panel->Controls->Add(this->cinemaName_label);
	this->review_panel->Controls->Add(this->movieName_label);
	this->review_panel->Controls->Add(this->assmnt_movie_pictBox);
	this->review_panel->Controls->Add(this->comment_textBox);
	this->review_panel->ResumeLayout();
}
Panel^ ReviewButtonForReviewCatalog::getReviewPanel()
{
	return review_panel;
}