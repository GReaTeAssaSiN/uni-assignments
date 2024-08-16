#include "AdminPanelCinemaService.h"

namespace CinemaServiceApplication
{
	AdminPanelCinemaService::AdminPanelCinemaService(void)
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}
	AdminPanelCinemaService::AdminPanelCinemaService(String^ userLogin)
	{
		InitializeComponent();
		this->adminLogin = userLogin;
	}
	AdminPanelCinemaService::~AdminPanelCinemaService()
	{
		if (components)
		{
			delete components;
		}
	}
	void AdminPanelCinemaService::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AdminPanelCinemaService::typeid));
		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		this->admin_close_btn = (gcnew System::Windows::Forms::Button());
		this->admin_label = (gcnew System::Windows::Forms::Label());
		this->admin_fromBtn_submain_panel = (gcnew System::Windows::Forms::Panel());
		this->func_btns_panel = (gcnew System::Windows::Forms::Panel());
		this->delete_data_btn = (gcnew System::Windows::Forms::Button());
		this->add_data_btn = (gcnew System::Windows::Forms::Button());
		this->apply_data_btn = (gcnew System::Windows::Forms::Button());
		this->update_data_btn = (gcnew System::Windows::Forms::Button());
		this->clear_data_btn = (gcnew System::Windows::Forms::Button());
		this->change_data_panel = (gcnew System::Windows::Forms::Panel());
		this->info_DataGridView = (gcnew System::Windows::Forms::DataGridView());
		this->contactInf_textBox = (gcnew System::Windows::Forms::TextBox());
		this->contactInf_label = (gcnew System::Windows::Forms::Label());
		this->street_textBox = (gcnew System::Windows::Forms::TextBox());
		this->city_textBox = (gcnew System::Windows::Forms::TextBox());
		this->houseDescr_textBox = (gcnew System::Windows::Forms::TextBox());
		this->cinemaName_textBox = (gcnew System::Windows::Forms::TextBox());
		this->houseNumber_textBox = (gcnew System::Windows::Forms::TextBox());
		this->cinemaPicture_textBox = (gcnew System::Windows::Forms::TextBox());
		this->closingTime_label = (gcnew System::Windows::Forms::Label());
		this->cinemaID_textBox = (gcnew System::Windows::Forms::TextBox());
		this->openingTime_label = (gcnew System::Windows::Forms::Label());
		this->street_label = (gcnew System::Windows::Forms::Label());
		this->houseDescr_label = (gcnew System::Windows::Forms::Label());
		this->city_label = (gcnew System::Windows::Forms::Label());
		this->houseLetter_label = (gcnew System::Windows::Forms::Label());
		this->cinemaName_label = (gcnew System::Windows::Forms::Label());
		this->houseNumber_label = (gcnew System::Windows::Forms::Label());
		this->cinemaPicture_label = (gcnew System::Windows::Forms::Label());
		this->cinemaID_label = (gcnew System::Windows::Forms::Label());
		this->cinemaName_comboBox = (gcnew System::Windows::Forms::ComboBox());
		this->movieFormat_comboBox = (gcnew System::Windows::Forms::ComboBox());
		this->release_textBox = (gcnew System::Windows::Forms::MaskedTextBox());
		this->ageLimit_textBox = (gcnew System::Windows::Forms::MaskedTextBox());
		this->duration_textBox = (gcnew System::Windows::Forms::MaskedTextBox());
		this->forMovieCinemaName_label = (gcnew System::Windows::Forms::Label());
		this->movieFormat_label = (gcnew System::Windows::Forms::Label());
		this->duration_label = (gcnew System::Windows::Forms::Label());
		this->genre_textBox = (gcnew System::Windows::Forms::TextBox());
		this->movieName_textBox = (gcnew System::Windows::Forms::TextBox());
		this->movieID_textBox = (gcnew System::Windows::Forms::TextBox());
		this->ageLimit_label = (gcnew System::Windows::Forms::Label());
		this->genre_label = (gcnew System::Windows::Forms::Label());
		this->release_label = (gcnew System::Windows::Forms::Label());
		this->movieName_label = (gcnew System::Windows::Forms::Label());
		this->movieID_label = (gcnew System::Windows::Forms::Label());
		this->userID_textBox = (gcnew System::Windows::Forms::TextBox());
		this->userLogin_textBox = (gcnew System::Windows::Forms::TextBox());
		this->userID_label = (gcnew System::Windows::Forms::Label());
		this->userRole_label = (gcnew System::Windows::Forms::Label());
		this->userPswd_label = (gcnew System::Windows::Forms::Label());
		this->userLogin_label = (gcnew System::Windows::Forms::Label());
		this->admin_submain_btn_panel = (gcnew System::Windows::Forms::Panel());
		this->admin_info_text = (gcnew System::Windows::Forms::TextBox());
		this->change_review_btn = (gcnew System::Windows::Forms::Button());
		this->change_movie_btn = (gcnew System::Windows::Forms::Button());
		this->change_cinema_btn = (gcnew System::Windows::Forms::Button());
		this->change_user_btn = (gcnew System::Windows::Forms::Button());
		this->userPswd_textBox = (gcnew System::Windows::Forms::TextBox());
		this->userRole_comboBox = (gcnew System::Windows::Forms::ComboBox());
		this->openingTime_textBox = (gcnew System::Windows::Forms::MaskedTextBox());
		this->closingTime_textBox = (gcnew System::Windows::Forms::MaskedTextBox());
		this->houseLetter_textBox = (gcnew System::Windows::Forms::TextBox());
		this->reviewID_label = (gcnew System::Windows::Forms::Label());
		this->comment_label = (gcnew System::Windows::Forms::Label());
		this->reviewID_textBox = (gcnew System::Windows::Forms::TextBox());
		this->comment_textBox = (gcnew System::Windows::Forms::TextBox());
		this->admin_fromBtn_submain_panel->SuspendLayout();
		this->func_btns_panel->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->info_DataGridView))->BeginInit();
		this->admin_submain_btn_panel->SuspendLayout();
		this->SuspendLayout();
		// 
		// admin_close_btn
		// 
		this->admin_close_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->admin_close_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"admin_close_btn.BackgroundImage")));
		this->admin_close_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->admin_close_btn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->admin_close_btn->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
		this->admin_close_btn->FlatAppearance->BorderSize = 3;
		this->admin_close_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Maroon;
		this->admin_close_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(94)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->admin_close_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->admin_close_btn->Location = System::Drawing::Point(1450, 0);
		this->admin_close_btn->Name = L"admin_close_btn";
		this->admin_close_btn->Size = System::Drawing::Size(50, 50);
		this->admin_close_btn->TabIndex = 0;
		this->admin_close_btn->UseVisualStyleBackColor = false;
		this->admin_close_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::admin_close_btn_Click);
		// 
		// admin_label
		// 
		this->admin_label->BackColor = System::Drawing::Color::DarkSlateGray;
		this->admin_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->admin_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->admin_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->admin_label->ForeColor = System::Drawing::Color::Transparent;
		this->admin_label->Location = System::Drawing::Point(0, 0);
		this->admin_label->MaximumSize = System::Drawing::Size(1450, 50);
		this->admin_label->MinimumSize = System::Drawing::Size(1450, 50);
		this->admin_label->Name = L"admin_label";
		this->admin_label->Size = System::Drawing::Size(1450, 50);
		this->admin_label->TabIndex = 1;
		this->admin_label->Text = L"АДМИНИСТРИРОВАНИЕ БАЗЫ ДАННЫХ CinemaService";
		this->admin_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// admin_fromBtn_submain_panel
		// 
		this->admin_fromBtn_submain_panel->BackColor = System::Drawing::Color::Silver;
		this->admin_fromBtn_submain_panel->Controls->Add(this->func_btns_panel);
		this->admin_fromBtn_submain_panel->Controls->Add(this->change_data_panel);
		this->admin_fromBtn_submain_panel->Controls->Add(this->info_DataGridView);
		this->admin_fromBtn_submain_panel->Location = System::Drawing::Point(300, 50);
		this->admin_fromBtn_submain_panel->MaximumSize = System::Drawing::Size(1200, 670);
		this->admin_fromBtn_submain_panel->MinimumSize = System::Drawing::Size(1200, 670);
		this->admin_fromBtn_submain_panel->Name = L"admin_fromBtn_submain_panel";
		this->admin_fromBtn_submain_panel->Size = System::Drawing::Size(1200, 670);
		this->admin_fromBtn_submain_panel->TabIndex = 2;
		// 
		// func_btns_panel
		// 
		this->func_btns_panel->Controls->Add(this->delete_data_btn);
		this->func_btns_panel->Controls->Add(this->add_data_btn);
		this->func_btns_panel->Controls->Add(this->apply_data_btn);
		this->func_btns_panel->Controls->Add(this->update_data_btn);
		this->func_btns_panel->Controls->Add(this->clear_data_btn);
		this->func_btns_panel->Location = System::Drawing::Point(1150, 6);
		this->func_btns_panel->Name = L"func_btns_panel";
		this->func_btns_panel->Size = System::Drawing::Size(47, 238);
		this->func_btns_panel->TabIndex = 6;
		// 
		// delete_data_btn
		// 
		this->delete_data_btn->BackColor = System::Drawing::Color::LightCoral;
		this->delete_data_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"delete_data_btn.BackgroundImage")));
		this->delete_data_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->delete_data_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->delete_data_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->delete_data_btn->FlatAppearance->BorderSize = 2;
		this->delete_data_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::IndianRed;
		this->delete_data_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
		this->delete_data_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->delete_data_btn->Location = System::Drawing::Point(3, 3);
		this->delete_data_btn->Name = L"delete_data_btn";
		this->delete_data_btn->Size = System::Drawing::Size(40, 40);
		this->delete_data_btn->TabIndex = 1;
		this->delete_data_btn->UseVisualStyleBackColor = false;
		this->delete_data_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::delete_data_btn_Click);
		// 
		// add_data_btn
		// 
		this->add_data_btn->BackColor = System::Drawing::Color::LightGreen;
		this->add_data_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"add_data_btn.BackgroundImage")));
		this->add_data_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->add_data_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->add_data_btn->FlatAppearance->BorderColor = System::Drawing::Color::LimeGreen;
		this->add_data_btn->FlatAppearance->BorderSize = 2;
		this->add_data_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MediumSpringGreen;
		this->add_data_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::PaleGreen;
		this->add_data_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->add_data_btn->Location = System::Drawing::Point(3, 49);
		this->add_data_btn->Name = L"add_data_btn";
		this->add_data_btn->Size = System::Drawing::Size(40, 40);
		this->add_data_btn->TabIndex = 4;
		this->add_data_btn->UseVisualStyleBackColor = false;
		this->add_data_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::add_data_btn_Click);
		// 
		// apply_data_btn
		// 
		this->apply_data_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->apply_data_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"apply_data_btn.BackgroundImage")));
		this->apply_data_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->apply_data_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->apply_data_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->apply_data_btn->FlatAppearance->BorderSize = 2;
		this->apply_data_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
			static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
		this->apply_data_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::PaleGreen;
		this->apply_data_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->apply_data_btn->Location = System::Drawing::Point(3, 141);
		this->apply_data_btn->Name = L"apply_data_btn";
		this->apply_data_btn->Size = System::Drawing::Size(40, 40);
		this->apply_data_btn->TabIndex = 2;
		this->apply_data_btn->UseVisualStyleBackColor = false;
		this->apply_data_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::apply_data_btn_Click);
		// 
		// update_data_btn
		// 
		this->update_data_btn->BackColor = System::Drawing::Color::PowderBlue;
		this->update_data_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"update_data_btn.BackgroundImage")));
		this->update_data_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->update_data_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->update_data_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->update_data_btn->FlatAppearance->BorderSize = 2;
		this->update_data_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
		this->update_data_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSkyBlue;
		this->update_data_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->update_data_btn->Location = System::Drawing::Point(3, 95);
		this->update_data_btn->Name = L"update_data_btn";
		this->update_data_btn->Size = System::Drawing::Size(40, 40);
		this->update_data_btn->TabIndex = 3;
		this->update_data_btn->UseVisualStyleBackColor = false;
		this->update_data_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::update_data_btn_Click);
		// 
		// clear_data_btn
		// 
		this->clear_data_btn->BackColor = System::Drawing::Color::DodgerBlue;
		this->clear_data_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->clear_data_btn->FlatAppearance->BorderColor = System::Drawing::Color::Navy;
		this->clear_data_btn->FlatAppearance->BorderSize = 2;
		this->clear_data_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkSlateGray;
		this->clear_data_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->clear_data_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->clear_data_btn->ForeColor = System::Drawing::Color::White;
		this->clear_data_btn->Location = System::Drawing::Point(3, 187);
		this->clear_data_btn->Name = L"clear_data_btn";
		this->clear_data_btn->Size = System::Drawing::Size(40, 40);
		this->clear_data_btn->TabIndex = 1;
		this->clear_data_btn->Text = L"CLEAR";
		this->clear_data_btn->UseVisualStyleBackColor = false;
		this->clear_data_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::clear_data_btn_Click);
		// 
		// change_data_panel
		// 
		this->change_data_panel->BackColor = System::Drawing::Color::White;
		this->change_data_panel->Location = System::Drawing::Point(5, 5);
		this->change_data_panel->Name = L"change_data_panel";
		this->change_data_panel->Size = System::Drawing::Size(1144, 239);
		this->change_data_panel->TabIndex = 5;
		// 
		// info_DataGridView
		// 
		this->info_DataGridView->AllowUserToAddRows = false;
		this->info_DataGridView->AllowUserToDeleteRows = false;
		this->info_DataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->info_DataGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
		this->info_DataGridView->BackgroundColor = System::Drawing::SystemColors::ControlLight;
		this->info_DataGridView->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Sunken;
		this->info_DataGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Sunken;
		dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
		dataGridViewCellStyle1->BackColor = System::Drawing::Color::DarkCyan;
		dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		dataGridViewCellStyle1->ForeColor = System::Drawing::Color::MediumSpringGreen;
		dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::LightSeaGreen;
		dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
		dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
		this->info_DataGridView->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
		this->info_DataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		this->info_DataGridView->Cursor = System::Windows::Forms::Cursors::IBeam;
		this->info_DataGridView->EnableHeadersVisualStyles = false;
		this->info_DataGridView->GridColor = System::Drawing::Color::DarkOliveGreen;
		this->info_DataGridView->Location = System::Drawing::Point(5, 250);
		this->info_DataGridView->MaximumSize = System::Drawing::Size(1190, 415);
		this->info_DataGridView->MinimumSize = System::Drawing::Size(1190, 415);
		this->info_DataGridView->Name = L"info_DataGridView";
		this->info_DataGridView->ReadOnly = true;
		this->info_DataGridView->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Sunken;
		dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
		dataGridViewCellStyle2->BackColor = System::Drawing::Color::DarkCyan;
		dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::LightSeaGreen;
		dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
		dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
		this->info_DataGridView->RowHeadersDefaultCellStyle = dataGridViewCellStyle2;
		this->info_DataGridView->RowHeadersWidth = 50;
		dataGridViewCellStyle3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		dataGridViewCellStyle3->ForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::Green;
		dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::White;
		this->info_DataGridView->RowsDefaultCellStyle = dataGridViewCellStyle3;
		this->info_DataGridView->RowTemplate->Height = 50;
		this->info_DataGridView->RowTemplate->ReadOnly = true;
		this->info_DataGridView->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->info_DataGridView->Size = System::Drawing::Size(1190, 415);
		this->info_DataGridView->TabIndex = 0;
		// 
		// contactInf_textBox
		// 
		this->contactInf_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->contactInf_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->contactInf_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->contactInf_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->contactInf_textBox->Location = System::Drawing::Point(921, 97);
		this->contactInf_textBox->MaxLength = 100;
		this->contactInf_textBox->Name = L"contactInf_textBox";
		this->contactInf_textBox->Size = System::Drawing::Size(204, 24);
		this->contactInf_textBox->TabIndex = 21;
		// 
		// contactInf_label
		// 
		this->contactInf_label->BackColor = System::Drawing::Color::Transparent;
		this->contactInf_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->contactInf_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->contactInf_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->contactInf_label->Location = System::Drawing::Point(763, 97);
		this->contactInf_label->Name = L"contactInf_label";
		this->contactInf_label->Size = System::Drawing::Size(135, 25);
		this->contactInf_label->TabIndex = 20;
		this->contactInf_label->Text = L"ContactInf:";
		this->contactInf_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// street_textBox
		// 
		this->street_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->street_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->street_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->street_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->street_textBox->Location = System::Drawing::Point(168, 188);
		this->street_textBox->MaxLength = 30;
		this->street_textBox->Name = L"street_textBox";
		this->street_textBox->Size = System::Drawing::Size(204, 24);
		this->street_textBox->TabIndex = 9;
		// 
		// city_textBox
		// 
		this->city_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->city_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->city_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->city_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->city_textBox->Location = System::Drawing::Point(168, 142);
		this->city_textBox->MaxLength = 30;
		this->city_textBox->Name = L"city_textBox";
		this->city_textBox->Size = System::Drawing::Size(204, 24);
		this->city_textBox->TabIndex = 8;
		// 
		// houseDescr_textBox
		// 
		this->houseDescr_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->houseDescr_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->houseDescr_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseDescr_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->houseDescr_textBox->Location = System::Drawing::Point(547, 98);
		this->houseDescr_textBox->MaxLength = 20;
		this->houseDescr_textBox->Name = L"houseDescr_textBox";
		this->houseDescr_textBox->Size = System::Drawing::Size(204, 24);
		this->houseDescr_textBox->TabIndex = 17;
		// 
		// cinemaName_textBox
		// 
		this->cinemaName_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->cinemaName_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->cinemaName_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaName_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->cinemaName_textBox->Location = System::Drawing::Point(168, 96);
		this->cinemaName_textBox->MaxLength = 50;
		this->cinemaName_textBox->Name = L"cinemaName_textBox";
		this->cinemaName_textBox->Size = System::Drawing::Size(204, 24);
		this->cinemaName_textBox->TabIndex = 7;
		// 
		// houseNumber_textBox
		// 
		this->houseNumber_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->houseNumber_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->houseNumber_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseNumber_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->houseNumber_textBox->Location = System::Drawing::Point(547, 14);
		this->houseNumber_textBox->MaxLength = 5;
		this->houseNumber_textBox->Name = L"houseNumber_textBox";
		this->houseNumber_textBox->Size = System::Drawing::Size(204, 24);
		this->houseNumber_textBox->TabIndex = 15;
		// 
		// cinemaPicture_textBox
		// 
		this->cinemaPicture_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->cinemaPicture_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->cinemaPicture_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->cinemaPicture_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->cinemaPicture_textBox->Location = System::Drawing::Point(168, 55);
		this->cinemaPicture_textBox->MaxLength = 500;
		this->cinemaPicture_textBox->Name = L"cinemaPicture_textBox";
		this->cinemaPicture_textBox->Size = System::Drawing::Size(204, 24);
		this->cinemaPicture_textBox->TabIndex = 6;
		// 
		// closingTime_label
		// 
		this->closingTime_label->BackColor = System::Drawing::Color::Transparent;
		this->closingTime_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->closingTime_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->closingTime_label->ForeColor = System::Drawing::Color::Red;
		this->closingTime_label->Location = System::Drawing::Point(763, 55);
		this->closingTime_label->Name = L"closingTime_label";
		this->closingTime_label->Size = System::Drawing::Size(135, 25);
		this->closingTime_label->TabIndex = 14;
		this->closingTime_label->Text = L"*ClosingTime:";
		this->closingTime_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// cinemaID_textBox
		// 
		this->cinemaID_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->cinemaID_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->cinemaID_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaID_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->cinemaID_textBox->Location = System::Drawing::Point(168, 12);
		this->cinemaID_textBox->MaxLength = 20;
		this->cinemaID_textBox->Name = L"cinemaID_textBox";
		this->cinemaID_textBox->Size = System::Drawing::Size(204, 24);
		this->cinemaID_textBox->TabIndex = 5;
		// 
		// openingTime_label
		// 
		this->openingTime_label->BackColor = System::Drawing::Color::Transparent;
		this->openingTime_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->openingTime_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->openingTime_label->ForeColor = System::Drawing::Color::Red;
		this->openingTime_label->Location = System::Drawing::Point(763, 14);
		this->openingTime_label->Name = L"openingTime_label";
		this->openingTime_label->Size = System::Drawing::Size(135, 25);
		this->openingTime_label->TabIndex = 13;
		this->openingTime_label->Text = L"*OpeningTime:";
		this->openingTime_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// street_label
		// 
		this->street_label->BackColor = System::Drawing::Color::Transparent;
		this->street_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->street_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->street_label->ForeColor = System::Drawing::Color::Red;
		this->street_label->Location = System::Drawing::Point(10, 188);
		this->street_label->Name = L"street_label";
		this->street_label->Size = System::Drawing::Size(135, 25);
		this->street_label->TabIndex = 4;
		this->street_label->Text = L"*Street:";
		this->street_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// houseDescr_label
		// 
		this->houseDescr_label->BackColor = System::Drawing::Color::Transparent;
		this->houseDescr_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->houseDescr_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseDescr_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->houseDescr_label->Location = System::Drawing::Point(389, 98);
		this->houseDescr_label->Name = L"houseDescr_label";
		this->houseDescr_label->Size = System::Drawing::Size(135, 25);
		this->houseDescr_label->TabIndex = 12;
		this->houseDescr_label->Text = L"HouseDescr:";
		this->houseDescr_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// city_label
		// 
		this->city_label->BackColor = System::Drawing::Color::Transparent;
		this->city_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->city_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->city_label->ForeColor = System::Drawing::Color::Red;
		this->city_label->Location = System::Drawing::Point(10, 142);
		this->city_label->Name = L"city_label";
		this->city_label->Size = System::Drawing::Size(135, 25);
		this->city_label->TabIndex = 3;
		this->city_label->Text = L"*City:";
		this->city_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// houseLetter_label
		// 
		this->houseLetter_label->BackColor = System::Drawing::Color::Transparent;
		this->houseLetter_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->houseLetter_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseLetter_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->houseLetter_label->Location = System::Drawing::Point(389, 52);
		this->houseLetter_label->Name = L"houseLetter_label";
		this->houseLetter_label->Size = System::Drawing::Size(135, 25);
		this->houseLetter_label->TabIndex = 11;
		this->houseLetter_label->Text = L"HouseLetter:";
		this->houseLetter_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// cinemaName_label
		// 
		this->cinemaName_label->BackColor = System::Drawing::Color::Transparent;
		this->cinemaName_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->cinemaName_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaName_label->ForeColor = System::Drawing::Color::Red;
		this->cinemaName_label->Location = System::Drawing::Point(10, 96);
		this->cinemaName_label->Name = L"cinemaName_label";
		this->cinemaName_label->Size = System::Drawing::Size(135, 25);
		this->cinemaName_label->TabIndex = 2;
		this->cinemaName_label->Text = L"*CinemaName:";
		this->cinemaName_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// houseNumber_label
		// 
		this->houseNumber_label->BackColor = System::Drawing::Color::Transparent;
		this->houseNumber_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->houseNumber_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseNumber_label->ForeColor = System::Drawing::Color::Red;
		this->houseNumber_label->Location = System::Drawing::Point(389, 12);
		this->houseNumber_label->Name = L"houseNumber_label";
		this->houseNumber_label->Size = System::Drawing::Size(135, 25);
		this->houseNumber_label->TabIndex = 10;
		this->houseNumber_label->Text = L"*HouseNumber:";
		this->houseNumber_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// cinemaPicture_label
		// 
		this->cinemaPicture_label->BackColor = System::Drawing::Color::Transparent;
		this->cinemaPicture_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->cinemaPicture_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaPicture_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->cinemaPicture_label->Location = System::Drawing::Point(10, 50);
		this->cinemaPicture_label->Name = L"cinemaPicture_label";
		this->cinemaPicture_label->Size = System::Drawing::Size(135, 25);
		this->cinemaPicture_label->TabIndex = 1;
		this->cinemaPicture_label->Text = L"CinemaPicture:";
		this->cinemaPicture_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// cinemaID_label
		// 
		this->cinemaID_label->BackColor = System::Drawing::Color::Transparent;
		this->cinemaID_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->cinemaID_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaID_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->cinemaID_label->Location = System::Drawing::Point(10, 10);
		this->cinemaID_label->Name = L"cinemaID_label";
		this->cinemaID_label->Size = System::Drawing::Size(135, 25);
		this->cinemaID_label->TabIndex = 0;
		this->cinemaID_label->Text = L"CinemaID:";
		this->cinemaID_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// cinemaName_comboBox
		// 
		this->cinemaName_comboBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->cinemaName_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cinemaName_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->cinemaName_comboBox->FormattingEnabled = true;
		this->cinemaName_comboBox->Location = System::Drawing::Point(656, 103);
		this->cinemaName_comboBox->MaxDropDownItems = 100;
		this->cinemaName_comboBox->Name = L"cinemaName_comboBox";
		this->cinemaName_comboBox->Size = System::Drawing::Size(246, 26);
		this->cinemaName_comboBox->TabIndex = 20;
		// 
		// movieFormat_comboBox
		// 
		this->movieFormat_comboBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->movieFormat_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->movieFormat_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->movieFormat_comboBox->FormattingEnabled = true;
		this->movieFormat_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"2D", L"3D" });
		this->movieFormat_comboBox->Location = System::Drawing::Point(656, 55);
		this->movieFormat_comboBox->MaxDropDownItems = 2;
		this->movieFormat_comboBox->Name = L"movieFormat_comboBox";
		this->movieFormat_comboBox->Size = System::Drawing::Size(246, 26);
		this->movieFormat_comboBox->TabIndex = 19;
		// 
		// release_textBox
		// 
		this->release_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->release_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->release_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->release_textBox->Location = System::Drawing::Point(196, 96);
		this->release_textBox->Mask = L"00-00-0000 00:00:00";
		this->release_textBox->Name = L"release_textBox";
		this->release_textBox->Size = System::Drawing::Size(246, 24);
		this->release_textBox->TabIndex = 18;
		this->release_textBox->ValidatingType = System::DateTime::typeid;
		// 
		// ageLimit_textBox
		// 
		this->ageLimit_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->ageLimit_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->ageLimit_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->ageLimit_textBox->Location = System::Drawing::Point(196, 196);
		this->ageLimit_textBox->Mask = L"00+";
		this->ageLimit_textBox->Name = L"ageLimit_textBox";
		this->ageLimit_textBox->Size = System::Drawing::Size(246, 24);
		this->ageLimit_textBox->TabIndex = 17;
		this->ageLimit_textBox->ValidatingType = System::DateTime::typeid;
		// 
		// duration_textBox
		// 
		this->duration_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->duration_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->duration_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->duration_textBox->Location = System::Drawing::Point(656, 10);
		this->duration_textBox->Mask = L"00:00:00";
		this->duration_textBox->Name = L"duration_textBox";
		this->duration_textBox->Size = System::Drawing::Size(246, 24);
		this->duration_textBox->TabIndex = 16;
		this->duration_textBox->ValidatingType = System::DateTime::typeid;
		// 
		// forMovieCinemaName_label
		// 
		this->forMovieCinemaName_label->BackColor = System::Drawing::Color::Transparent;
		this->forMovieCinemaName_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->forMovieCinemaName_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->forMovieCinemaName_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->forMovieCinemaName_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->forMovieCinemaName_label->Location = System::Drawing::Point(471, 104);
		this->forMovieCinemaName_label->Name = L"forMovieCinemaName_label";
		this->forMovieCinemaName_label->Size = System::Drawing::Size(135, 25);
		this->forMovieCinemaName_label->TabIndex = 12;
		this->forMovieCinemaName_label->Text = L"CinemaName:";
		this->forMovieCinemaName_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// movieFormat_label
		// 
		this->movieFormat_label->BackColor = System::Drawing::Color::Transparent;
		this->movieFormat_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->movieFormat_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->movieFormat_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->movieFormat_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->movieFormat_label->Location = System::Drawing::Point(471, 56);
		this->movieFormat_label->Name = L"movieFormat_label";
		this->movieFormat_label->Size = System::Drawing::Size(135, 25);
		this->movieFormat_label->TabIndex = 11;
		this->movieFormat_label->Text = L"MovieFormat:";
		this->movieFormat_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// duration_label
		// 
		this->duration_label->BackColor = System::Drawing::Color::Transparent;
		this->duration_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->duration_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->duration_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->duration_label->ForeColor = System::Drawing::Color::Red;
		this->duration_label->Location = System::Drawing::Point(470, 10);
		this->duration_label->Name = L"duration_label";
		this->duration_label->Size = System::Drawing::Size(135, 25);
		this->duration_label->TabIndex = 10;
		this->duration_label->Text = L"*Duration:";
		this->duration_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// genre_textBox
		// 
		this->genre_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->genre_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->genre_textBox->Cursor = System::Windows::Forms::Cursors::IBeam;
		this->genre_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->genre_textBox->Location = System::Drawing::Point(196, 147);
		this->genre_textBox->MaxLength = 100;
		this->genre_textBox->Name = L"genre_textBox";
		this->genre_textBox->Size = System::Drawing::Size(246, 24);
		this->genre_textBox->TabIndex = 8;
		// 
		// movieName_textBox
		// 
		this->movieName_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->movieName_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->movieName_textBox->Cursor = System::Windows::Forms::Cursors::IBeam;
		this->movieName_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->movieName_textBox->Location = System::Drawing::Point(196, 55);
		this->movieName_textBox->MaxLength = 50;
		this->movieName_textBox->Name = L"movieName_textBox";
		this->movieName_textBox->Size = System::Drawing::Size(246, 24);
		this->movieName_textBox->TabIndex = 6;
		// 
		// movieID_textBox
		// 
		this->movieID_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->movieID_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->movieID_textBox->Cursor = System::Windows::Forms::Cursors::Default;
		this->movieID_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->movieID_textBox->Location = System::Drawing::Point(196, 10);
		this->movieID_textBox->MaxLength = 20;
		this->movieID_textBox->Name = L"movieID_textBox";
		this->movieID_textBox->Size = System::Drawing::Size(246, 24);
		this->movieID_textBox->TabIndex = 5;
		// 
		// ageLimit_label
		// 
		this->ageLimit_label->BackColor = System::Drawing::Color::Transparent;
		this->ageLimit_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->ageLimit_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->ageLimit_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->ageLimit_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->ageLimit_label->Location = System::Drawing::Point(10, 193);
		this->ageLimit_label->Name = L"ageLimit_label";
		this->ageLimit_label->Size = System::Drawing::Size(135, 25);
		this->ageLimit_label->TabIndex = 4;
		this->ageLimit_label->Text = L"AgeLimit:";
		this->ageLimit_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// genre_label
		// 
		this->genre_label->BackColor = System::Drawing::Color::Transparent;
		this->genre_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->genre_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->genre_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->genre_label->ForeColor = System::Drawing::Color::Red;
		this->genre_label->Location = System::Drawing::Point(10, 147);
		this->genre_label->Name = L"genre_label";
		this->genre_label->Size = System::Drawing::Size(135, 25);
		this->genre_label->TabIndex = 3;
		this->genre_label->Text = L"*Genre:";
		this->genre_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// release_label
		// 
		this->release_label->BackColor = System::Drawing::Color::Transparent;
		this->release_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->release_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->release_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->release_label->ForeColor = System::Drawing::Color::Red;
		this->release_label->Location = System::Drawing::Point(10, 101);
		this->release_label->Name = L"release_label";
		this->release_label->Size = System::Drawing::Size(135, 25);
		this->release_label->TabIndex = 2;
		this->release_label->Text = L"*Release:";
		this->release_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// movieName_label
		// 
		this->movieName_label->BackColor = System::Drawing::Color::Transparent;
		this->movieName_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->movieName_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->movieName_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->movieName_label->ForeColor = System::Drawing::Color::Red;
		this->movieName_label->Location = System::Drawing::Point(10, 55);
		this->movieName_label->Name = L"movieName_label";
		this->movieName_label->Size = System::Drawing::Size(135, 25);
		this->movieName_label->TabIndex = 1;
		this->movieName_label->Text = L"*MovieName:";
		this->movieName_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// movieID_label
		// 
		this->movieID_label->BackColor = System::Drawing::Color::Transparent;
		this->movieID_label->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->movieID_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->movieID_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->movieID_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->movieID_label->Location = System::Drawing::Point(10, 10);
		this->movieID_label->Name = L"movieID_label";
		this->movieID_label->Size = System::Drawing::Size(135, 25);
		this->movieID_label->TabIndex = 0;
		this->movieID_label->Text = L"MovieID:";
		this->movieID_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// userID_textBox
		// 
		this->userID_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->userID_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->userID_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userID_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->userID_textBox->Location = System::Drawing::Point(140, 10);
		this->userID_textBox->MaxLength = 20;
		this->userID_textBox->Name = L"userID_textBox";
		this->userID_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
		this->userID_textBox->Size = System::Drawing::Size(225, 24);
		this->userID_textBox->TabIndex = 3;
		// 
		// userLogin_textBox
		// 
		this->userLogin_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->userLogin_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->userLogin_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userLogin_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->userLogin_textBox->Location = System::Drawing::Point(140, 55);
		this->userLogin_textBox->MaxLength = 20;
		this->userLogin_textBox->Name = L"userLogin_textBox";
		this->userLogin_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
		this->userLogin_textBox->Size = System::Drawing::Size(225, 24);
		this->userLogin_textBox->TabIndex = 3;
		// 
		// userID_label
		// 
		this->userID_label->BackColor = System::Drawing::Color::Transparent;
		this->userID_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->userID_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userID_label->ForeColor = System::Drawing::SystemColors::ButtonShadow;
		this->userID_label->Location = System::Drawing::Point(10, 10);
		this->userID_label->Name = L"userID_label";
		this->userID_label->Size = System::Drawing::Size(125, 25);
		this->userID_label->TabIndex = 0;
		this->userID_label->Text = L"UserID:";
		// 
		// userRole_label
		// 
		this->userRole_label->BackColor = System::Drawing::Color::Transparent;
		this->userRole_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->userRole_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userRole_label->ForeColor = System::Drawing::Color::Red;
		this->userRole_label->Location = System::Drawing::Point(10, 146);
		this->userRole_label->Name = L"userRole_label";
		this->userRole_label->Size = System::Drawing::Size(125, 25);
		this->userRole_label->TabIndex = 2;
		this->userRole_label->Text = L"*UserRole:";
		// 
		// userPswd_label
		// 
		this->userPswd_label->BackColor = System::Drawing::Color::Transparent;
		this->userPswd_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->userPswd_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userPswd_label->ForeColor = System::Drawing::Color::Red;
		this->userPswd_label->Location = System::Drawing::Point(10, 101);
		this->userPswd_label->Name = L"userPswd_label";
		this->userPswd_label->Size = System::Drawing::Size(125, 25);
		this->userPswd_label->TabIndex = 1;
		this->userPswd_label->Text = L"*UserPswd:";
		// 
		// userLogin_label
		// 
		this->userLogin_label->BackColor = System::Drawing::Color::Transparent;
		this->userLogin_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->userLogin_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userLogin_label->ForeColor = System::Drawing::Color::Red;
		this->userLogin_label->Location = System::Drawing::Point(10, 55);
		this->userLogin_label->Name = L"userLogin_label";
		this->userLogin_label->Size = System::Drawing::Size(125, 25);
		this->userLogin_label->TabIndex = 0;
		this->userLogin_label->Text = L"*UserLogin:";
		// 
		// admin_submain_btn_panel
		// 
		this->admin_submain_btn_panel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->admin_submain_btn_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->admin_submain_btn_panel->Controls->Add(this->admin_info_text);
		this->admin_submain_btn_panel->Controls->Add(this->change_review_btn);
		this->admin_submain_btn_panel->Controls->Add(this->change_movie_btn);
		this->admin_submain_btn_panel->Controls->Add(this->change_cinema_btn);
		this->admin_submain_btn_panel->Controls->Add(this->change_user_btn);
		this->admin_submain_btn_panel->Location = System::Drawing::Point(0, 50);
		this->admin_submain_btn_panel->MaximumSize = System::Drawing::Size(300, 670);
		this->admin_submain_btn_panel->MinimumSize = System::Drawing::Size(300, 670);
		this->admin_submain_btn_panel->Name = L"admin_submain_btn_panel";
		this->admin_submain_btn_panel->Size = System::Drawing::Size(300, 670);
		this->admin_submain_btn_panel->TabIndex = 0;
		// 
		// admin_info_text
		// 
		this->admin_info_text->BackColor = System::Drawing::Color::Bisque;
		this->admin_info_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->admin_info_text->ForeColor = System::Drawing::SystemColors::WindowText;
		this->admin_info_text->Location = System::Drawing::Point(2, 226);
		this->admin_info_text->MaxLength = 3000;
		this->admin_info_text->Multiline = true;
		this->admin_info_text->Name = L"admin_info_text";
		this->admin_info_text->ReadOnly = true;
		this->admin_info_text->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->admin_info_text->Size = System::Drawing::Size(296, 438);
		this->admin_info_text->TabIndex = 4;
		this->admin_info_text->Text = resources->GetString(L"admin_info_text.Text");
		// 
		// change_review_btn
		// 
		this->change_review_btn->BackColor = System::Drawing::Color::WhiteSmoke;
		this->change_review_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->change_review_btn->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
		this->change_review_btn->FlatAppearance->BorderSize = 3;
		this->change_review_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
		this->change_review_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGray;
		this->change_review_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->change_review_btn->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->change_review_btn->ForeColor = System::Drawing::Color::Teal;
		this->change_review_btn->Location = System::Drawing::Point(2, 170);
		this->change_review_btn->Name = L"change_review_btn";
		this->change_review_btn->Size = System::Drawing::Size(296, 50);
		this->change_review_btn->TabIndex = 3;
		this->change_review_btn->Text = L"Комментарий";
		this->change_review_btn->UseVisualStyleBackColor = false;
		this->change_review_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::change_review_btn_Click);
		// 
		// change_movie_btn
		// 
		this->change_movie_btn->BackColor = System::Drawing::Color::WhiteSmoke;
		this->change_movie_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->change_movie_btn->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
		this->change_movie_btn->FlatAppearance->BorderSize = 3;
		this->change_movie_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
		this->change_movie_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGray;
		this->change_movie_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->change_movie_btn->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->change_movie_btn->ForeColor = System::Drawing::Color::Teal;
		this->change_movie_btn->Location = System::Drawing::Point(2, 115);
		this->change_movie_btn->Name = L"change_movie_btn";
		this->change_movie_btn->Size = System::Drawing::Size(296, 50);
		this->change_movie_btn->TabIndex = 2;
		this->change_movie_btn->Text = L"Фильм";
		this->change_movie_btn->UseVisualStyleBackColor = false;
		this->change_movie_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::change_movie_btn_Click);
		// 
		// change_cinema_btn
		// 
		this->change_cinema_btn->BackColor = System::Drawing::Color::WhiteSmoke;
		this->change_cinema_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->change_cinema_btn->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
		this->change_cinema_btn->FlatAppearance->BorderSize = 3;
		this->change_cinema_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
		this->change_cinema_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGray;
		this->change_cinema_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->change_cinema_btn->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->change_cinema_btn->ForeColor = System::Drawing::Color::Teal;
		this->change_cinema_btn->Location = System::Drawing::Point(2, 60);
		this->change_cinema_btn->Name = L"change_cinema_btn";
		this->change_cinema_btn->Size = System::Drawing::Size(296, 50);
		this->change_cinema_btn->TabIndex = 1;
		this->change_cinema_btn->Text = L"Кинотеатр";
		this->change_cinema_btn->UseVisualStyleBackColor = false;
		this->change_cinema_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::change_cinema_btn_Click);
		// 
		// change_user_btn
		// 
		this->change_user_btn->BackColor = System::Drawing::Color::WhiteSmoke;
		this->change_user_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->change_user_btn->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
		this->change_user_btn->FlatAppearance->BorderSize = 3;
		this->change_user_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
		this->change_user_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGray;
		this->change_user_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->change_user_btn->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->change_user_btn->ForeColor = System::Drawing::Color::Teal;
		this->change_user_btn->Location = System::Drawing::Point(2, 5);
		this->change_user_btn->Name = L"change_user_btn";
		this->change_user_btn->Size = System::Drawing::Size(296, 50);
		this->change_user_btn->TabIndex = 0;
		this->change_user_btn->Text = L"Пользователь";
		this->change_user_btn->UseVisualStyleBackColor = false;
		this->change_user_btn->Click += gcnew System::EventHandler(this, &AdminPanelCinemaService::change_user_btn_Click);
		// 
		// userPswd_textBox
		// 
		this->userPswd_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->userPswd_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->userPswd_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userPswd_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->userPswd_textBox->Location = System::Drawing::Point(140, 101);
		this->userPswd_textBox->MaxLength = 20;
		this->userPswd_textBox->Name = L"userPswd_textBox";
		this->userPswd_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
		this->userPswd_textBox->Size = System::Drawing::Size(225, 24);
		this->userPswd_textBox->TabIndex = 5;
		// 
		// userRole_comboBox
		// 
		this->userRole_comboBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->userRole_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->userRole_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->userRole_comboBox->FormattingEnabled = true;
		this->userRole_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Admin", L"User" });
		this->userRole_comboBox->Location = System::Drawing::Point(140, 146);
		this->userRole_comboBox->Name = L"userRole_comboBox";
		this->userRole_comboBox->Size = System::Drawing::Size(225, 26);
		this->userRole_comboBox->TabIndex = 6;
		// 
		// openingTime_textBox
		// 
		this->openingTime_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->openingTime_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->openingTime_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->openingTime_textBox->Location = System::Drawing::Point(921, 15);
		this->openingTime_textBox->Mask = L"00:00:00";
		this->openingTime_textBox->Name = L"openingTime_textBox";
		this->openingTime_textBox->Size = System::Drawing::Size(204, 24);
		this->openingTime_textBox->TabIndex = 22;
		// 
		// closingTime_textBox
		// 
		this->closingTime_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->closingTime_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->closingTime_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->closingTime_textBox->Location = System::Drawing::Point(921, 57);
		this->closingTime_textBox->Mask = L"00:00:00";
		this->closingTime_textBox->Name = L"closingTime_textBox";
		this->closingTime_textBox->Size = System::Drawing::Size(204, 24);
		this->closingTime_textBox->TabIndex = 23;
		// 
		// houseLetter_textBox
		// 
		this->houseLetter_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->houseLetter_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->houseLetter_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->houseLetter_textBox->ForeColor = System::Drawing::SystemColors::WindowText;
		this->houseLetter_textBox->Location = System::Drawing::Point(547, 57);
		this->houseLetter_textBox->MaxLength = 1;
		this->houseLetter_textBox->Name = L"houseLetter_textBox";
		this->houseLetter_textBox->Size = System::Drawing::Size(204, 24);
		this->houseLetter_textBox->TabIndex = 16;
		// 
		// reviewID_label
		// 
		this->reviewID_label->BackColor = System::Drawing::Color::Transparent;
		this->reviewID_label->Cursor = System::Windows::Forms::Cursors::Default;
		this->reviewID_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->reviewID_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->reviewID_label->ForeColor = System::Drawing::Color::Red;
		this->reviewID_label->Location = System::Drawing::Point(18, 29);
		this->reviewID_label->Name = L"reviewID_label";
		this->reviewID_label->Size = System::Drawing::Size(129, 23);
		this->reviewID_label->TabIndex = 0;
		this->reviewID_label->Text = L"*ReviewID:";
		// 
		// comment_label
		// 
		this->comment_label->BackColor = System::Drawing::Color::Transparent;
		this->comment_label->Cursor = System::Windows::Forms::Cursors::Default;
		this->comment_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->comment_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->comment_label->Location = System::Drawing::Point(18, 96);
		this->comment_label->Name = L"comment_label";
		this->comment_label->Size = System::Drawing::Size(129, 23);
		this->comment_label->TabIndex = 1;
		this->comment_label->Text = L"Comment:";
		// 
		// reviewID_textBox
		// 
		this->reviewID_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->reviewID_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->reviewID_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->reviewID_textBox->Location = System::Drawing::Point(169, 31);
		this->reviewID_textBox->MaxLength = 20;
		this->reviewID_textBox->Name = L"reviewID_textBox";
		this->reviewID_textBox->Size = System::Drawing::Size(220, 24);
		this->reviewID_textBox->TabIndex = 2;
		// 
		// comment_textBox
		// 
		this->comment_textBox->BackColor = System::Drawing::Color::WhiteSmoke;
		this->comment_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->comment_textBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->comment_textBox->Location = System::Drawing::Point(169, 91);
		this->comment_textBox->Multiline = true;
		this->comment_textBox->Name = L"comment_textBox";
		this->comment_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->comment_textBox->Size = System::Drawing::Size(942, 137);
		this->comment_textBox->TabIndex = 3;
		// 
		// AdminPanelCinemaService
		// 
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
		this->BackColor = System::Drawing::Color::Honeydew;
		this->CancelButton = this->admin_close_btn;
		this->ClientSize = System::Drawing::Size(1500, 720);
		this->Controls->Add(this->admin_submain_btn_panel);
		this->Controls->Add(this->admin_label);
		this->Controls->Add(this->admin_close_btn);
		this->DoubleBuffered = true;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->MaximumSize = System::Drawing::Size(1500, 720);
		this->MinimumSize = System::Drawing::Size(1500, 720);
		this->Name = L"AdminPanelCinemaService";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"Admin Panel for CinemaService";
		this->admin_fromBtn_submain_panel->ResumeLayout(false);
		this->func_btns_panel->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->info_DataGridView))->EndInit();
		this->admin_submain_btn_panel->ResumeLayout(false);
		this->admin_submain_btn_panel->PerformLayout();
		this->ResumeLayout(false);

	}
	System::Void AdminPanelCinemaService::admin_close_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	System::Void AdminPanelCinemaService::change_user_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			choice = 1;
			this->admin_fromBtn_submain_panel->SuspendLayout();
			this->change_data_panel->SuspendLayout();
			this->SuspendLayout();
			this->change_data_panel->Controls->Clear();
			this->change_data_panel->Controls->Add(this->userRole_comboBox);
			this->change_data_panel->Controls->Add(this->userPswd_textBox);
			this->change_data_panel->Controls->Add(this->userLogin_textBox);
			this->change_data_panel->Controls->Add(this->userID_textBox);
			this->change_data_panel->Controls->Add(this->userRole_label);
			this->change_data_panel->Controls->Add(this->userPswd_label);
			this->change_data_panel->Controls->Add(this->userLogin_label);
			this->change_data_panel->Controls->Add(this->userID_label);
			this->Controls->Add(this->admin_fromBtn_submain_panel);

			DataBaseQueries^ queryDB = gcnew DataBaseQueries();
			queryDB->ConnectToDB();
			queryDB->openConnection();
			if (adminLogin->ToLower() == queryDB->getMainAdminLogin()->ToLower())
				queryDB->userInformationShow(info_DataGridView);
			else
				queryDB->userInfromationShowForNotMainAdmin(info_DataGridView);
			queryDB->closeConnection();

			this->admin_fromBtn_submain_panel->ResumeLayout(false);
			this->change_data_panel->ResumeLayout(false);
			this->change_data_panel->PerformLayout();
		}
	System::Void AdminPanelCinemaService::change_cinema_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			choice = 2;
			this->admin_fromBtn_submain_panel->SuspendLayout();
			this->change_data_panel->SuspendLayout();
			this->SuspendLayout();
			this->change_data_panel->Controls->Clear();
			this->change_data_panel->Controls->Add(this->contactInf_textBox);
			this->change_data_panel->Controls->Add(this->contactInf_label);
			this->change_data_panel->Controls->Add(this->closingTime_textBox);
			this->change_data_panel->Controls->Add(this->street_textBox);
			this->change_data_panel->Controls->Add(this->openingTime_textBox);
			this->change_data_panel->Controls->Add(this->city_textBox);
			this->change_data_panel->Controls->Add(this->houseDescr_textBox);
			this->change_data_panel->Controls->Add(this->houseLetter_textBox);
			this->change_data_panel->Controls->Add(this->cinemaName_textBox);
			this->change_data_panel->Controls->Add(this->houseNumber_textBox);
			this->change_data_panel->Controls->Add(this->cinemaPicture_textBox);
			this->change_data_panel->Controls->Add(this->closingTime_label);
			this->change_data_panel->Controls->Add(this->cinemaID_textBox);
			this->change_data_panel->Controls->Add(this->openingTime_label);
			this->change_data_panel->Controls->Add(this->street_label);
			this->change_data_panel->Controls->Add(this->houseDescr_label);
			this->change_data_panel->Controls->Add(this->city_label);
			this->change_data_panel->Controls->Add(this->houseLetter_label);
			this->change_data_panel->Controls->Add(this->cinemaName_label);
			this->change_data_panel->Controls->Add(this->houseNumber_label);
			this->change_data_panel->Controls->Add(this->cinemaPicture_label);
			this->change_data_panel->Controls->Add(this->cinemaID_label);
			this->Controls->Add(this->admin_fromBtn_submain_panel);

			DataBaseQueries^ queryDB = gcnew DataBaseQueries();
			queryDB->cinemaShow(info_DataGridView);

			this->admin_fromBtn_submain_panel->ResumeLayout(false);
			this->change_data_panel->ResumeLayout(false);
			this->change_data_panel->PerformLayout();
		}
	System::Void AdminPanelCinemaService::change_movie_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			choice = 3;
			this->admin_fromBtn_submain_panel->SuspendLayout();
			this->change_data_panel->SuspendLayout();
			this->SuspendLayout();
			this->change_data_panel->Controls->Clear();
			this->change_data_panel->Controls->Add(this->cinemaName_comboBox);
			this->change_data_panel->Controls->Add(this->movieFormat_comboBox);
			this->change_data_panel->Controls->Add(this->release_textBox);
			this->change_data_panel->Controls->Add(this->ageLimit_textBox);
			this->change_data_panel->Controls->Add(this->duration_textBox);
			this->change_data_panel->Controls->Add(this->forMovieCinemaName_label);
			this->change_data_panel->Controls->Add(this->movieFormat_label);
			this->change_data_panel->Controls->Add(this->duration_label);
			this->change_data_panel->Controls->Add(this->genre_textBox);
			this->change_data_panel->Controls->Add(this->movieName_textBox);
			this->change_data_panel->Controls->Add(this->movieID_textBox);
			this->change_data_panel->Controls->Add(this->ageLimit_label);
			this->change_data_panel->Controls->Add(this->genre_label);
			this->change_data_panel->Controls->Add(this->release_label);
			this->change_data_panel->Controls->Add(this->movieName_label);
			this->change_data_panel->Controls->Add(this->movieID_label);
			this->Controls->Add(this->admin_fromBtn_submain_panel);

			DataBaseQueries^ queryDB = gcnew DataBaseQueries();
			queryDB->movieShow(info_DataGridView);

			Int32 selectedIndex{ (this->cinemaName_comboBox->SelectedItem == nullptr ? -1 : this->cinemaName_comboBox->SelectedIndex) };
			this->cinemaName_comboBox->Items->Clear();
			this->cinemaName_comboBox->Items->Add(L"None");
			queryDB->openConnection();
			SqlDataReader^ reader = queryDB->getReaderCinemaNameBox();
			while (reader->Read())
				this->cinemaName_comboBox->Items->Add(reader->GetString(0));
			queryDB->closeConnection();
			this->cinemaName_comboBox->SelectedIndex = selectedIndex;

			this->admin_fromBtn_submain_panel->ResumeLayout(false);
			this->change_data_panel->ResumeLayout(false);
			this->change_data_panel->PerformLayout();
		}
	System::Void AdminPanelCinemaService::change_review_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			choice = 4;
			this->admin_fromBtn_submain_panel->SuspendLayout();
			this->change_data_panel->SuspendLayout();
			this->SuspendLayout();
			this->change_data_panel->Controls->Clear();
			this->change_data_panel->Controls->Add(this->comment_textBox);
			this->change_data_panel->Controls->Add(this->reviewID_textBox);
			this->change_data_panel->Controls->Add(this->comment_label);
			this->change_data_panel->Controls->Add(this->reviewID_label);
			this->Controls->Add(this->admin_fromBtn_submain_panel);

			DataBaseQueries^ queryDB = gcnew DataBaseQueries();
			queryDB->commentShow(info_DataGridView);

			this->admin_fromBtn_submain_panel->ResumeLayout(false);
			this->change_data_panel->ResumeLayout(false);
			this->change_data_panel->PerformLayout();
		}
	System::Void AdminPanelCinemaService::delete_data_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			switch (choice)
			{
			case 1:
			{
				if (this->userID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ userID{ this->userID_textBox->Text->ToString() };
					for (int i{}; i < userID->Length; i++)
						if (userID[i] < '0' || userID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->deleteUserAccountFromAdmin(userID, adminLogin))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID пользователя должно состоять только из цифр!", "Ошибка ID пользователя!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID пользователя!", "Ошибка ID пользователя!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			case 2:
			{
				if (this->cinemaID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ cinemaID{ this->cinemaID_textBox->Text->ToString() };
					for (int i{}; i < cinemaID->Length; i++)
						if (cinemaID[i] < '0' || cinemaID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->deleteCinemaFromAdmin(cinemaID))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID кинотеатра должно состоять только из цифр!", "Ошибка ID кинотеатра!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID кинотеатра!", "Ошибка ID кинотеатра!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			case 3:
			{
				if (this->movieID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ movieID{ this->movieID_textBox->Text->ToString() };
					for (int i{}; i < movieID->Length; i++)
						if (movieID[i] < '0' || movieID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->deleteMovieFromAdmin(movieID, (this->cinemaName_comboBox->SelectedItem == nullptr ? "None" : this->cinemaName_comboBox->SelectedItem->ToString())))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID фильма должно состоять только из цифр!", "Ошибка ID фильма!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID фильма!", "Ошибка ID фильма!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			case 4:
			{
				if (this->reviewID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ reviewID{ this->reviewID_textBox->Text->ToString() };
					for (int i{}; i < reviewID->Length; i++)
						if (reviewID[i] < '0' || reviewID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->deleteReviewFromAdmin(reviewID))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID отзыва должно состоять только из цифр!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID отзыва!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			default:;
			}
		}
	System::Void AdminPanelCinemaService::add_data_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			switch (choice)
			{
			case 1:
			{
				String^ userLogin = this->userLogin_textBox->Text;
				String^ userPswd = this->userPswd_textBox->Text;
				Boolean true_userLogin{ true };
				for (int i{}; i < userLogin->Length; i++)
				{
					if (userLogin[i] >= '0' && userLogin[i] <= '9' || userLogin[i] >= 'а' && userLogin[i] <= 'я' || userLogin[i] >= 'А' && userLogin[i] <= 'Я' ||
						userLogin[i] >= 'a' && userLogin[i] <= 'z' || userLogin[i] >= 'A' && userLogin[i] <= 'Z' || userLogin[i] == '-' || userLogin[i] == '_')
					{
						continue;
					}
					else
					{
						true_userLogin = false;
						break;
					}
				}
				if (true_userLogin)
				{
					if (userLogin->Length < 5 || userLogin->Length > 20 || userPswd->Length < 5 || userPswd->Length > 20)
						MessageBox::Show("Длина логина должна быть от 5 до 20 знаков, как и длина пароля.", "Ошибка! Неверная длина логина и/или пароля.", MessageBoxButtons::OK, MessageBoxIcon::Information);
					else
					{
						if (this->userRole_comboBox->SelectedIndex != -1)
						{
							DataBaseQueries^ queryDB = gcnew DataBaseQueries();
							if (queryDB->checkNewUserAccount(userLogin) && queryDB->addNewUserAccountFromAdmin(userLogin, userPswd, this->userRole_comboBox->SelectedItem->ToString(), adminLogin))
								MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
						else
							MessageBox::Show("Укажите права доступа для пользователя!", "Ошибка прав доступа пользователя!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
				else
					MessageBox::Show("Логин должен состоять из букв русского или латинского алфаваита, цифр и/или символов '_' и '-'!", "Ошибка логина!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			case 2:
			{
				this->openingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
				this->closingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
				if (this->cinemaName_textBox->Text->ToString() == "" || this->city_textBox->Text->ToString() == "" || this->street_textBox->Text->ToString() == "" ||
					this->houseNumber_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->openingTime_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->openingTime_textBox->Text->ToString()) ||
					String::IsNullOrEmpty(this->closingTime_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->closingTime_textBox->Text->ToString()))
				{
					MessageBox::Show("Проверьте заполненность таких полей, как CinemaName|City|Street|HouseNumber|OpeningTime|ClosingTime", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
				{
					this->openingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
					this->closingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
					DataBaseQueries^ queryDB = gcnew DataBaseQueries();
					if (queryDB->addNewCinemaFromAdmin(this->cinemaPicture_textBox->Text->ToString(), this->cinemaName_textBox->Text->ToString(), this->city_textBox->Text->ToString(), this->street_textBox->Text->ToString(),
						this->houseNumber_textBox->Text->ToString(), this->houseLetter_textBox->Text->ToString(), this->houseDescr_textBox->Text->ToString(), this->openingTime_textBox->Text->ToString(),
						this->closingTime_textBox->Text->ToString(), this->contactInf_textBox->Text->ToString()))
					{
						MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
				break;
			}
			case 3:
			{
				if (this->cinemaName_comboBox->SelectedItem == nullptr || this->cinemaName_comboBox->SelectedItem->ToString() == "None")
				{
					this->release_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
					this->duration_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
					if (this->movieName_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->release_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->release_textBox->Text->ToString()) ||
						this->genre_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->duration_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->duration_textBox->Text->ToString()))
					{
						MessageBox::Show("Проверьте заполненность таких полей, как MovieName|Release|Genre|Duration", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
					{
						this->release_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
						this->duration_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
						this->ageLimit_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->addMovieFromAdmin(this->movieName_textBox->Text->ToString(), this->release_textBox->Text->ToString(), this->genre_textBox->Text->ToString(), this->ageLimit_textBox->Text->ToString(),
							this->duration_textBox->Text->ToString(), (this->movieFormat_comboBox->SelectedItem == nullptr ? "" : this->movieFormat_comboBox->SelectedItem->ToString()),
							(this->cinemaName_comboBox->SelectedItem == nullptr ? "None" : this->cinemaName_comboBox->SelectedItem->ToString())))
						{
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
						this->ageLimit_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
					}
				}
				else
				{
					if (this->movieName_textBox->Text->ToString() == "")
						MessageBox::Show("Укажите название фильма, которое хотите добавить в указанный кинотеатр!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					else
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->addMovieFromAdmin(this->movieName_textBox->Text->ToString(), "", "", "", "", "", this->cinemaName_comboBox->SelectedItem->ToString()))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
				break;
			}
			case 4:
			{
				if (this->reviewID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ reviewID{ this->reviewID_textBox->Text->ToString() };
					for (int i{}; i < reviewID->Length; i++)
						if (reviewID[i] < '0' || reviewID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->addReviewFromAdmin(reviewID, this->comment_textBox))
							MessageBox::Show("Внимательно изучите комментарий, при необходимости измените его. Не забудьте нажать кнопку Apply!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID отзыва должно состоять только из цифр!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID отзыва!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			default:;
			}
		}
	System::Void AdminPanelCinemaService::update_data_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			switch (choice)
			{
			case 1:
			{
				DataBaseQueries^ queryDB = gcnew DataBaseQueries();
				queryDB->ConnectToDB();
				queryDB->openConnection();
				if (adminLogin->ToLower() == queryDB->getMainAdminLogin()->ToLower())
					queryDB->userInformationShow(info_DataGridView);
				else
					queryDB->userInfromationShowForNotMainAdmin(info_DataGridView);
				queryDB->closeConnection();
				break;
			}
			case 2:
			{
				DataBaseQueries^ queryDB = gcnew DataBaseQueries();
				queryDB->cinemaShow(info_DataGridView);
				break;
			}
			case 3:
			{
				DataBaseQueries^ queryDB = gcnew DataBaseQueries();
				queryDB->movieShow(info_DataGridView);
				break;
			}
			case 4:
			{
				DataBaseQueries^ queryDB = gcnew DataBaseQueries();
				queryDB->commentShow(info_DataGridView);
				break;
			}
			default:;
			}
		}
	System::Void AdminPanelCinemaService::apply_data_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			switch (choice)
			{
			case 1:
			{
				if (this->userID_textBox->Text == "" || this->userLogin_textBox->Text == "" || this->userPswd_textBox->Text == "" || this->userRole_comboBox->SelectedIndex == -1)
					MessageBox::Show("Заполните все поля формы для изменения информации о пользователе!", "Ошибка изменения данных о пользователе!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				else
				{
					Boolean isNumeric{ true };
					String^ userID{ this->userID_textBox->Text->ToString() };
					for (int i{}; i < userID->Length; i++)
						if (userID[i] < '0' || userID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						String^ userLogin = this->userLogin_textBox->Text;
						String^ userPswd = this->userPswd_textBox->Text;
						Boolean true_userLogin{ true };
						for (int i{}; i < userLogin->Length; i++)
						{
							if (userLogin[i] >= '0' && userLogin[i] <= '9' || userLogin[i] >= 'а' && userLogin[i] <= 'я' || userLogin[i] >= 'А' && userLogin[i] <= 'Я' ||
								userLogin[i] >= 'a' && userLogin[i] <= 'z' || userLogin[i] >= 'A' && userLogin[i] <= 'Z' || userLogin[i] == '-' || userLogin[i] == '_')
							{
								continue;
							}
							else
							{
								true_userLogin = false;
								break;
							}
						}
						if (true_userLogin)
						{
							if (userLogin->Length < 5 || userLogin->Length > 20 || userPswd->Length < 5 || userPswd->Length > 20)
								MessageBox::Show("Длина логина должна быть от 5 до 20 знаков, как и длина пароля.", "Ошибка! Неверная длина логина и/или пароля.", MessageBoxButtons::OK, MessageBoxIcon::Information);
							else
							{
								if (this->userRole_comboBox->SelectedIndex != -1)
								{
									DataBaseQueries^ queryDB = gcnew DataBaseQueries();
									if (queryDB->updateUserAccountFromAdmin(this->userID_textBox->Text, this->userLogin_textBox->Text, this->userPswd_textBox->Text, this->userRole_comboBox->SelectedItem->ToString(), adminLogin))
										MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
								}
								else
									MessageBox::Show("Укажите права доступа для пользователя!", "Ошибка прав доступа пользователя!", MessageBoxButtons::OK, MessageBoxIcon::Information);
							}
						}
						else
							MessageBox::Show("Логин должен состоять из букв русского или латинского алфаваита, цифр и/или символов '_' и '-'!", "Ошибка логина!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID пользователя должно состоять только из цифр!", "Ошибка ID пользователя!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				break;
			}
			case 2:
			{
				Boolean isNumeric{ true };
				String^ cinemaID{ this->cinemaID_textBox->Text->ToString() };
				if (cinemaID != "")
				{
					for (int i{}; i < cinemaID->Length; i++)
						if (cinemaID[i] < '0' || cinemaID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						this->openingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
						this->closingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
						if (this->cinemaName_textBox->Text->ToString() == "" || this->city_textBox->Text->ToString() == "" || this->street_textBox->Text->ToString() == "" ||
							this->houseNumber_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->openingTime_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->openingTime_textBox->Text->ToString()) ||
							String::IsNullOrEmpty(this->closingTime_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->closingTime_textBox->Text->ToString()))
						{
							MessageBox::Show("Проверьте заполненность таких полей, как CinemaName|City|Street|HouseNumber|OpeningTime|ClosingTime", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
						else
						{
							this->openingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
							this->closingTime_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
							DataBaseQueries^ query = gcnew DataBaseQueries();
							if (query->updateCinemaFromAdmin(this->cinemaID_textBox->Text->ToString(), this->cinemaPicture_textBox->Text->ToString(), this->cinemaName_textBox->Text->ToString(), this->city_textBox->Text->ToString(),
								this->street_textBox->Text->ToString(), this->houseNumber_textBox->Text->ToString(), this->houseLetter_textBox->Text->ToString(), this->houseDescr_textBox->Text->ToString(),
								this->openingTime_textBox->Text->ToString(), this->closingTime_textBox->Text->ToString(), this->contactInf_textBox->Text->ToString()))
							{
								MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
							}
						}
					}
					else
						MessageBox::Show("ID кинотеатра должно состоять только из цифр!", "Ошибка ID кинотеатра!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Укажите значение ID кинотеатра!", "Ошибка ID кинотеатра!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			case 3:
			{
				if (this->movieID_textBox->Text->ToString() == "")
					MessageBox::Show("Укажите значение ID фильма!", "Ошибка ID фильма!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				else
				{
					Boolean isNumeric{ true };
					String^ movieID{ this->movieID_textBox->Text->ToString() };
					for (int i{}; i < movieID->Length; i++)
						if (movieID[i] < '0' || movieID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						this->release_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
						this->duration_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
						if (this->movieName_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->release_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->release_textBox->Text->ToString()) ||
							this->genre_textBox->Text->ToString() == "" || String::IsNullOrEmpty(this->duration_textBox->Text->ToString()) || String::IsNullOrWhiteSpace(this->duration_textBox->Text->ToString()))
						{
							MessageBox::Show("Проверьте заполненность таких полей, как MovieName|Release|Genre|Duration", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
						else
						{
							this->release_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
							this->duration_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
							this->ageLimit_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
							DataBaseQueries^ queryDB = gcnew DataBaseQueries();
							if (queryDB->updateMovieFromAdmin(this->movieID_textBox->Text->ToString(), this->movieName_textBox->Text->ToString(), this->release_textBox->Text->ToString(), this->genre_textBox->Text->ToString(),
								this->ageLimit_textBox->Text->ToString(), this->duration_textBox->Text->ToString(), (this->movieFormat_comboBox->SelectedItem == nullptr ? "" : this->movieFormat_comboBox->SelectedItem->ToString()),
								(this->cinemaName_comboBox->SelectedItem == nullptr ? "None" : this->cinemaName_comboBox->SelectedItem->ToString())))
							{
								MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
							}
							this->ageLimit_textBox->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePromptAndLiterals;
						}
					}
					else
						MessageBox::Show("ID фильма должно состоять только из цифр!", "Ошибка ID фильма!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				break;
			}
			case 4:
			{
				if (this->reviewID_textBox->Text->ToString() != "")
				{
					Boolean isNumeric{ true };
					String^ reviewID{ this->reviewID_textBox->Text->ToString() };
					for (int i{}; i < reviewID->Length; i++)
						if (reviewID[i] < '0' || reviewID[i] > '9')
						{
							isNumeric = false;
							break;
						}
					if (isNumeric)
					{
						DataBaseQueries^ queryDB = gcnew DataBaseQueries();
						if (queryDB->updateReviewFromAdmin(reviewID, this->comment_textBox->Text->ToString()))
							MessageBox::Show("Обновите данные, чтобы увидеть изменения в таблице!", "Подсказка!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else
						MessageBox::Show("ID отзыва должно состоять только из цифр!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
					MessageBox::Show("Заполните поле формы ID отзыва!", "Ошибка ID отзыва!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			}
			default:;
			}
		}
	System::Void AdminPanelCinemaService::clear_data_btn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			switch (choice)
			{
			case 1:
			{
				this->userID_textBox->Text = L"";
				this->userLogin_textBox->Text = L"";
				this->userPswd_textBox->Text = L"";
				this->userRole_comboBox->SelectedIndex = -1;
				break;
			}
			case 2:
			{
				this->cinemaID_textBox->Text = L"";
				this->cinemaPicture_textBox->Text = L"";
				this->cinemaName_textBox->Text = L"";
				this->city_textBox->Text = L"";
				this->street_textBox->Text = L"";
				this->houseNumber_textBox->Text = L"";
				this->houseLetter_textBox->Text = L"";
				this->houseDescr_textBox->Text = L"";
				this->openingTime_textBox->Text = L"";
				this->closingTime_textBox->Text = L"";
				this->contactInf_textBox->Text = L"";
				break;
			}
			case 3:
			{
				this->movieID_textBox->Text = L"";
				this->movieName_textBox->Text = L"";
				this->release_textBox->Text = L"";
				this->genre_textBox->Text = L"";
				this->ageLimit_textBox->Text = L"";
				this->duration_textBox->Text = L"";
				this->movieFormat_comboBox->SelectedIndex = -1;
				this->cinemaName_comboBox->SelectedIndex = -1;
				break;
			}
			case 4:
			{
				this->reviewID_textBox->Text = L"";
				this->comment_textBox->Text = L"";
			}
			default:;
			}
		}
}