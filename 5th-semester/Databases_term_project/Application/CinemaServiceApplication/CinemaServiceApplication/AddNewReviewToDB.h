#pragma once

#include "DataBaseQueries.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class AddNewReviewToDB : public System::Windows::Forms::Panel
{
	private: System::Windows::Forms::Panel^ add_new_review_panel{};
	private: System::Windows::Forms::Button^ post_review_btn{};
	private: System::Windows::Forms::Label^ userLogin_DateTime_label{};
	private: System::Windows::Forms::Label^ cinema_label{};
	private: System::Windows::Forms::Label^ movie_label{};
	private: System::Windows::Forms::Label^ assmnt_label{};
	private: System::Windows::Forms::ComboBox^ cinema_comboBox{};
	private: System::Windows::Forms::ComboBox^ movie_comboBox{};
	private: System::Windows::Forms::ComboBox^ assmnt_comboBox{};
	private: System::Windows::Forms::TextBox^ comment_textBox{};
	private: System::Windows::Forms::Button^ clear_btn{};
	private: String^ userName{};
	public: AddNewReviewToDB(String^ userName);
	public: Panel^ getAddNewReviewPanel();
	private: System::Void cinema_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e);	
	private: System::Void cinema_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e);
	private: System::Void cinema_comboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void movie_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e);
	private: System::Void movie_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e);
	private: System::Void assmnt_comboBox_DropDown(System::Object^ sender, System::EventArgs^ e);
	private: System::Void assmnt_comboBox_DropDownClosed(System::Object^ sender, System::EventArgs^ e);
	private: System::Void post_review_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void clear_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};