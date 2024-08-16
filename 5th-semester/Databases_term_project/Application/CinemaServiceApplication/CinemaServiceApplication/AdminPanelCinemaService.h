#pragma once

#include "DataBaseQueries.h"

namespace CinemaServiceApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ AdminPanelCinemaService
	/// </summary>
	public ref class AdminPanelCinemaService : public System::Windows::Forms::Form
	{
	public:
		AdminPanelCinemaService(void);
		AdminPanelCinemaService(String^ userLogin);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~AdminPanelCinemaService();
	private: Int32 choice{};
	private: String^ adminLogin{};
	//ќбщее дл€ всех вкладок.
	private: System::Windows::Forms::Button^ admin_close_btn;
	private: System::Windows::Forms::Label^ admin_label;
	private: System::Windows::Forms::Panel^ admin_fromBtn_submain_panel;
	private: System::Windows::Forms::Panel^ admin_submain_btn_panel;
	private: System::Windows::Forms::Button^ change_user_btn;
	private: System::Windows::Forms::Button^ change_cinema_btn;
	private: System::Windows::Forms::TextBox^ admin_info_text;
	private: System::Windows::Forms::Button^ change_review_btn;
	private: System::Windows::Forms::Button^ change_movie_btn;
	private: System::Windows::Forms::DataGridView^ info_DataGridView;
	//Ћокальное дл€ всех вкладок.
	private: System::Windows::Forms::Button^ delete_data_btn;
	private: System::Windows::Forms::Button^ add_data_btn;
	private: System::Windows::Forms::Button^ update_data_btn;
	private: System::Windows::Forms::Button^ apply_data_btn;
	private: System::Windows::Forms::Button^ clear_data_btn;
	private: System::Windows::Forms::Panel^ change_data_panel;
	private: System::Windows::Forms::Panel^ func_btns_panel;
	//¬кладка пользователи.
	private: System::Windows::Forms::Label^ userID_label;
	private: System::Windows::Forms::TextBox^ userID_textBox;
	private: System::Windows::Forms::Label^ userLogin_label;
	private: System::Windows::Forms::TextBox^ userLogin_textBox;
	private: System::Windows::Forms::Label^ userRole_label;
	private: System::Windows::Forms::Label^ userPswd_label;
	private: System::Windows::Forms::ComboBox^ userRole_comboBox;
	private: System::Windows::Forms::TextBox^ userPswd_textBox;
	//¬кладка кинотеатры.
	private: System::Windows::Forms::Label^ cinemaID_label;
	private: System::Windows::Forms::TextBox^ cinemaID_textBox;
	private: System::Windows::Forms::Label^ street_label;
	private: System::Windows::Forms::Label^ city_label;
	private: System::Windows::Forms::Label^ cinemaName_label;
	private: System::Windows::Forms::Label^ cinemaPicture_label;
	private: System::Windows::Forms::TextBox^ street_textBox;
	private: System::Windows::Forms::TextBox^ city_textBox;
	private: System::Windows::Forms::TextBox^ houseDescr_textBox;
	private: System::Windows::Forms::TextBox^ cinemaName_textBox;
	private: System::Windows::Forms::TextBox^ houseNumber_textBox;
	private: System::Windows::Forms::TextBox^ cinemaPicture_textBox;
	private: System::Windows::Forms::Label^ closingTime_label;
	private: System::Windows::Forms::Label^ openingTime_label;
	private: System::Windows::Forms::Label^ houseDescr_label;
	private: System::Windows::Forms::Label^ houseLetter_label;
	private: System::Windows::Forms::Label^ houseNumber_label;
	private: System::Windows::Forms::TextBox^ contactInf_textBox;
	private: System::Windows::Forms::Label^ contactInf_label;
	private: System::Windows::Forms::MaskedTextBox^ closingTime_textBox;
	private: System::Windows::Forms::MaskedTextBox^ openingTime_textBox;
	private: System::Windows::Forms::TextBox^ houseLetter_textBox;
	//¬кладка фильмы.
	private: System::Windows::Forms::Label^ movieID_label;
	private: System::Windows::Forms::Label^ ageLimit_label;
	private: System::Windows::Forms::Label^ genre_label;
	private: System::Windows::Forms::Label^ release_label;
	private: System::Windows::Forms::Label^ movieName_label;
	private: System::Windows::Forms::TextBox^ movieID_textBox;
	private: System::Windows::Forms::TextBox^ genre_textBox;
	private: System::Windows::Forms::TextBox^ movieName_textBox;
	private: System::Windows::Forms::MaskedTextBox^ duration_textBox;
	private: System::Windows::Forms::Label^ forMovieCinemaName_label;
	private: System::Windows::Forms::Label^ movieFormat_label;
	private: System::Windows::Forms::Label^ duration_label;
	private: System::Windows::Forms::MaskedTextBox^ ageLimit_textBox;
	private: System::Windows::Forms::MaskedTextBox^ release_textBox;
	private: System::Windows::Forms::ComboBox^ movieFormat_comboBox;
	private: System::Windows::Forms::ComboBox^ cinemaName_comboBox;
	//¬кладка комментарии.
	private: System::Windows::Forms::Label^ reviewID_label;
	private: System::Windows::Forms::TextBox^ comment_textBox;
	private: System::Windows::Forms::TextBox^ reviewID_textBox;
	private: System::Windows::Forms::Label^ comment_label;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
		private: System::Void admin_close_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void change_user_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void change_cinema_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void change_movie_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void change_review_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void delete_data_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void add_data_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void update_data_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void apply_data_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void clear_data_btn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
