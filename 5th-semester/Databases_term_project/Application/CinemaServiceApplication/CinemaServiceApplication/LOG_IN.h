#pragma once

#include "CinemaService.h"
#include "AdminPanelCinemaService.h"
#include "DataBaseQueries.h"

namespace CinemaServiceApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ LOG_IN
	/// </summary>
	public ref class LOG_IN : public System::Windows::Forms::Form
	{
	public:
		LOG_IN(void);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~LOG_IN();
	private: System::Windows::Forms::Button^ log_in_enter_btn;
	private: System::Windows::Forms::Button^ log_in_close_btn;
	private: System::Windows::Forms::Label^ log_in_label_C;
	private: System::Windows::Forms::Label^ log_in_main_label;
	private: System::Windows::Forms::Label^ log_in_label_I;
	private: System::Windows::Forms::Label^ log_in_label_N;
	private: System::Windows::Forms::Label^ log_in_label_E;
	private: System::Windows::Forms::Label^ log_in_label_M;
	private: System::Windows::Forms::Label^ log_in_label_A;
	private: System::Windows::Forms::Label^ log_in_label_S;
	private: System::Windows::Forms::Label^ log_in_label_E2;
	private: System::Windows::Forms::Label^ log_in_label_R;
	private: System::Windows::Forms::Label^ log_in_label_V;
	private: System::Windows::Forms::Label^ log_in_label_I2;
	private: System::Windows::Forms::Label^ log_in_label_E1;
	private: System::Windows::Forms::Label^ log_in_label_C2;
	private: System::Windows::Forms::Label^ log_in_login_label;
	private: System::Windows::Forms::Label^ log_in_label_pswd;
	private: System::Windows::Forms::TextBox^ log_in_login_textBox;
	private: System::Windows::Forms::TextBox^ log_in_pswd_textBox;
	private: System::Windows::Forms::Button^ eye_hide_btn;
	private: System::Windows::Forms::Button^ log_in_clear_btn;
	private: System::Windows::Forms::LinkLabel^ log_in_link_label;
	private: System::Windows::Forms::Button^ eye_show_btn;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
		private: System::Void log_in_close_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void log_in_enter_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void log_in_clear_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void eye_hide_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void eye_show_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void log_in_link_label_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	};
}
