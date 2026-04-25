#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>
#include "AppointmentForm.h"
#include "SurgeryForm.h"

namespace HPSapp 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class PatientDashboardForm : public Form
	{
	private:
		DatabaseManager* dbManager;
		Login* currentUser;

	private: System::Windows::Forms::Label^ welcomeLabel;
	private: System::Windows::Forms::Button^ viewRecordsButton;
	private: System::Windows::Forms::Button^ bookAppointmentButton;
	private: System::Windows::Forms::Button^ bookSurgeryButton;
	private: System::Windows::Forms::Button^ viewBillButton;
	private: System::Windows::Forms::Button^ logoutButton;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ bedStatusLabel;
	private: System::Windows::Forms::Label^ doctorAssignedLabel;

	public:
		PatientDashboardForm(Login* user)
		{
			currentUser = user;
			dbManager = new DatabaseManager();
			InitializeComponent();
			UpdateWelcomeLabel();
		}

	protected:
		~PatientDashboardForm()
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
			this->viewRecordsButton = (gcnew System::Windows::Forms::Button());
			this->bookAppointmentButton = (gcnew System::Windows::Forms::Button());
			this->bookSurgeryButton = (gcnew System::Windows::Forms::Button());
			this->viewBillButton = (gcnew System::Windows::Forms::Button());
			this->logoutButton = (gcnew System::Windows::Forms::Button());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->bedStatusLabel = (gcnew System::Windows::Forms::Label());
			this->doctorAssignedLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();

			// titleLabel
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->titleLabel->Location = System::Drawing::Point(20, 20);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(320, 29);
			this->titleLabel->TabIndex = 0;
			this->titleLabel->Text = L"Patient Dashboard";

			// welcomeLabel
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->welcomeLabel->Location = System::Drawing::Point(20, 60);
			this->welcomeLabel->Name = L"welcomeLabel";
			this->welcomeLabel->Size = System::Drawing::Size(200, 18);
			this->welcomeLabel->TabIndex = 1;
			this->welcomeLabel->Text = L"Welcome, Patient!";

			// bedStatusLabel
			this->bedStatusLabel->AutoSize = true;
			this->bedStatusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bedStatusLabel->Location = System::Drawing::Point(20, 90);
			this->bedStatusLabel->Name = L"bedStatusLabel";
			this->bedStatusLabel->Size = System::Drawing::Size(150, 17);
			this->bedStatusLabel->TabIndex = 7;
			this->bedStatusLabel->Text = L"Assigned Bed: Not Assigned";

			// doctorAssignedLabel
			this->doctorAssignedLabel->AutoSize = true;
			this->doctorAssignedLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->doctorAssignedLabel->Location = System::Drawing::Point(20, 110);
			this->doctorAssignedLabel->Name = L"doctorAssignedLabel";
			this->doctorAssignedLabel->Size = System::Drawing::Size(200, 17);
			this->doctorAssignedLabel->TabIndex = 8;
			this->doctorAssignedLabel->Text = L"Assigned Doctor: Not Assigned";

			// viewRecordsButton
			this->viewRecordsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->viewRecordsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewRecordsButton->ForeColor = System::Drawing::Color::White;
			this->viewRecordsButton->Location = System::Drawing::Point(20, 150);
			this->viewRecordsButton->Name = L"viewRecordsButton";
			this->viewRecordsButton->Size = System::Drawing::Size(150, 40);
			this->viewRecordsButton->TabIndex = 2;
			this->viewRecordsButton->Text = L"View Records";
			this->viewRecordsButton->UseVisualStyleBackColor = false;
			this->viewRecordsButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::viewRecordsButton_Click);

			// bookAppointmentButton
			this->bookAppointmentButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->bookAppointmentButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bookAppointmentButton->ForeColor = System::Drawing::Color::White;
			this->bookAppointmentButton->Location = System::Drawing::Point(180, 150);
			this->bookAppointmentButton->Name = L"bookAppointmentButton";
			this->bookAppointmentButton->Size = System::Drawing::Size(150, 40);
			this->bookAppointmentButton->TabIndex = 3;
			this->bookAppointmentButton->Text = L"Book Appointment";
			this->bookAppointmentButton->UseVisualStyleBackColor = false;
			this->bookAppointmentButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::bookAppointmentButton_Click);

			// SugeryButton
			this->bookSurgeryButton->BackColor = System::Drawing::Color::FromArgb(153, 0, 0);
			this->bookSurgeryButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->bookSurgeryButton->ForeColor = System::Drawing::Color::White;
			this->bookSurgeryButton->Location = System::Drawing::Point(340, 150);
			this->bookSurgeryButton->Name = L"bookSurgeryButton";
			this->bookSurgeryButton->Size = System::Drawing::Size(150, 40);
			this->bookSurgeryButton->Text = L"Book Surgery";
			this->bookSurgeryButton->UseVisualStyleBackColor = false;
			this->bookSurgeryButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::bookSurgeryButton_Click);

			// viewBillButton
			this->viewBillButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(204)), static_cast<System::Int32>(static_cast<System::Byte>(102)));
			this->viewBillButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewBillButton->ForeColor = System::Drawing::Color::White;
			this->viewBillButton->Location = System::Drawing::Point(180, 200);
			this->viewBillButton->Name = L"viewBillButton";
			this->viewBillButton->Size = System::Drawing::Size(120, 40);
			this->viewBillButton->TabIndex = 4;
			this->viewBillButton->Text = L"View Bill";
			this->viewBillButton->UseVisualStyleBackColor = false;
			this->viewBillButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::viewBillButton_Click);

			// logoutButton
			this->logoutButton->BackColor = System::Drawing::Color::Red;
			this->logoutButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->logoutButton->ForeColor = System::Drawing::Color::White;
			this->logoutButton->Location = System::Drawing::Point(470, 150);
			this->logoutButton->Name = L"logoutButton";
			this->logoutButton->Size = System::Drawing::Size(120, 40);
			this->logoutButton->TabIndex = 5;
			this->logoutButton->Text = L"Logout";
			this->logoutButton->UseVisualStyleBackColor = false;
			this->logoutButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::logoutButton_Click);

			// PatientDashboardForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(650, 250);
			this->Controls->Add(this->doctorAssignedLabel);
			this->Controls->Add(this->bedStatusLabel);
			this->Controls->Add(this->logoutButton);
			this->Controls->Add(this->viewBillButton);
			this->Controls->Add(this->bookAppointmentButton);
			this->Controls->Add(this->bookSurgeryButton);
			this->Controls->Add(this->viewRecordsButton);
			this->Controls->Add(this->welcomeLabel);
			this->Controls->Add(this->titleLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"PatientDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Patient Dashboard";
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Patient)!";
		}

	private: System::Void viewRecordsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("View Medical Records - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void bookAppointmentButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		AppointmentForm^ form = gcnew AppointmentForm();
		form->ShowDialog();
	}
 
	private: System::Void viewBillButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("View Billing Information - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) 
		{
			this->Close();
		}
	}

	private: System::Void bookSurgeryButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SurgeryForm^ form = gcnew SurgeryForm();
		form->ShowDialog();
	}

	};
}
