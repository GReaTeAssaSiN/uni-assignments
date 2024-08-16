#pragma once

#include "ReviewTableDBElement.h"
#include "DataBaseQueries.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;


ref class ReviewButtonForReviewCatalog : public System::Windows::Forms::Panel
{
	private: System::Windows::Forms::Panel^ review_panel{};
	private: System::Windows::Forms::Label^ userLogin_DateTime_label{};
	private: System::Windows::Forms::Label^ cinemaName_label{};
	private: System::Windows::Forms::Label^ movieName_label{};
	private: System::Windows::Forms::PictureBox^ assmnt_movie_pictBox{};
	private: System::Windows::Forms::TextBox^ comment_textBox{};
	private: ReviewTableDBElement^ review{};
	private: String^ userName_DateTime_string{};
	public: ReviewButtonForReviewCatalog(SqlDataReader^ reader);
	public: Panel^ getReviewPanel();
};

