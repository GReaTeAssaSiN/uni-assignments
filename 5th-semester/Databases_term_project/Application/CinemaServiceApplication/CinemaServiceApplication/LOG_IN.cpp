#include "LOG_IN.h"
#include "SIGN_UP.h"

namespace CinemaServiceApplication
{
	LOG_IN::LOG_IN(void)
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}
	LOG_IN::~LOG_IN()
	{
		if (components)
		{
			delete components;
		}
	}
	void LOG_IN::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LOG_IN::typeid));
		this->log_in_enter_btn = (gcnew System::Windows::Forms::Button());
		this->log_in_close_btn = (gcnew System::Windows::Forms::Button());
		this->log_in_label_C = (gcnew System::Windows::Forms::Label());
		this->log_in_main_label = (gcnew System::Windows::Forms::Label());
		this->log_in_label_I = (gcnew System::Windows::Forms::Label());
		this->log_in_label_N = (gcnew System::Windows::Forms::Label());
		this->log_in_label_E = (gcnew System::Windows::Forms::Label());
		this->log_in_label_M = (gcnew System::Windows::Forms::Label());
		this->log_in_label_A = (gcnew System::Windows::Forms::Label());
		this->log_in_label_S = (gcnew System::Windows::Forms::Label());
		this->log_in_label_E2 = (gcnew System::Windows::Forms::Label());
		this->log_in_label_R = (gcnew System::Windows::Forms::Label());
		this->log_in_label_V = (gcnew System::Windows::Forms::Label());
		this->log_in_label_I2 = (gcnew System::Windows::Forms::Label());
		this->log_in_label_E1 = (gcnew System::Windows::Forms::Label());
		this->log_in_label_C2 = (gcnew System::Windows::Forms::Label());
		this->log_in_login_label = (gcnew System::Windows::Forms::Label());
		this->log_in_label_pswd = (gcnew System::Windows::Forms::Label());
		this->log_in_login_textBox = (gcnew System::Windows::Forms::TextBox());
		this->log_in_pswd_textBox = (gcnew System::Windows::Forms::TextBox());
		this->eye_hide_btn = (gcnew System::Windows::Forms::Button());
		this->log_in_clear_btn = (gcnew System::Windows::Forms::Button());
		this->log_in_link_label = (gcnew System::Windows::Forms::LinkLabel());
		this->eye_show_btn = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// log_in_enter_btn
		// 
		this->log_in_enter_btn->BackColor = System::Drawing::Color::Azure;
		this->log_in_enter_btn->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaptionText;
		this->log_in_enter_btn->FlatAppearance->BorderSize = 2;
		this->log_in_enter_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Teal;
		this->log_in_enter_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SpringGreen;
		resources->ApplyResources(this->log_in_enter_btn, L"log_in_enter_btn");
		this->log_in_enter_btn->Name = L"log_in_enter_btn";
		this->log_in_enter_btn->UseVisualStyleBackColor = false;
		this->log_in_enter_btn->Click += gcnew System::EventHandler(this, &LOG_IN::log_in_enter_btn_Click);
		// 
		// log_in_close_btn
		// 
		this->log_in_close_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		resources->ApplyResources(this->log_in_close_btn, L"log_in_close_btn");
		this->log_in_close_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->log_in_close_btn->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
		this->log_in_close_btn->FlatAppearance->BorderSize = 3;
		this->log_in_close_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Maroon;
		this->log_in_close_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->log_in_close_btn->Name = L"log_in_close_btn";
		this->log_in_close_btn->UseVisualStyleBackColor = false;
		this->log_in_close_btn->Click += gcnew System::EventHandler(this, &LOG_IN::log_in_close_btn_Click);
		// 
		// log_in_label_C
		// 
		this->log_in_label_C->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_C->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_C, L"log_in_label_C");
		this->log_in_label_C->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->log_in_label_C->Name = L"log_in_label_C";
		// 
		// log_in_main_label
		// 
		this->log_in_main_label->BackColor = System::Drawing::Color::LightBlue;
		this->log_in_main_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->log_in_main_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_main_label, L"log_in_main_label");
		this->log_in_main_label->ForeColor = System::Drawing::SystemColors::ControlText;
		this->log_in_main_label->Name = L"log_in_main_label";
		// 
		// log_in_label_I
		// 
		this->log_in_label_I->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_I->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_I, L"log_in_label_I");
		this->log_in_label_I->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(29)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->log_in_label_I->Name = L"log_in_label_I";
		// 
		// log_in_label_N
		// 
		this->log_in_label_N->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_N->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_N, L"log_in_label_N");
		this->log_in_label_N->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(101)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->log_in_label_N->Name = L"log_in_label_N";
		// 
		// log_in_label_E
		// 
		this->log_in_label_E->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_E->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_E, L"log_in_label_E");
		this->log_in_label_E->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
			static_cast<System::Int32>(static_cast<System::Byte>(235)));
		this->log_in_label_E->Name = L"log_in_label_E";
		// 
		// log_in_label_M
		// 
		this->log_in_label_M->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_M->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_M, L"log_in_label_M");
		this->log_in_label_M->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(234)));
		this->log_in_label_M->Name = L"log_in_label_M";
		// 
		// log_in_label_A
		// 
		this->log_in_label_A->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_A->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_A, L"log_in_label_A");
		this->log_in_label_A->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(24)),
			static_cast<System::Int32>(static_cast<System::Byte>(119)));
		this->log_in_label_A->Name = L"log_in_label_A";
		// 
		// log_in_label_S
		// 
		this->log_in_label_S->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_S->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_S, L"log_in_label_S");
		this->log_in_label_S->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(27)),
			static_cast<System::Int32>(static_cast<System::Byte>(23)));
		this->log_in_label_S->Name = L"log_in_label_S";
		// 
		// log_in_label_E2
		// 
		this->log_in_label_E2->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_E2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_E2, L"log_in_label_E2");
		this->log_in_label_E2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
			static_cast<System::Int32>(static_cast<System::Byte>(23)));
		this->log_in_label_E2->Name = L"log_in_label_E2";
		// 
		// log_in_label_R
		// 
		this->log_in_label_R->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_R->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_R, L"log_in_label_R");
		this->log_in_label_R->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(88)),
			static_cast<System::Int32>(static_cast<System::Byte>(21)));
		this->log_in_label_R->Name = L"log_in_label_R";
		// 
		// log_in_label_V
		// 
		this->log_in_label_V->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_V->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_V, L"log_in_label_V");
		this->log_in_label_V->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
			static_cast<System::Int32>(static_cast<System::Byte>(25)));
		this->log_in_label_V->Name = L"log_in_label_V";
		// 
		// log_in_label_I2
		// 
		this->log_in_label_I2->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_I2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_I2, L"log_in_label_I2");
		this->log_in_label_I2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(188)),
			static_cast<System::Int32>(static_cast<System::Byte>(29)));
		this->log_in_label_I2->Name = L"log_in_label_I2";
		// 
		// log_in_label_E1
		// 
		this->log_in_label_E1->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_E1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_E1, L"log_in_label_E1");
		this->log_in_label_E1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(119)), static_cast<System::Int32>(static_cast<System::Byte>(235)),
			static_cast<System::Int32>(static_cast<System::Byte>(30)));
		this->log_in_label_E1->Name = L"log_in_label_E1";
		// 
		// log_in_label_C2
		// 
		this->log_in_label_C2->BackColor = System::Drawing::Color::Indigo;
		this->log_in_label_C2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_C2, L"log_in_label_C2");
		this->log_in_label_C2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(235)),
			static_cast<System::Int32>(static_cast<System::Byte>(31)));
		this->log_in_label_C2->Name = L"log_in_label_C2";
		// 
		// log_in_login_label
		// 
		this->log_in_login_label->BackColor = System::Drawing::Color::Transparent;
		this->log_in_login_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_login_label, L"log_in_login_label");
		this->log_in_login_label->Name = L"log_in_login_label";
		// 
		// log_in_label_pswd
		// 
		this->log_in_label_pswd->BackColor = System::Drawing::Color::Transparent;
		this->log_in_label_pswd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		resources->ApplyResources(this->log_in_label_pswd, L"log_in_label_pswd");
		this->log_in_label_pswd->Name = L"log_in_label_pswd";
		// 
		// log_in_login_textBox
		// 
		resources->ApplyResources(this->log_in_login_textBox, L"log_in_login_textBox");
		this->log_in_login_textBox->Name = L"log_in_login_textBox";
		// 
		// log_in_pswd_textBox
		// 
		resources->ApplyResources(this->log_in_pswd_textBox, L"log_in_pswd_textBox");
		this->log_in_pswd_textBox->Name = L"log_in_pswd_textBox";
		this->log_in_pswd_textBox->UseSystemPasswordChar = true;
		// 
		// eye_hide_btn
		// 
		this->eye_hide_btn->BackColor = System::Drawing::Color::Transparent;
		resources->ApplyResources(this->eye_hide_btn, L"eye_hide_btn");
		this->eye_hide_btn->Name = L"eye_hide_btn";
		this->eye_hide_btn->UseVisualStyleBackColor = false;
		this->eye_hide_btn->Click += gcnew System::EventHandler(this, &LOG_IN::eye_hide_btn_Click);
		// 
		// log_in_clear_btn
		// 
		this->log_in_clear_btn->BackColor = System::Drawing::Color::DodgerBlue;
		this->log_in_clear_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->log_in_clear_btn->FlatAppearance->BorderColor = System::Drawing::Color::Navy;
		this->log_in_clear_btn->FlatAppearance->BorderSize = 2;
		this->log_in_clear_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkSlateGray;
		this->log_in_clear_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		resources->ApplyResources(this->log_in_clear_btn, L"log_in_clear_btn");
		this->log_in_clear_btn->ForeColor = System::Drawing::Color::White;
		this->log_in_clear_btn->Name = L"log_in_clear_btn";
		this->log_in_clear_btn->UseVisualStyleBackColor = false;
		this->log_in_clear_btn->Click += gcnew System::EventHandler(this, &LOG_IN::log_in_clear_btn_Click);
		// 
		// log_in_link_label
		// 
		this->log_in_link_label->ActiveLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->log_in_link_label->BackColor = System::Drawing::Color::Transparent;
		this->log_in_link_label->DisabledLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
		resources->ApplyResources(this->log_in_link_label, L"log_in_link_label");
		this->log_in_link_label->ForeColor = System::Drawing::SystemColors::ControlText;
		this->log_in_link_label->Name = L"log_in_link_label";
		this->log_in_link_label->TabStop = true;
		this->log_in_link_label->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &LOG_IN::log_in_link_label_LinkClicked);
		// 
		// eye_show_btn
		// 
		this->eye_show_btn->BackColor = System::Drawing::Color::Transparent;
		resources->ApplyResources(this->eye_show_btn, L"eye_show_btn");
		this->eye_show_btn->Name = L"eye_show_btn";
		this->eye_show_btn->UseVisualStyleBackColor = false;
		this->eye_show_btn->Click += gcnew System::EventHandler(this, &LOG_IN::eye_show_btn_Click);
		// 
		// LOG_IN
		// 
		this->AcceptButton = this->log_in_enter_btn;
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(171)),
			static_cast<System::Int32>(static_cast<System::Byte>(175)));
		this->CancelButton = this->log_in_close_btn;
		resources->ApplyResources(this, L"$this");
		this->Controls->Add(this->log_in_link_label);
		this->Controls->Add(this->log_in_clear_btn);
		this->Controls->Add(this->eye_show_btn);
		this->Controls->Add(this->eye_hide_btn);
		this->Controls->Add(this->log_in_pswd_textBox);
		this->Controls->Add(this->log_in_login_textBox);
		this->Controls->Add(this->log_in_label_pswd);
		this->Controls->Add(this->log_in_login_label);
		this->Controls->Add(this->log_in_label_C2);
		this->Controls->Add(this->log_in_label_E1);
		this->Controls->Add(this->log_in_label_I2);
		this->Controls->Add(this->log_in_label_V);
		this->Controls->Add(this->log_in_label_R);
		this->Controls->Add(this->log_in_label_E2);
		this->Controls->Add(this->log_in_label_S);
		this->Controls->Add(this->log_in_label_A);
		this->Controls->Add(this->log_in_label_M);
		this->Controls->Add(this->log_in_label_E);
		this->Controls->Add(this->log_in_label_N);
		this->Controls->Add(this->log_in_label_I);
		this->Controls->Add(this->log_in_main_label);
		this->Controls->Add(this->log_in_label_C);
		this->Controls->Add(this->log_in_close_btn);
		this->Controls->Add(this->log_in_enter_btn);
		this->DoubleBuffered = true;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->KeyPreview = true;
		this->Name = L"LOG_IN";
		this->ResumeLayout(false);
		this->PerformLayout();
	}
	System::Void LOG_IN::log_in_close_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	System::Void LOG_IN::log_in_enter_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ userLogin = this->log_in_login_textBox->Text;
		String^ userPswd = this->log_in_pswd_textBox->Text;
		DataBaseQueries^ queryDB = gcnew DataBaseQueries();
		if (queryDB->logInUserAccount(userLogin, userPswd))
		{
			if (queryDB->checkLogInAdminAccount(userLogin, userPswd) == false)
			{
				CinemaService^ cinema_service_form = gcnew CinemaService(this->log_in_login_textBox->Text);
				this->Hide();
				cinema_service_form->ShowDialog();
				this->Show();
			}
			else
			{
				AdminPanelCinemaService^ adm_p_form = gcnew AdminPanelCinemaService(this->log_in_login_textBox->Text);
				this->Hide();
				adm_p_form->ShowDialog();
				this->Show();
			}
		}
	}
	System::Void LOG_IN::log_in_clear_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->log_in_login_textBox->Text = L"";
		this->log_in_pswd_textBox->Text = L"";
	}
	System::Void LOG_IN::eye_hide_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->log_in_pswd_textBox->UseSystemPasswordChar = true;
		this->eye_hide_btn->Visible = false;
		this->eye_show_btn->Visible = true;
	}
	System::Void LOG_IN::eye_show_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->log_in_pswd_textBox->UseSystemPasswordChar = false;
		this->eye_show_btn->Visible = false;
		this->eye_hide_btn->Visible = true;
	}
	System::Void LOG_IN::log_in_link_label_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
	{
		SIGN_UP^ sign_up_form = gcnew SIGN_UP(this);
		this->Hide();
		sign_up_form->ShowDialog();
		this->Show();
	}
}