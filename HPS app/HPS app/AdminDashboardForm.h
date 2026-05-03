#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>
#include "BillingModule.h"
#include "BedTrackingForm.h"
#include "MyForm.h"

namespace HPSapp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AdminDashboardForm : public Form
	{
	private:
		DatabaseManager* dbManager;
		Login* currentUser;

	private: System::Windows::Forms::Panel^ sidebarPanel;
	private: System::Windows::Forms::Panel^ contentPanel;
	private: System::Windows::Forms::Panel^ headerPanel;
	private: System::Windows::Forms::Panel^ logoPanel;

	private: System::Windows::Forms::Label^ logoLabel;
	private: System::Windows::Forms::Label^ logoSubLabel;
	private: System::Windows::Forms::Label^ sidebarDivider1;
	private: System::Windows::Forms::Label^ sidebarDivider2;
	private: System::Windows::Forms::Label^ sectionLabel1;
	private: System::Windows::Forms::Label^ sectionLabel2;

	private: System::Windows::Forms::Label^ welcomeLabel;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ contentTitleLabel;

	private: System::Windows::Forms::Button^ addAdminButton;
	private: System::Windows::Forms::Button^ addPatientButton;
	private: System::Windows::Forms::Button^ addDoctorButton;
	private: System::Windows::Forms::Button^ viewPatientsButton;
	private: System::Windows::Forms::Button^ viewDoctorsButton;
	private: System::Windows::Forms::Button^ bedTrackingButton;
	private: System::Windows::Forms::Button^ noticeBoardButton;
	private: System::Windows::Forms::Button^ billingButton;
	private: System::Windows::Forms::Button^ logoutButton;

	private: System::Windows::Forms::DataGridView^ dataGridView;

	public:
		AdminDashboardForm(Login* user)
		{
			currentUser = user;
			dbManager = new DatabaseManager();
			InitializeComponent();
			UpdateWelcomeLabel();
		}

	protected:
		~AdminDashboardForm()
		{
			if (components) delete components;
			if (dbManager)  delete dbManager;
		}

	private: System::ComponentModel::Container^ components;

	private:
		Button^ MakeSidebarButton(String^ text, String^ icon, int yPos,
			System::Drawing::Color bg, System::Drawing::Color fg)
		{
			Button^ btn = gcnew Button();
			btn->Text = icon + "  " + text;
			btn->Location = System::Drawing::Point(12, yPos);
			btn->Size = System::Drawing::Size(196, 40);
			btn->BackColor = bg;
			btn->ForeColor = fg;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->FlatAppearance->MouseOverBackColor =
				System::Drawing::Color::FromArgb(235, 243, 251);
			btn->FlatAppearance->MouseDownBackColor =
				System::Drawing::Color::FromArgb(207, 226, 245);
			btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular));
			btn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			btn->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			btn->Cursor = System::Windows::Forms::Cursors::Hand;
			btn->TabStop = false;
			return btn;
		}

		void InitializeComponent(void)
		{
			this->sidebarPanel = (gcnew Panel());
			this->contentPanel = (gcnew Panel());
			this->headerPanel = (gcnew Panel());
			this->logoPanel = (gcnew Panel());

			this->logoLabel = (gcnew Label());
			this->logoSubLabel = (gcnew Label());
			this->sidebarDivider1 = (gcnew Label());
			this->sidebarDivider2 = (gcnew Label());
			this->sectionLabel1 = (gcnew Label());
			this->sectionLabel2 = (gcnew Label());

			this->welcomeLabel = (gcnew Label());
			this->titleLabel = (gcnew Label());
			this->contentTitleLabel = (gcnew Label());

			this->dataGridView = (gcnew DataGridView());

			this->addAdminButton = MakeSidebarButton(L"Add Admin", L"★", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->addPatientButton = MakeSidebarButton(L"Add Patient", L"✚", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->addDoctorButton = MakeSidebarButton(L"Add Doctor", L"✚", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->viewPatientsButton = MakeSidebarButton(L"View Patients", L"◉", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->viewDoctorsButton = MakeSidebarButton(L"View Doctors", L"◉", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->bedTrackingButton = MakeSidebarButton(L"Bed Tracking", L"▣", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->noticeBoardButton = MakeSidebarButton(L"Notice Board", L"☰", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->billingButton = MakeSidebarButton(L"Billing", L"$", 0,
				System::Drawing::Color::FromArgb(235, 243, 251),
				System::Drawing::Color::FromArgb(44, 44, 42));

			this->logoutButton = (gcnew Button());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
			this->SuspendLayout();

			
			this->sidebarPanel->BackColor = System::Drawing::Color::White;
			this->sidebarPanel->Location = System::Drawing::Point(0, 0);
			this->sidebarPanel->Size = System::Drawing::Size(220, 680);
			this->sidebarPanel->Name = L"sidebarPanel";

			
			this->logoPanel->BackColor = System::Drawing::Color::FromArgb(24, 95, 165);
			this->logoPanel->Location = System::Drawing::Point(0, 0);
			this->logoPanel->Size = System::Drawing::Size(220, 72);
			this->logoPanel->Name = L"logoPanel";

			this->logoLabel->AutoSize = false;
			this->logoLabel->Text = L"HPS Hospital";
			this->logoLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Bold));
			this->logoLabel->ForeColor = System::Drawing::Color::White;
			this->logoLabel->Location = System::Drawing::Point(16, 12);
			this->logoLabel->Size = System::Drawing::Size(190, 24);
			this->logoLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			this->logoSubLabel->AutoSize = false;
			this->logoSubLabel->Text = L"Admin Dashboard";
			this->logoSubLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->logoSubLabel->ForeColor = System::Drawing::Color::FromArgb(180, 212, 240);
			this->logoSubLabel->Location = System::Drawing::Point(16, 38);
			this->logoSubLabel->Size = System::Drawing::Size(190, 18);

			this->logoPanel->Controls->Add(this->logoLabel);
			this->logoPanel->Controls->Add(this->logoSubLabel);

			
			this->sectionLabel1->AutoSize = false;
			this->sectionLabel1->Text = L"MANAGE";
			this->sectionLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel1->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel1->Location = System::Drawing::Point(16, 88);
			this->sectionLabel1->Size = System::Drawing::Size(180, 16);

			this->addAdminButton->Location = System::Drawing::Point(12, 108);
			this->addPatientButton->Location = System::Drawing::Point(12, 152);
			this->addDoctorButton->Location = System::Drawing::Point(12, 196);
			this->viewPatientsButton->Location = System::Drawing::Point(12, 240);
			this->viewDoctorsButton->Location = System::Drawing::Point(12, 284);

			this->sidebarDivider1->AutoSize = false;
			this->sidebarDivider1->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider1->Location = System::Drawing::Point(12, 334);
			this->sidebarDivider1->Size = System::Drawing::Size(196, 1);

			this->sectionLabel2->AutoSize = false;
			this->sectionLabel2->Text = L"TOOLS";
			this->sectionLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel2->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel2->Location = System::Drawing::Point(16, 344);
			this->sectionLabel2->Size = System::Drawing::Size(180, 16);

			this->bedTrackingButton->Location = System::Drawing::Point(12, 364);
			this->noticeBoardButton->Location = System::Drawing::Point(12, 408);
			this->billingButton->Location = System::Drawing::Point(12, 452);

	
			this->sidebarDivider2->AutoSize = false;
			this->sidebarDivider2->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider2->Location = System::Drawing::Point(12, 506);
			this->sidebarDivider2->Size = System::Drawing::Size(196, 1);

			this->logoutButton->Text = L"⏻  Logout";
			this->logoutButton->Location = System::Drawing::Point(12, 620);
			this->logoutButton->Size = System::Drawing::Size(196, 40);
			this->logoutButton->BackColor = System::Drawing::Color::FromArgb(255, 240, 240);
			this->logoutButton->ForeColor = System::Drawing::Color::FromArgb(180, 30, 30);
			this->logoutButton->FlatStyle = FlatStyle::Flat;
			this->logoutButton->FlatAppearance->BorderSize = 0;
			this->logoutButton->FlatAppearance->MouseOverBackColor =
				System::Drawing::Color::FromArgb(255, 220, 220);
			this->logoutButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->logoutButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->logoutButton->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			this->logoutButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->logoutButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::logoutButton_Click);

			
			this->addAdminButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addAdminButton_Click);
			this->addPatientButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addPatientButton_Click);
			this->addDoctorButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addDoctorButton_Click);
			this->viewPatientsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewPatientsButton_Click);
			this->viewDoctorsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewDoctorsButton_Click);
			this->bedTrackingButton->Click += gcnew EventHandler(this, &AdminDashboardForm::bedTrackingButton_Click);
			this->noticeBoardButton->Click += gcnew EventHandler(this, &AdminDashboardForm::noticeBoardButton_Click);
			this->billingButton->Click += gcnew EventHandler(this, &AdminDashboardForm::billingButton_Click);

			
			this->sidebarPanel->Controls->Add(this->logoPanel);
			this->sidebarPanel->Controls->Add(this->sectionLabel1);
			this->sidebarPanel->Controls->Add(this->addAdminButton);
			this->sidebarPanel->Controls->Add(this->addPatientButton);
			this->sidebarPanel->Controls->Add(this->addDoctorButton);
			this->sidebarPanel->Controls->Add(this->viewPatientsButton);
			this->sidebarPanel->Controls->Add(this->viewDoctorsButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider1);
			this->sidebarPanel->Controls->Add(this->sectionLabel2);
			this->sidebarPanel->Controls->Add(this->bedTrackingButton);
			this->sidebarPanel->Controls->Add(this->noticeBoardButton);
			this->sidebarPanel->Controls->Add(this->billingButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider2);
			this->sidebarPanel->Controls->Add(this->logoutButton);

			
			this->headerPanel->BackColor = System::Drawing::Color::White;
			this->headerPanel->Location = System::Drawing::Point(220, 0);
			this->headerPanel->Size = System::Drawing::Size(860, 64);
			this->headerPanel->Name = L"headerPanel";

			this->titleLabel->AutoSize = false;
			this->titleLabel->Text = L"Admin Dashboard";
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->titleLabel->Location = System::Drawing::Point(24, 12);
			this->titleLabel->Size = System::Drawing::Size(340, 30);
			this->titleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			this->welcomeLabel->AutoSize = false;
			this->welcomeLabel->Text = L"Welcome, Admin!";
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->welcomeLabel->Location = System::Drawing::Point(24, 40);
			this->welcomeLabel->Size = System::Drawing::Size(340, 18);

			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Controls->Add(this->welcomeLabel);

			
			this->contentPanel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->contentPanel->Location = System::Drawing::Point(220, 64);
			this->contentPanel->Size = System::Drawing::Size(860, 616);
			this->contentPanel->Name = L"contentPanel";

			
			this->contentTitleLabel->AutoSize = false;
			this->contentTitleLabel->Text = L"Select an action from the sidebar to view data";
			this->contentTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->contentTitleLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->contentTitleLabel->Location = System::Drawing::Point(20, 16);
			this->contentTitleLabel->Size = System::Drawing::Size(820, 22);
			this->contentTitleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			
			this->dataGridView->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataGridView->ColumnHeadersDefaultCellStyle->BackColor =
				System::Drawing::Color::FromArgb(24, 95, 165);
			this->dataGridView->ColumnHeadersDefaultCellStyle->ForeColor =
				System::Drawing::Color::White;
			this->dataGridView->ColumnHeadersDefaultCellStyle->Font =
				(gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->dataGridView->ColumnHeadersDefaultCellStyle->Padding =
				System::Windows::Forms::Padding(8, 0, 0, 0);
			this->dataGridView->ColumnHeadersHeight = 36;
			this->dataGridView->EnableHeadersVisualStyles = false;
			this->dataGridView->DefaultCellStyle->Font =
				(gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->dataGridView->DefaultCellStyle->Padding =
				System::Windows::Forms::Padding(6, 0, 0, 0);
			this->dataGridView->RowTemplate->Height = 30;
			this->dataGridView->AlternatingRowsDefaultCellStyle->BackColor =
				System::Drawing::Color::FromArgb(245, 248, 252);
			this->dataGridView->GridColor = System::Drawing::Color::FromArgb(220, 225, 232);
			this->dataGridView->Location = System::Drawing::Point(20, 50);
			this->dataGridView->ReadOnly = true;
			this->dataGridView->Size = System::Drawing::Size(820, 540);
			this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView->RowHeadersVisible = false;
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

			this->contentPanel->Controls->Add(this->contentTitleLabel);
			this->contentPanel->Controls->Add(this->dataGridView);

		
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->ClientSize = System::Drawing::Size(1080, 680);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Admin Dashboard";

			this->Controls->Add(this->sidebarPanel);
			this->Controls->Add(this->headerPanel);
			this->Controls->Add(this->contentPanel);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		
	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Admin)";
		}

		

	private: System::Void addAdminButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ adminUsername = InputBox("Enter Admin Username:");
		if (String::IsNullOrEmpty(adminUsername)) return;

		String^ adminPassword = InputBox("Enter Admin Password:");
		if (String::IsNullOrEmpty(adminPassword)) return;

		std::string username = msclr::interop::marshal_as<std::string>(adminUsername);
		std::string password = msclr::interop::marshal_as<std::string>(adminPassword);

		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (dbManager->UsernameExists(username)) {
			MessageBox::Show("Username '" + adminUsername + "' already exists! Please choose a different username.", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect();
			return;
		}

		std::string role = "Admin";
		if (dbManager->AddUsername(username, password, role)) {
			MessageBox::Show(
				"Admin account created successfully!\n\nUsername: " + adminUsername + "\nPassword: " + adminPassword + "\nRole: Admin",
				"Admin Account Created", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			MessageBox::Show("Failed to create admin account. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		dbManager->Disconnect();
	}

	private: System::Void addPatientButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ patientName = InputBox("Enter Patient Name:");
		if (String::IsNullOrEmpty(patientName)) return;

		String^ medicalHistory = InputBox("Enter Medical History:");
		if (String::IsNullOrEmpty(medicalHistory)) medicalHistory = "None";

		std::string name = msclr::interop::marshal_as<std::string>(patientName);
		std::string history = msclr::interop::marshal_as<std::string>(medicalHistory);

		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (dbManager->PatientNameExists(name)) {
			MessageBox::Show("Patient '" + patientName + "' already exists in the system!", "Duplicate Entry", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect();
			return;
		}

		if (dbManager->AddPatient(name, history)) {
			MessageBox::Show("Patient '" + patientName + "' added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Do you want to create a login account for this patient?",
				"Create Login Account", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				String^ patientUsername = InputBox("Enter username for " + patientName + ":");
				if (String::IsNullOrEmpty(patientUsername)) {
					MessageBox::Show("Username cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				std::string username_std = msclr::interop::marshal_as<std::string>(patientUsername);
				if (dbManager->UsernameExists(username_std)) {
					MessageBox::Show("Username '" + patientUsername + "' already exists!", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				String^ patientPassword = InputBox("Enter password for " + patientName + ":");
				if (String::IsNullOrEmpty(patientPassword)) {
					MessageBox::Show("Password cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				std::string username = msclr::interop::marshal_as<std::string>(patientUsername);
				std::string password = msclr::interop::marshal_as<std::string>(patientPassword);
				std::string role = "Patient";

				if (dbManager->AddUsername(username, password, role)) {
					MessageBox::Show(
						"Login account created successfully!\n\nUsername: " + patientUsername + "\nPassword: " + patientPassword,
						"Account Created", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Failed to create login account.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
		else {
			MessageBox::Show("Failed to add patient. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		dbManager->Disconnect();
	}

	private: System::Void addDoctorButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ doctorName = InputBox("Enter Doctor Name:");
		if (String::IsNullOrEmpty(doctorName)) return;

		String^ specialty = InputBox("Enter Specialty:");
		if (String::IsNullOrEmpty(specialty)) specialty = "General";

		String^ salary = InputBox("Enter Salary:");
		if (String::IsNullOrEmpty(salary)) salary = "0";

		std::string name = msclr::interop::marshal_as<std::string>(doctorName);
		std::string spec = msclr::interop::marshal_as<std::string>(specialty);
		std::string sal = msclr::interop::marshal_as<std::string>(salary);

		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (dbManager->DoctorNameExists(name)) {
			MessageBox::Show("Doctor '" + doctorName + "' already exists in the system!", "Duplicate Entry", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect(); return;
		}

		if (dbManager->AddDoctor(name, spec, sal, true)) {
			MessageBox::Show("Doctor '" + doctorName + "' added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Do you want to create a login account for this doctor?",
				"Create Login Account", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				String^ doctorUsername = InputBox("Enter username for " + doctorName + ":");
				if (String::IsNullOrEmpty(doctorUsername)) {
					MessageBox::Show("Username cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				std::string username_std = msclr::interop::marshal_as<std::string>(doctorUsername);
				if (dbManager->UsernameExists(username_std)) {
					MessageBox::Show("Username '" + doctorUsername + "' already exists!", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				String^ doctorPassword = InputBox("Enter password for " + doctorName + ":");
				if (String::IsNullOrEmpty(doctorPassword)) {
					MessageBox::Show("Password cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect(); return;
				}

				std::string username = msclr::interop::marshal_as<std::string>(doctorUsername);
				std::string password = msclr::interop::marshal_as<std::string>(doctorPassword);
				std::string role = "Doctor";

				if (dbManager->AddUsername(username, password, role)) {
					MessageBox::Show(
						"Login account created successfully!\n\nUsername: " + doctorUsername + "\nPassword: " + doctorPassword,
						"Account Created", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Failed to create login account.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
		else {
			MessageBox::Show("Failed to add doctor. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		dbManager->Disconnect();
	}

	private: System::Void viewPatientsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		dataGridView->Rows->Clear();
		dataGridView->Columns->Clear();
		contentTitleLabel->Text = L"Patients";

		dataGridView->Columns->Add("PatientID", "Patient ID");
		dataGridView->Columns->Add("Name", "Name");
		dataGridView->Columns->Add("History", "Medical History");

		sqlite3_stmt* stmt;
		std::string query = "SELECT PatientID, Name, History FROM Patients;";

		if (sqlite3_prepare_v2(dbManager->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int     patientId = sqlite3_column_int(stmt, 0);
				String^ name = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
				String^ history = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
				dataGridView->Rows->Add(patientId.ToString(), name, history);
			}
		}

		sqlite3_finalize(stmt);
		dbManager->Disconnect();

		if (dataGridView->Rows->Count == 0) {
			MessageBox::Show("No patients found in database.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	private: System::Void viewDoctorsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		dataGridView->Rows->Clear();
		dataGridView->Columns->Clear();
		contentTitleLabel->Text = L"Doctors";

		dataGridView->Columns->Add("DoctorID", "Doctor ID");
		dataGridView->Columns->Add("Name", "Name");
		dataGridView->Columns->Add("Specialty", "Specialty");
		dataGridView->Columns->Add("Salary", "Salary");
		dataGridView->Columns->Add("Available", "Available");

		sqlite3_stmt* stmt;
		std::string query = "SELECT DoctorID, Name, Specialty, Salary, IsAvailable FROM Doctors;";

		if (sqlite3_prepare_v2(dbManager->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int     doctorId = sqlite3_column_int(stmt, 0);
				String^ name = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
				String^ specialty = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
				String^ salary = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
				int     isAvailable = sqlite3_column_int(stmt, 4);
				String^ available = isAvailable ? "Yes" : "No";
				dataGridView->Rows->Add(doctorId.ToString(), name, specialty, salary, available);
			}
		}

		sqlite3_finalize(stmt);
		dbManager->Disconnect();

		if (dataGridView->Rows->Count == 0) {
			MessageBox::Show("No doctors found in database.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to logout?", "Logout",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			this->Close();
		}
	}

	private: System::Void bedTrackingButton_Click(System::Object^ sender, System::EventArgs^ e) {
		HospitalManagment::BedTrackingForm^ bedForm = gcnew HospitalManagment::BedTrackingForm();
		bedForm->ShowDialog(this);
	}

	private: System::Void noticeBoardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		HospitalManagment::MyForm^ noticeForm = gcnew HospitalManagment::MyForm();
		noticeForm->ShowDialog(this);
	}

	private: System::Void billingButton_Click(System::Object^ sender, System::EventArgs^ e) {
		HospitalManagment::BillingModule^ billForm = gcnew HospitalManagment::BillingModule();
		billForm->ShowDialog(this);
	}

	private:
		String^ InputBox(String^ prompt) {
			Form^ form = gcnew Form();
			form->Text = "Input";
			form->Width = 300;
			form->Height = 150;
			form->StartPosition = FormStartPosition::CenterParent;
			Label^ label = gcnew Label();
			label->Left = 20; label->Top = 20; label->Text = prompt; label->Width = 250;
			TextBox^ textBox = gcnew TextBox();
			textBox->Left = 20; textBox->Top = 50; textBox->Width = 250;
			Button^ okButton = gcnew Button();
			okButton->Text = "OK";
			okButton->Left = 120;
			okButton->Top = 80;
			okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			form->Controls->Add(label);
			form->Controls->Add(textBox);
			form->Controls->Add(okButton);
			form->ShowDialog();
			return textBox->Text;
		}
	};
}