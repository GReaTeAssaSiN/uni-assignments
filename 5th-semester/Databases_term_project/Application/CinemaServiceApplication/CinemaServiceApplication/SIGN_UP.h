#pragma once

#include "LOG_IN.h"
#include "DataBaseQueries.h"

namespace CinemaServiceApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ SIGN_UP
	/// </summary>
	public ref class SIGN_UP : public System::Windows::Forms::Form
	{
	public:
		SIGN_UP(void);
		SIGN_UP(LOG_IN^ parent_log_in_form);
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~SIGN_UP();
	private: LOG_IN^ parent_log_in_form{};
	private: System::Windows::Forms::Button^ sign_up_close_btn;
	private: System::Windows::Forms::Button^ sign_up_enter_btn;
	private: System::Windows::Forms::Label^ sign_up_main_label;
	private: System::Windows::Forms::Label^ sign_up_label_C2;
	private: System::Windows::Forms::Label^ sign_up_label_E1;
	private: System::Windows::Forms::Label^ sign_up_label_I2;
	private: System::Windows::Forms::Label^ sign_up_label_V;
	private: System::Windows::Forms::Label^ sign_up_label_R;
	private: System::Windows::Forms::Label^ sign_up_label_E2;
	private: System::Windows::Forms::Label^ sign_up_label_S;
	private: System::Windows::Forms::Label^ sign_up_label_A;
	private: System::Windows::Forms::Label^ sign_up_label_M;
	private: System::Windows::Forms::Label^ sign_up_label_E;
	private: System::Windows::Forms::Label^ sign_up_label_N;
	private: System::Windows::Forms::Label^ sign_up_label_I;
	private: System::Windows::Forms::Label^ sign_up_label_C;
	private: System::Windows::Forms::Button^ sign_up_clear_btn;
	private: System::Windows::Forms::TextBox^ sign_up_pswd_textBox;
	private: System::Windows::Forms::TextBox^ sign_up_login_textBox;
	private: System::Windows::Forms::Label^ sign_up_label_pswd;
	private: System::Windows::Forms::Label^ sign_up_login_label;
	private: System::Windows::Forms::Button^ eye_hide_btn;
	private: System::Windows::Forms::Button^ eye_show_btn;
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
		private: System::Void sign_up_close_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void sign_up_clear_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void sign_up_enter_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void eye_hide_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void eye_show_btn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
