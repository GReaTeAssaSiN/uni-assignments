#include "SIGN_UP.h"

namespace CinemaServiceApplication
{
	SIGN_UP::SIGN_UP(void)
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}
	SIGN_UP::SIGN_UP(LOG_IN^ parent_log_in_form)
	{
		InitializeComponent();
		this->parent_log_in_form = parent_log_in_form;
	}
	SIGN_UP::~SIGN_UP()
	{
		if (components)
		{
			delete components;
		}
	}
	void SIGN_UP::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SIGN_UP::typeid));
		this->sign_up_close_btn = (gcnew System::Windows::Forms::Button());
		this->sign_up_enter_btn = (gcnew System::Windows::Forms::Button());
		this->sign_up_main_label = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_C2 = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_E1 = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_I2 = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_V = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_R = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_E2 = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_S = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_A = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_M = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_E = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_N = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_I = (gcnew System::Windows::Forms::Label());
		this->sign_up_label_C = (gcnew System::Windows::Forms::Label());
		this->sign_up_clear_btn = (gcnew System::Windows::Forms::Button());
		this->sign_up_pswd_textBox = (gcnew System::Windows::Forms::TextBox());
		this->sign_up_login_textBox = (gcnew System::Windows::Forms::TextBox());
		this->sign_up_label_pswd = (gcnew System::Windows::Forms::Label());
		this->sign_up_login_label = (gcnew System::Windows::Forms::Label());
		this->eye_hide_btn = (gcnew System::Windows::Forms::Button());
		this->eye_show_btn = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// sign_up_close_btn
		// 
		this->sign_up_close_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->sign_up_close_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sign_up_close_btn.BackgroundImage")));
		this->sign_up_close_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->sign_up_close_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->sign_up_close_btn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->sign_up_close_btn->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
		this->sign_up_close_btn->FlatAppearance->BorderSize = 3;
		this->sign_up_close_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Maroon;
		this->sign_up_close_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->sign_up_close_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_close_btn->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_close_btn->Location = System::Drawing::Point(520, 0);
		this->sign_up_close_btn->MaximumSize = System::Drawing::Size(80, 80);
		this->sign_up_close_btn->MinimumSize = System::Drawing::Size(80, 80);
		this->sign_up_close_btn->Name = L"sign_up_close_btn";
		this->sign_up_close_btn->Size = System::Drawing::Size(80, 80);
		this->sign_up_close_btn->TabIndex = 2;
		this->sign_up_close_btn->UseVisualStyleBackColor = false;
		this->sign_up_close_btn->Click += gcnew System::EventHandler(this, &SIGN_UP::sign_up_close_btn_Click);
		// 
		// sign_up_enter_btn
		// 
		this->sign_up_enter_btn->BackColor = System::Drawing::Color::Azure;
		this->sign_up_enter_btn->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaptionText;
		this->sign_up_enter_btn->FlatAppearance->BorderSize = 2;
		this->sign_up_enter_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Teal;
		this->sign_up_enter_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SpringGreen;
		this->sign_up_enter_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_enter_btn->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_enter_btn->Location = System::Drawing::Point(124, 359);
		this->sign_up_enter_btn->MaximumSize = System::Drawing::Size(352, 58);
		this->sign_up_enter_btn->MinimumSize = System::Drawing::Size(352, 58);
		this->sign_up_enter_btn->Name = L"sign_up_enter_btn";
		this->sign_up_enter_btn->Size = System::Drawing::Size(352, 58);
		this->sign_up_enter_btn->TabIndex = 3;
		this->sign_up_enter_btn->Text = L"ЗАРЕГИСТРИРОВАТЬ";
		this->sign_up_enter_btn->UseVisualStyleBackColor = false;
		this->sign_up_enter_btn->Click += gcnew System::EventHandler(this, &SIGN_UP::sign_up_enter_btn_Click);
		// 
		// sign_up_main_label
		// 
		this->sign_up_main_label->BackColor = System::Drawing::Color::LightBlue;
		this->sign_up_main_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->sign_up_main_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_main_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 25.8F, System::Drawing::FontStyle::Bold));
		this->sign_up_main_label->ForeColor = System::Drawing::SystemColors::ControlText;
		this->sign_up_main_label->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sign_up_main_label.Image")));
		this->sign_up_main_label->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
		this->sign_up_main_label->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_main_label->Location = System::Drawing::Point(0, 80);
		this->sign_up_main_label->MaximumSize = System::Drawing::Size(600, 80);
		this->sign_up_main_label->MinimumSize = System::Drawing::Size(600, 80);
		this->sign_up_main_label->Name = L"sign_up_main_label";
		this->sign_up_main_label->Size = System::Drawing::Size(600, 80);
		this->sign_up_main_label->TabIndex = 4;
		this->sign_up_main_label->Text = L"РЕГИСТРАЦИЯ";
		this->sign_up_main_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// sign_up_label_C2
		// 
		this->sign_up_label_C2->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_C2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_C2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_C2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
		this->sign_up_label_C2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_C2->Location = System::Drawing::Point(440, 0);
		this->sign_up_label_C2->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_C2->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_C2->Name = L"sign_up_label_C2";
		this->sign_up_label_C2->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_C2->TabIndex = 28;
		this->sign_up_label_C2->Text = L"C";
		this->sign_up_label_C2->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_E1
		// 
		this->sign_up_label_E1->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_E1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_E1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_E1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(119)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
		this->sign_up_label_E1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_E1->Location = System::Drawing::Point(480, 0);
		this->sign_up_label_E1->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E1->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E1->Name = L"sign_up_label_E1";
		this->sign_up_label_E1->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_E1->TabIndex = 27;
		this->sign_up_label_E1->Text = L"E";
		this->sign_up_label_E1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_I2
		// 
		this->sign_up_label_I2->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_I2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_I2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_I2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
			static_cast<System::Int32>(static_cast<System::Byte>(188)), static_cast<System::Int32>(static_cast<System::Byte>(29)));
		this->sign_up_label_I2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_I2->Location = System::Drawing::Point(400, 0);
		this->sign_up_label_I2->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_I2->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_I2->Name = L"sign_up_label_I2";
		this->sign_up_label_I2->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_I2->TabIndex = 26;
		this->sign_up_label_I2->Text = L"I";
		this->sign_up_label_I2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_V
		// 
		this->sign_up_label_V->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_V->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_V->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_V->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
			static_cast<System::Int32>(static_cast<System::Byte>(25)));
		this->sign_up_label_V->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_V->Location = System::Drawing::Point(360, 0);
		this->sign_up_label_V->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_V->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_V->Name = L"sign_up_label_V";
		this->sign_up_label_V->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_V->TabIndex = 25;
		this->sign_up_label_V->Text = L"V";
		this->sign_up_label_V->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_R
		// 
		this->sign_up_label_R->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_R->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_R->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_R->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(88)),
			static_cast<System::Int32>(static_cast<System::Byte>(21)));
		this->sign_up_label_R->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_R->Location = System::Drawing::Point(320, 0);
		this->sign_up_label_R->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_R->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_R->Name = L"sign_up_label_R";
		this->sign_up_label_R->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_R->TabIndex = 24;
		this->sign_up_label_R->Text = L"R";
		this->sign_up_label_R->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_E2
		// 
		this->sign_up_label_E2->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_E2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_E2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_E2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)),
			static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(23)));
		this->sign_up_label_E2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_E2->Location = System::Drawing::Point(280, 0);
		this->sign_up_label_E2->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E2->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E2->Name = L"sign_up_label_E2";
		this->sign_up_label_E2->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_E2->TabIndex = 23;
		this->sign_up_label_E2->Text = L"E";
		this->sign_up_label_E2->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_S
		// 
		this->sign_up_label_S->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_S->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_S->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_S->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(27)),
			static_cast<System::Int32>(static_cast<System::Byte>(23)));
		this->sign_up_label_S->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_S->Location = System::Drawing::Point(240, 0);
		this->sign_up_label_S->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_S->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_S->Name = L"sign_up_label_S";
		this->sign_up_label_S->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_S->TabIndex = 22;
		this->sign_up_label_S->Text = L"S";
		this->sign_up_label_S->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_A
		// 
		this->sign_up_label_A->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_A->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_A->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_A->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(24)),
			static_cast<System::Int32>(static_cast<System::Byte>(119)));
		this->sign_up_label_A->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_A->Location = System::Drawing::Point(200, 0);
		this->sign_up_label_A->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_A->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_A->Name = L"sign_up_label_A";
		this->sign_up_label_A->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_A->TabIndex = 21;
		this->sign_up_label_A->Text = L"A";
		this->sign_up_label_A->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_M
		// 
		this->sign_up_label_M->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_M->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_M->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_M->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(234)));
		this->sign_up_label_M->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_M->Location = System::Drawing::Point(160, 0);
		this->sign_up_label_M->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_M->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_M->Name = L"sign_up_label_M";
		this->sign_up_label_M->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_M->TabIndex = 20;
		this->sign_up_label_M->Text = L"M";
		this->sign_up_label_M->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_E
		// 
		this->sign_up_label_E->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_E->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_E->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_E->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->sign_up_label_E->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_E->Location = System::Drawing::Point(120, 0);
		this->sign_up_label_E->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_E->Name = L"sign_up_label_E";
		this->sign_up_label_E->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_E->TabIndex = 19;
		this->sign_up_label_E->Text = L"E";
		this->sign_up_label_E->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_N
		// 
		this->sign_up_label_N->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_N->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_N->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_N->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(101)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->sign_up_label_N->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_N->Location = System::Drawing::Point(80, 0);
		this->sign_up_label_N->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_N->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_N->Name = L"sign_up_label_N";
		this->sign_up_label_N->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_N->TabIndex = 18;
		this->sign_up_label_N->Text = L"N";
		this->sign_up_label_N->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_label_I
		// 
		this->sign_up_label_I->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_I->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_I->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_I->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(29)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->sign_up_label_I->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_I->Location = System::Drawing::Point(40, 0);
		this->sign_up_label_I->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_I->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_I->Name = L"sign_up_label_I";
		this->sign_up_label_I->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_I->TabIndex = 17;
		this->sign_up_label_I->Text = L"I";
		this->sign_up_label_I->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
		// 
		// sign_up_label_C
		// 
		this->sign_up_label_C->BackColor = System::Drawing::Color::Indigo;
		this->sign_up_label_C->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_C->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold));
		this->sign_up_label_C->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->sign_up_label_C->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_C->Location = System::Drawing::Point(0, 0);
		this->sign_up_label_C->MaximumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_C->MinimumSize = System::Drawing::Size(40, 80);
		this->sign_up_label_C->Name = L"sign_up_label_C";
		this->sign_up_label_C->Size = System::Drawing::Size(40, 80);
		this->sign_up_label_C->TabIndex = 16;
		this->sign_up_label_C->Text = L"C";
		this->sign_up_label_C->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// sign_up_clear_btn
		// 
		this->sign_up_clear_btn->BackColor = System::Drawing::Color::DodgerBlue;
		this->sign_up_clear_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->sign_up_clear_btn->FlatAppearance->BorderColor = System::Drawing::Color::Navy;
		this->sign_up_clear_btn->FlatAppearance->BorderSize = 2;
		this->sign_up_clear_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DodgerBlue;
		this->sign_up_clear_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->sign_up_clear_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_clear_btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Bold));
		this->sign_up_clear_btn->ForeColor = System::Drawing::Color::White;
		this->sign_up_clear_btn->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_clear_btn->Location = System::Drawing::Point(520, 80);
		this->sign_up_clear_btn->MaximumSize = System::Drawing::Size(80, 80);
		this->sign_up_clear_btn->MinimumSize = System::Drawing::Size(80, 80);
		this->sign_up_clear_btn->Name = L"sign_up_clear_btn";
		this->sign_up_clear_btn->Size = System::Drawing::Size(80, 80);
		this->sign_up_clear_btn->TabIndex = 29;
		this->sign_up_clear_btn->Text = L"CLEAR";
		this->sign_up_clear_btn->UseVisualStyleBackColor = false;
		this->sign_up_clear_btn->Click += gcnew System::EventHandler(this, &SIGN_UP::sign_up_clear_btn_Click);
		// 
		// sign_up_pswd_textBox
		// 
		this->sign_up_pswd_textBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15));
		this->sign_up_pswd_textBox->Location = System::Drawing::Point(157, 274);
		this->sign_up_pswd_textBox->MaximumSize = System::Drawing::Size(400, 36);
		this->sign_up_pswd_textBox->MaxLength = 20;
		this->sign_up_pswd_textBox->MinimumSize = System::Drawing::Size(400, 36);
		this->sign_up_pswd_textBox->Name = L"sign_up_pswd_textBox";
		this->sign_up_pswd_textBox->Size = System::Drawing::Size(400, 36);
		this->sign_up_pswd_textBox->TabIndex = 33;
		this->sign_up_pswd_textBox->UseSystemPasswordChar = true;
		// 
		// sign_up_login_textBox
		// 
		this->sign_up_login_textBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15));
		this->sign_up_login_textBox->Location = System::Drawing::Point(157, 194);
		this->sign_up_login_textBox->MaximumSize = System::Drawing::Size(437, 36);
		this->sign_up_login_textBox->MaxLength = 20;
		this->sign_up_login_textBox->MinimumSize = System::Drawing::Size(437, 36);
		this->sign_up_login_textBox->Name = L"sign_up_login_textBox";
		this->sign_up_login_textBox->Size = System::Drawing::Size(437, 36);
		this->sign_up_login_textBox->TabIndex = 32;
		// 
		// sign_up_label_pswd
		// 
		this->sign_up_label_pswd->BackColor = System::Drawing::Color::Transparent;
		this->sign_up_label_pswd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_label_pswd->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Bold));
		this->sign_up_label_pswd->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_label_pswd->Location = System::Drawing::Point(6, 270);
		this->sign_up_label_pswd->MaximumSize = System::Drawing::Size(145, 40);
		this->sign_up_label_pswd->MinimumSize = System::Drawing::Size(145, 40);
		this->sign_up_label_pswd->Name = L"sign_up_label_pswd";
		this->sign_up_label_pswd->Size = System::Drawing::Size(145, 40);
		this->sign_up_label_pswd->TabIndex = 31;
		this->sign_up_label_pswd->Text = L"Пароль:";
		this->sign_up_label_pswd->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// sign_up_login_label
		// 
		this->sign_up_login_label->BackColor = System::Drawing::Color::Transparent;
		this->sign_up_login_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sign_up_login_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Bold));
		this->sign_up_login_label->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->sign_up_login_label->Location = System::Drawing::Point(6, 190);
		this->sign_up_login_label->MaximumSize = System::Drawing::Size(145, 40);
		this->sign_up_login_label->MinimumSize = System::Drawing::Size(145, 40);
		this->sign_up_login_label->Name = L"sign_up_login_label";
		this->sign_up_login_label->Size = System::Drawing::Size(145, 40);
		this->sign_up_login_label->TabIndex = 30;
		this->sign_up_login_label->Text = L"Логин:";
		this->sign_up_login_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// eye_hide_btn
		// 
		this->eye_hide_btn->BackColor = System::Drawing::Color::Transparent;
		this->eye_hide_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"eye_hide_btn.BackgroundImage")));
		this->eye_hide_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		this->eye_hide_btn->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->eye_hide_btn->Location = System::Drawing::Point(558, 274);
		this->eye_hide_btn->Name = L"eye_hide_btn";
		this->eye_hide_btn->Size = System::Drawing::Size(36, 36);
		this->eye_hide_btn->TabIndex = 34;
		this->eye_hide_btn->UseVisualStyleBackColor = false;
		this->eye_hide_btn->Click += gcnew System::EventHandler(this, &SIGN_UP::eye_hide_btn_Click);
		// 
		// eye_show_btn
		// 
		this->eye_show_btn->BackColor = System::Drawing::Color::Transparent;
		this->eye_show_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"eye_show_btn.BackgroundImage")));
		this->eye_show_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		this->eye_show_btn->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->eye_show_btn->Location = System::Drawing::Point(558, 274);
		this->eye_show_btn->Name = L"eye_show_btn";
		this->eye_show_btn->Size = System::Drawing::Size(36, 36);
		this->eye_show_btn->TabIndex = 35;
		this->eye_show_btn->UseVisualStyleBackColor = false;
		this->eye_show_btn->Click += gcnew System::EventHandler(this, &SIGN_UP::eye_show_btn_Click);
		// 
		// SIGN_UP
		// 
		this->AcceptButton = this->sign_up_enter_btn;
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
		this->BackColor = System::Drawing::Color::CadetBlue;
		this->CancelButton = this->sign_up_close_btn;
		this->ClientSize = System::Drawing::Size(600, 500);
		this->Controls->Add(this->eye_show_btn);
		this->Controls->Add(this->eye_hide_btn);
		this->Controls->Add(this->sign_up_pswd_textBox);
		this->Controls->Add(this->sign_up_login_textBox);
		this->Controls->Add(this->sign_up_label_pswd);
		this->Controls->Add(this->sign_up_login_label);
		this->Controls->Add(this->sign_up_clear_btn);
		this->Controls->Add(this->sign_up_label_C2);
		this->Controls->Add(this->sign_up_label_E1);
		this->Controls->Add(this->sign_up_label_I2);
		this->Controls->Add(this->sign_up_label_V);
		this->Controls->Add(this->sign_up_label_R);
		this->Controls->Add(this->sign_up_label_E2);
		this->Controls->Add(this->sign_up_label_S);
		this->Controls->Add(this->sign_up_label_A);
		this->Controls->Add(this->sign_up_label_M);
		this->Controls->Add(this->sign_up_label_E);
		this->Controls->Add(this->sign_up_label_N);
		this->Controls->Add(this->sign_up_label_I);
		this->Controls->Add(this->sign_up_label_C);
		this->Controls->Add(this->sign_up_main_label);
		this->Controls->Add(this->sign_up_enter_btn);
		this->Controls->Add(this->sign_up_close_btn);
		this->DoubleBuffered = true;
		this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
		this->MaximumSize = System::Drawing::Size(600, 500);
		this->MinimumSize = System::Drawing::Size(600, 500);
		this->Name = L"SIGN_UP";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"SIGN UP";
		this->ResumeLayout(false);
		this->PerformLayout();
	}
	System::Void SIGN_UP::sign_up_close_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
		this->parent_log_in_form->Show();
	}
	System::Void SIGN_UP::sign_up_clear_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->sign_up_login_textBox->Text = L"";
		this->sign_up_pswd_textBox->Text = L"";
	}
	System::Void SIGN_UP::sign_up_enter_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ loginUser = this->sign_up_login_textBox->Text;
		String^ pswdUser = this->sign_up_pswd_textBox->Text;
		Boolean true_loginUser{ true };
		for (int i{}; i < loginUser->Length; i++)
		{
			if (loginUser[i] >= '0' && loginUser[i] <= '9' || loginUser[i] >= 'а' && loginUser[i] <= 'я' || loginUser[i] >= 'А' && loginUser[i] <= 'Я' || 
				loginUser[i] >= 'a' && loginUser[i] <= 'z' || loginUser[i] >= 'A' && loginUser[i] <= 'Z' || loginUser[i] == '-' || loginUser[i] == '_')
			{
				continue;
			}
			else
			{
				true_loginUser = false;
				break;
			}
		}
		if (true_loginUser)
		{
			if (loginUser->Length < 5 || loginUser->Length > 20 || pswdUser->Length < 5 || pswdUser->Length > 20)
				MessageBox::Show("Длина логина должна быть от 5 до 20 знаков, как и длина пароля.", "Ошибка! Неверная длина логина и/или пароля.", MessageBoxButtons::OK, MessageBoxIcon::Information);
			else
			{
				DataBaseQueries^ queryDB = gcnew DataBaseQueries();
				if (queryDB->checkNewUserAccount(loginUser) && queryDB->addNewUserAccountData(loginUser, pswdUser))
				{
					this->Close();
					this->parent_log_in_form->Show();
				}
			}
		}
		else
			MessageBox::Show("Логин должен состоять из букв русского или латинского алфаваита, цифр и/или символов '_' и '-'!", "Ошибка логина!", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	System::Void SIGN_UP::eye_hide_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->sign_up_pswd_textBox->UseSystemPasswordChar = true;
		this->eye_hide_btn->Visible = false;
		this->eye_show_btn->Visible = true;
	}
	System::Void SIGN_UP::eye_show_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->sign_up_pswd_textBox->UseSystemPasswordChar = false;
		this->eye_show_btn->Visible = false;
		this->eye_hide_btn->Visible = true;
	}
}