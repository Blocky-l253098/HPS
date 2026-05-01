#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>

// New feature windows
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

	private: System::Windows::Forms::Label^ welcomeLabel;
	private: System::Windows::Forms::Button^ addAdminButton;
	private: System::Windows::Forms::Button^ addPatientButton;
	private: System::Windows::Forms::Button^ addDoctorButton;
	private: System::Windows::Forms::Button^ viewPatientsButton;
	private: System::Windows::Forms::Button^ viewDoctorsButton;
	private: System::Windows::Forms::Button^ logoutButton;
	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::DataGridView^ dataGridView;
	private: System::Windows::Forms::Label^ titleLabel;

	private: System::Windows::Forms::Button^ bedTrackingButton;
	private: System::Windows::Forms::Button^ noticeBoardButton;
	private: System::Windows::Forms::Button^ billingButton;

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
			if (components)
			{
				delete components;
			}
			if (dbManager) delete dbManager;
		}

	private: System::ComponentModel::Container^ components;

	private:
		void InitializeComponent(void)
		{
			this->welcomeLabel = (gcnew System::Windows::Forms::Label());
			this->addAdminButton = (gcnew System::Windows::Forms::Button());
			this->addPatientButton = (gcnew System::Windows::Forms::Button());
			this->addDoctorButton = (gcnew System::Windows::Forms::Button());
			this->viewPatientsButton = (gcnew System::Windows::Forms::Button());
			this->viewDoctorsButton = (gcnew System::Windows::Forms::Button());

			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->bedTrackingButton = (gcnew System::Windows::Forms::Button());
			this->noticeBoardButton = (gcnew System::Windows::Forms::Button());
			this->billingButton = (gcnew System::Windows::Forms::Button());
			this->logoutButton = (gcnew System::Windows::Forms::Button());


			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
			this->mainPanel->SuspendLayout();
			this->SuspendLayout();

			// titleLabel
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(0, 102, 204);
			this->titleLabel->Location = System::Drawing::Point(20, 20);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(300, 29);
			this->titleLabel->Text = L"Admin Dashboard";

			// welcomeLabel
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(64, 64, 64);
			this->welcomeLabel->Location = System::Drawing::Point(20, 60);
			this->welcomeLabel->Name = L"welcomeLabel";
			this->welcomeLabel->Size = System::Drawing::Size(200, 18);
			this->welcomeLabel->Text = L"Welcome, Admin!";

			// --- FIRST ROW ---
			// addAdminButton (NEW)
			this->addAdminButton->BackColor = System::Drawing::Color::FromArgb(200, 0, 0);
			this->addAdminButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->addAdminButton->ForeColor = System::Drawing::Color::White;
			this->addAdminButton->Location = System::Drawing::Point(20, 100);
			this->addAdminButton->Size = System::Drawing::Size(150, 40);
			this->addAdminButton->Text = L"Add Admin";
			this->addAdminButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addAdminButton_Click);

			// addPatientButton
			this->addPatientButton->BackColor = System::Drawing::Color::FromArgb(0, 102, 204);
			this->addPatientButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->addPatientButton->ForeColor = System::Drawing::Color::White;
			this->addPatientButton->Location = System::Drawing::Point(180, 100);
			this->addPatientButton->Size = System::Drawing::Size(150, 40);
			this->addPatientButton->Text = L"Add Patient";
			this->addPatientButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addPatientButton_Click);

			// addDoctorButton
			this->addDoctorButton->BackColor = System::Drawing::Color::FromArgb(0, 102, 204);
			this->addDoctorButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->addDoctorButton->ForeColor = System::Drawing::Color::White;
			this->addDoctorButton->Location = System::Drawing::Point(340, 100);
			this->addDoctorButton->Size = System::Drawing::Size(150, 40);
			this->addDoctorButton->Text = L"Add Doctor";
			this->addDoctorButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addDoctorButton_Click);

			// viewPatientsButton
			this->viewPatientsButton->BackColor = System::Drawing::Color::FromArgb(0, 102, 204);
			this->viewPatientsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->viewPatientsButton->ForeColor = System::Drawing::Color::White;
			this->viewPatientsButton->Location = System::Drawing::Point(500, 100);
			this->viewPatientsButton->Size = System::Drawing::Size(150, 40);
			this->viewPatientsButton->Text = L"View Patients";
			this->viewPatientsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewPatientsButton_Click);

			// viewDoctorsButton
			this->viewDoctorsButton->BackColor = System::Drawing::Color::FromArgb(0, 204, 102);
			this->viewDoctorsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->viewDoctorsButton->ForeColor = System::Drawing::Color::White;
			this->viewDoctorsButton->Location = System::Drawing::Point(660, 100);
			this->viewDoctorsButton->Size = System::Drawing::Size(150, 40);
			this->viewDoctorsButton->Text = L"View Doctors";
			this->viewDoctorsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewDoctorsButton_Click);


			// --- SECOND ROW ---
			// bedTrackingButton
			this->bedTrackingButton->BackColor = System::Drawing::Color::FromArgb(70, 130, 180);
			this->bedTrackingButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->bedTrackingButton->ForeColor = System::Drawing::Color::White;
			this->bedTrackingButton->Location = System::Drawing::Point(20, 150);
			this->bedTrackingButton->Size = System::Drawing::Size(150, 40);
			this->bedTrackingButton->Text = L"Bed Tracking";
			this->bedTrackingButton->Click += gcnew EventHandler(this, &AdminDashboardForm::bedTrackingButton_Click);

			// noticeBoardButton
			this->noticeBoardButton->BackColor = System::Drawing::Color::FromArgb(72, 201, 176);
			this->noticeBoardButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->noticeBoardButton->ForeColor = System::Drawing::Color::White;
			this->noticeBoardButton->Location = System::Drawing::Point(180, 150);
			this->noticeBoardButton->Size = System::Drawing::Size(150, 40);
			this->noticeBoardButton->Text = L"Notice Board";
			this->noticeBoardButton->Click += gcnew EventHandler(this, &AdminDashboardForm::noticeBoardButton_Click);

			// billingButton
			this->billingButton->BackColor = System::Drawing::Color::FromArgb(100, 149, 237);
			this->billingButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->billingButton->ForeColor = System::Drawing::Color::White;
			this->billingButton->Location = System::Drawing::Point(340, 150);
			this->billingButton->Size = System::Drawing::Size(150, 40);
			this->billingButton->Text = L"Billing";
			this->billingButton->Click += gcnew EventHandler(this, &AdminDashboardForm::billingButton_Click);

			// logoutButton
			this->logoutButton->BackColor = System::Drawing::Color::Red;
			this->logoutButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->logoutButton->ForeColor = System::Drawing::Color::White;
			this->logoutButton->Location = System::Drawing::Point(660, 150);
			this->logoutButton->Size = System::Drawing::Size(150, 40);
			this->logoutButton->Text = L"Logout";
			this->logoutButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::logoutButton_Click);

			// dataGridView
			this->dataGridView->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView->Location = System::Drawing::Point(20, 210);
			this->dataGridView->ReadOnly = true;
			this->dataGridView->Size = System::Drawing::Size(790, 260);

			// AdminDashboardForm setup
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(830, 510);

			// Adding controls
			this->Controls->Add(this->titleLabel);
			this->Controls->Add(this->welcomeLabel);
			this->Controls->Add(this->addAdminButton);
			this->Controls->Add(this->addPatientButton);
			this->Controls->Add(this->addDoctorButton);
			this->Controls->Add(this->viewPatientsButton);
			this->Controls->Add(this->viewDoctorsButton);
			this->Controls->Add(this->bedTrackingButton);
			this->Controls->Add(this->noticeBoardButton);
			this->Controls->Add(this->billingButton);
			this->Controls->Add(this->logoutButton);
			this->Controls->Add(this->dataGridView);

			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Admin Dashboard";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Admin)!";
		}

	private: System::Void addAdminButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ adminUsername = InputBox("Enter Admin Username:");
		if (String::IsNullOrEmpty(adminUsername)) return;

		String^ adminPassword = InputBox("Enter Admin Password:");
		if (String::IsNullOrEmpty(adminPassword)) return;

		// Convert to unmanaged strings
		std::string username = msclr::interop::marshal_as<std::string>(adminUsername);
		std::string password = msclr::interop::marshal_as<std::string>(adminPassword);

		// Connect to database
		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Check if username already exists
		if (dbManager->UsernameExists(username)) {
			MessageBox::Show("Username '" + adminUsername + "' already exists! Please choose a different username.", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect();
			return;
		}

		// Add admin user to database with role "Admin"
		std::string role = "Admin";
		if (dbManager->AddUsername(username, password, role)) {
			MessageBox::Show(
				"Admin account created successfully!\n\nUsername: " + adminUsername + "\nPassword: " + adminPassword + "\nRole: Admin",
				"Admin Account Created",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
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

		// Convert to unmanaged strings
		std::string name = msclr::interop::marshal_as<std::string>(patientName);
		std::string history = msclr::interop::marshal_as<std::string>(medicalHistory);

		// Connect to database
		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Check if patient name already exists
		if (dbManager->PatientNameExists(name)) {
			MessageBox::Show("Patient '" + patientName + "' already exists in the system!", "Duplicate Entry", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect();
			return;
		}

		// Add patient to database
		if (dbManager->AddPatient(name, history)) {
			MessageBox::Show("Patient '" + patientName + "' added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			
			// Ask admin if they want to create a login account for this patient
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Do you want to create a login account for this patient?", 
				"Create Login Account", 
				MessageBoxButtons::YesNo, 
				MessageBoxIcon::Question
			);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				// Prompt for username
				String^ patientUsername = InputBox("Enter username for " + patientName + ":");
				if (String::IsNullOrEmpty(patientUsername)) {
					MessageBox::Show("Username cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Check if username already exists
				std::string username_std = msclr::interop::marshal_as<std::string>(patientUsername);
				if (dbManager->UsernameExists(username_std)) {
					MessageBox::Show("Username '" + patientUsername + "' already exists! Please choose a different username.", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Prompt for password
				String^ patientPassword = InputBox("Enter password for " + patientName + ":");
				if (String::IsNullOrEmpty(patientPassword)) {
					MessageBox::Show("Password cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Convert to unmanaged strings
				std::string username = msclr::interop::marshal_as<std::string>(patientUsername);
				std::string password = msclr::interop::marshal_as<std::string>(patientPassword);
				std::string role = "Patient";

				// Add user account to database
				if (dbManager->AddUsername(username, password, role)) {
					MessageBox::Show(
						"Login account created successfully!\n\nUsername: " + patientUsername + "\nPassword: " + patientPassword,
						"Account Created",
						MessageBoxButtons::OK,
						MessageBoxIcon::Information
					);
				}
				else {
					MessageBox::Show("Failed to create login account. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

		// Convert to unmanaged strings
		std::string name = msclr::interop::marshal_as<std::string>(doctorName);
		std::string spec = msclr::interop::marshal_as<std::string>(specialty);
		std::string sal = msclr::interop::marshal_as<std::string>(salary);

		// Connect to database
		if (!dbManager->Connect()) {
			MessageBox::Show("Failed to connect to database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Check if doctor name already exists
		if (dbManager->DoctorNameExists(name)) {
			MessageBox::Show("Doctor '" + doctorName + "' already exists in the system!", "Duplicate Entry", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			dbManager->Disconnect();
			return;
		}

		// Add doctor to database (available by default = true)
		if (dbManager->AddDoctor(name, spec, sal, true)) {
			MessageBox::Show("Doctor '" + doctorName + "' added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			
			// Ask admin if they want to create a login account for this doctor
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Do you want to create a login account for this doctor?",
				"Create Login Account",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question
			);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				// Prompt for username
				String^ doctorUsername = InputBox("Enter username for " + doctorName + ":");
				if (String::IsNullOrEmpty(doctorUsername)) {
					MessageBox::Show("Username cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Check if username already exists
				std::string username_std = msclr::interop::marshal_as<std::string>(doctorUsername);
				if (dbManager->UsernameExists(username_std)) {
					MessageBox::Show("Username '" + doctorUsername + "' already exists! Please choose a different username.", "Duplicate Username", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Prompt for password
				String^ doctorPassword = InputBox("Enter password for " + doctorName + ":");
				if (String::IsNullOrEmpty(doctorPassword)) {
					MessageBox::Show("Password cannot be empty! Login account not created.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					dbManager->Disconnect();
					return;
				}

				// Convert to unmanaged strings
				std::string username = msclr::interop::marshal_as<std::string>(doctorUsername);
				std::string password = msclr::interop::marshal_as<std::string>(doctorPassword);
				std::string role = "Doctor";

				// Add user account to database
				if (dbManager->AddUsername(username, password, role)) {
					MessageBox::Show(
						"Login account created successfully!\n\nUsername: " + doctorUsername + "\nPassword: " + doctorPassword,
						"Account Created",
						MessageBoxButtons::OK,
						MessageBoxIcon::Information
					);
				}
				else {
					MessageBox::Show("Failed to create login account. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

		dataGridView->Columns->Add("PatientID", "Patient ID");
		dataGridView->Columns->Add("Name", "Name");
		dataGridView->Columns->Add("History", "Medical History");

		sqlite3_stmt* stmt;
		std::string query = "SELECT PatientID, Name, History FROM Patients;";

		if (sqlite3_prepare_v2(dbManager->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int patientId = sqlite3_column_int(stmt, 0);
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

		dataGridView->Columns->Add("DoctorID", "Doctor ID");
		dataGridView->Columns->Add("Name", "Name");
		dataGridView->Columns->Add("Specialty", "Specialty");
		dataGridView->Columns->Add("Salary", "Salary");
		dataGridView->Columns->Add("Available", "Available");

		sqlite3_stmt* stmt;
		std::string query = "SELECT DoctorID, Name, Specialty, Salary, IsAvailable FROM Doctors;";

		if (sqlite3_prepare_v2(dbManager->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int doctorId = sqlite3_column_int(stmt, 0);
				String^ name = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
				String^ specialty = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
				String^ salary = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
				int isAvailable = sqlite3_column_int(stmt, 4);
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
		if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
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
			okButton->Text = "OK"; okButton->Left = 120; okButton->Top = 80;
			okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			form->Controls->Add(label); form->Controls->Add(textBox); form->Controls->Add(okButton);
			form->ShowDialog();
			return textBox->Text;
		}
	};
}