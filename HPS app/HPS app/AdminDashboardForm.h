#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>

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
	private: System::Windows::Forms::Button^ addPatientButton;
	private: System::Windows::Forms::Button^ addDoctorButton;
	private: System::Windows::Forms::Button^ viewPatientsButton;
	private: System::Windows::Forms::Button^ viewDoctorsButton;
	private: System::Windows::Forms::Button^ logoutButton;
	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::DataGridView^ dataGridView;
	private: System::Windows::Forms::Label^ titleLabel;

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

	private: System::ComponentModel::Container ^components;

	private:
		void InitializeComponent(void)
		{
			this->welcomeLabel = (gcnew System::Windows::Forms::Label());
			this->addPatientButton = (gcnew System::Windows::Forms::Button());
			this->addDoctorButton = (gcnew System::Windows::Forms::Button());
			this->viewPatientsButton = (gcnew System::Windows::Forms::Button());
			this->viewDoctorsButton = (gcnew System::Windows::Forms::Button());
			this->logoutButton = (gcnew System::Windows::Forms::Button());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
			this->mainPanel->SuspendLayout();
			this->SuspendLayout();

			// titleLabel
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->titleLabel->Location = System::Drawing::Point(20, 20);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(300, 29);
			this->titleLabel->TabIndex = 0;
			this->titleLabel->Text = L"Admin Dashboard";

			// welcomeLabel
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->welcomeLabel->Location = System::Drawing::Point(20, 60);
			this->welcomeLabel->Name = L"welcomeLabel";
			this->welcomeLabel->Size = System::Drawing::Size(200, 18);
			this->welcomeLabel->TabIndex = 1;
			this->welcomeLabel->Text = L"Welcome, Admin!";

			// addPatientButton
			this->addPatientButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->addPatientButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addPatientButton->ForeColor = System::Drawing::Color::White;
			this->addPatientButton->Location = System::Drawing::Point(20, 100);
			this->addPatientButton->Name = L"addPatientButton";
			this->addPatientButton->Size = System::Drawing::Size(150, 40);
			this->addPatientButton->TabIndex = 2;
			this->addPatientButton->Text = L"Add Patient";
			this->addPatientButton->UseVisualStyleBackColor = false;
			this->addPatientButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addPatientButton_Click);

			// addDoctorButton
			this->addDoctorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->addDoctorButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addDoctorButton->ForeColor = System::Drawing::Color::White;
			this->addDoctorButton->Location = System::Drawing::Point(180, 100);
			this->addDoctorButton->Name = L"addDoctorButton";
			this->addDoctorButton->Size = System::Drawing::Size(150, 40);
			this->addDoctorButton->TabIndex = 3;
			this->addDoctorButton->Text = L"Add Doctor";
			this->addDoctorButton->UseVisualStyleBackColor = false;
			this->addDoctorButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::addDoctorButton_Click);

			// viewPatientsButton
			this->viewPatientsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->viewPatientsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewPatientsButton->ForeColor = System::Drawing::Color::White;
			this->viewPatientsButton->Location = System::Drawing::Point(340, 100);
			this->viewPatientsButton->Name = L"viewPatientsButton";
			this->viewPatientsButton->Size = System::Drawing::Size(150, 40);
			this->viewPatientsButton->TabIndex = 4;
			this->viewPatientsButton->Text = L"View Patients";
			this->viewPatientsButton->UseVisualStyleBackColor = false;
			this->viewPatientsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewPatientsButton_Click);

			// viewDoctorsButton
			this->viewDoctorsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(204)), static_cast<System::Int32>(static_cast<System::Byte>(102)));
			this->viewDoctorsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewDoctorsButton->ForeColor = System::Drawing::Color::White;
			this->viewDoctorsButton->Location = System::Drawing::Point(500, 100);
			this->viewDoctorsButton->Name = L"viewDoctorsButton";
			this->viewDoctorsButton->Size = System::Drawing::Size(150, 40);
			this->viewDoctorsButton->TabIndex = 5;
			this->viewDoctorsButton->Text = L"View Doctors";
			this->viewDoctorsButton->UseVisualStyleBackColor = false;
			this->viewDoctorsButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::viewDoctorsButton_Click);

			// logoutButton
			this->logoutButton->BackColor = System::Drawing::Color::Red;
			this->logoutButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->logoutButton->ForeColor = System::Drawing::Color::White;
			this->logoutButton->Location = System::Drawing::Point(660, 100);
			this->logoutButton->Name = L"logoutButton";
			this->logoutButton->Size = System::Drawing::Size(120, 40);
			this->logoutButton->TabIndex = 6;
			this->logoutButton->Text = L"Logout";
			this->logoutButton->UseVisualStyleBackColor = false;
			this->logoutButton->Click += gcnew System::EventHandler(this, &AdminDashboardForm::logoutButton_Click);

			// dataGridView
			this->dataGridView->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView->Location = System::Drawing::Point(20, 160);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->ReadOnly = true;
			this->dataGridView->Size = System::Drawing::Size(760, 300);
			this->dataGridView->TabIndex = 7;

			// mainPanel
			this->mainPanel->BackColor = System::Drawing::Color::White;
			this->mainPanel->Location = System::Drawing::Point(0, 0);
			this->mainPanel->Name = L"mainPanel";
			this->mainPanel->Size = System::Drawing::Size(800, 500);
			this->mainPanel->TabIndex = 8;

			// AdminDashboardForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(800, 500);
			this->Controls->Add(this->dataGridView);
			this->Controls->Add(this->logoutButton);
			this->Controls->Add(this->viewDoctorsButton);
			this->Controls->Add(this->viewPatientsButton);
			this->Controls->Add(this->addDoctorButton);
			this->Controls->Add(this->addPatientButton);
			this->Controls->Add(this->welcomeLabel);
			this->Controls->Add(this->titleLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"AdminDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Admin Dashboard";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
			this->mainPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Admin)!";
		}

	private: System::Void addPatientButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ name = InputBox("Enter Patient Name:");
		if (String::IsNullOrEmpty(name)) return;

		String^ history = InputBox("Enter Patient History:");
		if (String::IsNullOrEmpty(history)) return;

		std::string patientName = msclr::interop::marshal_as<std::string>(name);
		std::string patientHistory = msclr::interop::marshal_as<std::string>(history);

		if (dbManager->Connect()) {
			if (dbManager->AddPatient(patientName, patientHistory)) {
				MessageBox::Show("Patient added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to add patient!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void addDoctorButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ name = InputBox("Enter Doctor Name:");
		if (String::IsNullOrEmpty(name)) return;

		String^ specialty = InputBox("Enter Specialty:");
		if (String::IsNullOrEmpty(specialty)) return;

		String^ salary = InputBox("Enter Salary:");
		if (String::IsNullOrEmpty(salary)) return;

		std::string doctorName = msclr::interop::marshal_as<std::string>(name);
		std::string doctorSpecialty = msclr::interop::marshal_as<std::string>(specialty);
		std::string doctorSalary = msclr::interop::marshal_as<std::string>(salary);

		if (dbManager->Connect()) {
			if (dbManager->AddDoctor(doctorName, doctorSpecialty, doctorSalary, true)) {
				MessageBox::Show("Doctor added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to add doctor!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void viewPatientsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("View Patients - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void viewDoctorsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("View Doctors - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			this->Close();
		}
	}

	private:
		String^ InputBox(String^ prompt) {
			Form^ form = gcnew Form();
			form->Text = "Input";
			form->Width = 300;
			form->Height = 150;
			form->StartPosition = FormStartPosition::CenterParent;
			form->TopMost = true;

			Label^ label = gcnew Label();
			label->Left = 20;
			label->Top = 20;
			label->Text = prompt;
			label->Width = 250;

			TextBox^ textBox = gcnew TextBox();
			textBox->Left = 20;
			textBox->Top = 50;
			textBox->Width = 250;

			Button^ okButton = gcnew Button();
			okButton->Text = "OK";
			okButton->Left = 120;
			okButton->Top = 80;
			okButton->DialogResult = System::Windows::Forms::DialogResult::OK;

			form->AcceptButton = okButton;
			form->Controls->Add(label);
			form->Controls->Add(textBox);
			form->Controls->Add(okButton);

			form->ShowDialog();
			return textBox->Text;
		}
	};
}
