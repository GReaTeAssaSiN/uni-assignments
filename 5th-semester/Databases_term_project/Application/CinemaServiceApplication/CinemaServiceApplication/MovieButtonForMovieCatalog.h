#pragma once

#include "MovieTableDBElement.h"
#include "DataBaseQueries.h"
#include "ReviewButtonForReviewCatalog.h"
#include "AddNewReviewToDB.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class MovieButtonForMovieCatalog : public System::Windows::Forms::Button
{
	private: Button^ add_new_review_btn{};
	private: Button^ movie_btn{};
	private: MovieTableDBElement^ movie{};
	private: Panel^ main_movie_btn_panel{};
	private: Panel^ submain_movie_btn_panel{};
	private: Int32^ cinemaID{};
	private: String^ userName{};
	private: Label^ update_inf_label{};
	public: MovieButtonForMovieCatalog(SqlDataReader^ reader, Panel^ main_movie_btn_panel, Int32^ cinemaID, String^ userName, Label^ update_inf_label);
	public: Button^ getMovieBtn();
	private: System::Void movie_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void add_new_review_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};



