#pragma once

#include "CinemaButtonForCinemaCatalog.h"

namespace CinemaServiceApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Сводка для CinemaService
	/// </summary>
	public ref class CinemaService : public System::Windows::Forms::Form
	{
	public:
		CinemaService(void);
		CinemaService(String^ UserName);
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~CinemaService();
	private: String^ UserName{};
	private: CinemaButtonForCinemaCatalog^ cinema_btn_for_cinema_ctlg{};
	private: System::Windows::Forms::FlowLayoutPanel^ submain_cinema_flowLayoutPanel;
	private: System::Windows::Forms::Button^ cinemaservice_exit_btn;
	private: System::Windows::Forms::Label^ submain_cinema_label;
	private: System::Windows::Forms::Panel^ submain_cinema_panel;
	private: System::Windows::Forms::Button^ search_btn;
	private: System::Windows::Forms::TextBox^ search_textBox;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
		private: System::Void search_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void cinemaservice_exit_btn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void search_textBox_Enter(System::Object^ sender, System::EventArgs^ e);
		private: System::Void search_textBox_Leave(System::Object^ sender, System::EventArgs^ e);
	};
}
