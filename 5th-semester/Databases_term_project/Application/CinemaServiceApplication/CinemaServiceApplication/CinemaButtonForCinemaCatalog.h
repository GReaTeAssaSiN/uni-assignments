#pragma once

#include "CinemaTableDBElement.h"
#include "DataBaseQueries.h"
#include "MovieButtonForMovieCatalog.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class CinemaButtonForCinemaCatalog : public System::Windows::Forms::Button
{
	private: Button^ cinema_btn{};
	private: PictureBox^ cinema_img{};
	private: TextBox^ cinema_description{};
	private: TextBox^ search_textBox{};
	private: Button^ search_btn{};
	private: Panel^ movie_catalog_panel{};
	private: CinemaTableDBElement^ cinema{};
	private: Panel^ main_cinema_btn_panel{};
	private: String^ userName{};
	private: Label^ update_inf_label{};
	public: CinemaButtonForCinemaCatalog(SqlDataReader^ reader, Panel^ main_cinema_btn_panel, String^ userName, Label^ update_inf_label);
	public: Button^ getCinemaBtn();
	private: System::Void cinema_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void search_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void search_textBox_Enter(System::Object^ sender, System::EventArgs^ e);
	private: System::Void search_textBox_Leave(System::Object^ sender, System::EventArgs^ e);
};
