#include "CinemaService.h"

namespace CinemaServiceApplication
{
	CinemaService::CinemaService(void)
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}
	CinemaService::CinemaService(String^ UserName)
	{
		InitializeComponent();
		this->UserName = UserName;
		//Запрос каталога кинотеатров с описанием.
		DataBaseQueries^ queryDB = gcnew DataBaseQueries();
		queryDB->ConnectToDB();
		queryDB->openConnection();
		SqlDataReader^ reader = queryDB->getReaderCinemaCatalog();
		while (reader->Read())
		{
			CinemaButtonForCinemaCatalog^ cinema_btn = gcnew CinemaButtonForCinemaCatalog(reader, this->submain_cinema_panel, this->UserName, this->submain_cinema_label);
			this->submain_cinema_flowLayoutPanel->Controls->Add(cinema_btn->getCinemaBtn());
		}
		queryDB->closeConnection();
	}
	CinemaService::~CinemaService()
	{
		if (components)
		{
			delete components;
		}
	}
	void CinemaService::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CinemaService::typeid));
		this->submain_cinema_flowLayoutPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
		this->cinemaservice_exit_btn = (gcnew System::Windows::Forms::Button());
		this->submain_cinema_label = (gcnew System::Windows::Forms::Label());
		this->submain_cinema_panel = (gcnew System::Windows::Forms::Panel());
		this->search_btn = (gcnew System::Windows::Forms::Button());
		this->search_textBox = (gcnew System::Windows::Forms::TextBox());
		this->SuspendLayout();
		// 
		// submain_cinema_flowLayoutPanel
		// 
		this->submain_cinema_flowLayoutPanel->AutoScroll = true;
		this->submain_cinema_flowLayoutPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->submain_cinema_flowLayoutPanel->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
		this->submain_cinema_flowLayoutPanel->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 13.8F, System::Drawing::FontStyle::Bold,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->submain_cinema_flowLayoutPanel->Location = System::Drawing::Point(0, 50);
		this->submain_cinema_flowLayoutPanel->MaximumSize = System::Drawing::Size(220, 670);
		this->submain_cinema_flowLayoutPanel->MinimumSize = System::Drawing::Size(220, 670);
		this->submain_cinema_flowLayoutPanel->Name = L"submain_cinema_flowLayoutPanel";
		this->submain_cinema_flowLayoutPanel->Size = System::Drawing::Size(220, 670);
		this->submain_cinema_flowLayoutPanel->TabIndex = 0;
		// 
		// cinemaservice_exit_btn
		// 
		this->cinemaservice_exit_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
		this->cinemaservice_exit_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->cinemaservice_exit_btn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cinemaservice_exit_btn->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
		this->cinemaservice_exit_btn->FlatAppearance->BorderSize = 3;
		this->cinemaservice_exit_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Brown;
		this->cinemaservice_exit_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::IndianRed;
		this->cinemaservice_exit_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->cinemaservice_exit_btn->ForeColor = System::Drawing::SystemColors::ControlText;
		this->cinemaservice_exit_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cinemaservice_exit_btn.Image")));
		this->cinemaservice_exit_btn->Location = System::Drawing::Point(1030, 0);
		this->cinemaservice_exit_btn->MaximumSize = System::Drawing::Size(50, 50);
		this->cinemaservice_exit_btn->MinimumSize = System::Drawing::Size(50, 50);
		this->cinemaservice_exit_btn->Name = L"cinemaservice_exit_btn";
		this->cinemaservice_exit_btn->Size = System::Drawing::Size(50, 50);
		this->cinemaservice_exit_btn->TabIndex = 0;
		this->cinemaservice_exit_btn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
		this->cinemaservice_exit_btn->UseVisualStyleBackColor = false;
		this->cinemaservice_exit_btn->Click += gcnew System::EventHandler(this, &CinemaService::cinemaservice_exit_btn_Click);
		// 
		// submain_cinema_label
		// 
		this->submain_cinema_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->submain_cinema_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->submain_cinema_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->submain_cinema_label->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->submain_cinema_label->ForeColor = System::Drawing::SystemColors::MenuBar;
		this->submain_cinema_label->Location = System::Drawing::Point(220, 0);
		this->submain_cinema_label->MaximumSize = System::Drawing::Size(810, 50);
		this->submain_cinema_label->MinimumSize = System::Drawing::Size(810, 50);
		this->submain_cinema_label->Name = L"submain_cinema_label";
		this->submain_cinema_label->Size = System::Drawing::Size(810, 50);
		this->submain_cinema_label->TabIndex = 1;
		this->submain_cinema_label->Text = L"Выберите кинотеатр из предложенного списка";
		this->submain_cinema_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// submain_cinema_panel
		// 
		this->submain_cinema_panel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(140)),
			static_cast<System::Int32>(static_cast<System::Byte>(146)), static_cast<System::Int32>(static_cast<System::Byte>(172)));
		this->submain_cinema_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->submain_cinema_panel->Location = System::Drawing::Point(220, 50);
		this->submain_cinema_panel->MaximumSize = System::Drawing::Size(860, 690);
		this->submain_cinema_panel->MinimumSize = System::Drawing::Size(860, 690);
		this->submain_cinema_panel->Name = L"submain_cinema_panel";
		this->submain_cinema_panel->Size = System::Drawing::Size(860, 690);
		this->submain_cinema_panel->TabIndex = 2;
		// 
		// search_btn
		// 
		this->search_btn->BackColor = System::Drawing::Color::SteelBlue;
		this->search_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"search_btn.BackgroundImage")));
		this->search_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->search_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->search_btn->FlatAppearance->BorderColor = System::Drawing::Color::Indigo;
		this->search_btn->FlatAppearance->BorderSize = 2;
		this->search_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::RoyalBlue;
		this->search_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->search_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->search_btn->Location = System::Drawing::Point(170, 0);
		this->search_btn->MaximumSize = System::Drawing::Size(50, 50);
		this->search_btn->MinimumSize = System::Drawing::Size(50, 50);
		this->search_btn->Name = L"search_btn";
		this->search_btn->Size = System::Drawing::Size(50, 50);
		this->search_btn->TabIndex = 3;
		this->search_btn->UseVisualStyleBackColor = false;
		this->search_btn->Click += gcnew System::EventHandler(this, &CinemaService::search_btn_Click);
		// 
		// search_textBox
		// 
		this->search_textBox->BackColor = System::Drawing::Color::GhostWhite;
		this->search_textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->search_textBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->search_textBox->Location = System::Drawing::Point(2, 12);
		this->search_textBox->MaximumSize = System::Drawing::Size(168, 25);
		this->search_textBox->MaxLength = 30;
		this->search_textBox->MinimumSize = System::Drawing::Size(168, 25);
		this->search_textBox->Name = L"search_textBox";
		this->search_textBox->Size = System::Drawing::Size(168, 25);
		this->search_textBox->TabIndex = 4;
		this->search_textBox->Text = L"Поиск кинотеатра";
		this->search_textBox->Enter += gcnew System::EventHandler(this, &CinemaService::search_textBox_Enter);
		this->search_textBox->Leave += gcnew System::EventHandler(this, &CinemaService::search_textBox_Leave);
		// 
		// CinemaService
		// 
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
			static_cast<System::Int32>(static_cast<System::Byte>(64)));
		this->CancelButton = this->cinemaservice_exit_btn;
		this->ClientSize = System::Drawing::Size(1080, 720);
		this->Controls->Add(this->search_btn);
		this->Controls->Add(this->cinemaservice_exit_btn);
		this->Controls->Add(this->search_textBox);
		this->Controls->Add(this->submain_cinema_panel);
		this->Controls->Add(this->submain_cinema_label);
		this->Controls->Add(this->submain_cinema_flowLayoutPanel);
		this->DoubleBuffered = true;
		this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->Margin = System::Windows::Forms::Padding(4);
		this->MaximumSize = System::Drawing::Size(1080, 720);
		this->MinimumSize = System::Drawing::Size(1080, 720);
		this->Name = L"CinemaService";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"CinemaService";
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	System::Void CinemaService::search_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->submain_cinema_flowLayoutPanel->Controls->Clear();
		this->submain_cinema_flowLayoutPanel->SuspendLayout();
		DataBaseQueries^ queryDB = gcnew DataBaseQueries();
		queryDB->ConnectToDB();
		queryDB->openConnection();
		SqlDataReader^ reader{};
		if (this->search_textBox->Text != "" && this->search_textBox->Text != "Поиск кинотеатра")
			reader = queryDB->getReaderSearchedCinemaCatalog(this->search_textBox->Text);
		else
		{
			reader = queryDB->getReaderCinemaCatalog();
			this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(192, 192, 192);
			this->search_textBox->Text = L"Поиск кинотеатра";
		}
		while (reader->Read())
		{
			CinemaButtonForCinemaCatalog^ cinema_btn = gcnew CinemaButtonForCinemaCatalog(reader, this->submain_cinema_panel, this->UserName, this->submain_cinema_label);
			this->submain_cinema_flowLayoutPanel->Controls->Add(cinema_btn->getCinemaBtn());
		}
		queryDB->closeConnection();
		this->submain_cinema_flowLayoutPanel->ResumeLayout();
	}
	System::Void CinemaService::cinemaservice_exit_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	System::Void CinemaService::search_textBox_Enter(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->search_textBox->Text == "Поиск кинотеатра")
		{
			this->search_textBox->Text = L"";
			this->search_textBox->ForeColor = System::Drawing::Color::Navy;
		}
	}
	System::Void CinemaService::search_textBox_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (this->search_textBox->Text == "")
	{
		this->search_textBox->ForeColor = System::Drawing::Color::FromArgb(192, 192, 192);
		this->search_textBox->Text = L"Поиск кинотеатра";
	}
}
}