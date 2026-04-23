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

	public ref class DoctorDashboardForm : public Form
	{
	private:
		DatabaseManager* dbManager;
		Login* currentUser;

	private: System::Windows::Forms::Label^ welcomeLabel;
	private: System::Windows::Forms::Button^ viewAppointmentsButton;
	private: System::Windows::Forms::Button^ bookAppointmentButton;
	private: System::Windows::Forms::Button^ updateStatusButton;
	private: System::Windows::Forms::Button^ logoutButton;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::DataGridView^ appointmentsGridView;

	public:
		DoctorDashboardForm(Login* user)
		{
			currentUser = user;
			dbManager = new DatabaseManager();
			InitializeComponent();
			UpdateWelcomeLabel();
		}

	protected:
		~DoctorDashboardForm()
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
			this->viewAppointmentsButton = (gcnew System::Windows::Forms::Button());
			this->bookAppointmentButton = (gcnew System::Windows::Forms::Button());
			this->updateStatusButton = (gcnew System::Windows::Forms::Button());
			this->logoutButton = (gcnew System::Windows::Forms::Button());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->appointmentsGridView = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGridView))->BeginInit();
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
			this->titleLabel->Text = L"Doctor Dashboard";

			// welcomeLabel
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->welcomeLabel->Location = System::Drawing::Point(20, 60);
			this->welcomeLabel->Name = L"welcomeLabel";
			this->welcomeLabel->Size = System::Drawing::Size(200, 18);
			this->welcomeLabel->TabIndex = 1;
			this->welcomeLabel->Text = L"Welcome, Doctor!";

			// viewAppointmentsButton
			this->viewAppointmentsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->viewAppointmentsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->viewAppointmentsButton->ForeColor = System::Drawing::Color::White;
			this->viewAppointmentsButton->Location = System::Drawing::Point(20, 100);
			this->viewAppointmentsButton->Name = L"viewAppointmentsButton";
			this->viewAppointmentsButton->Size = System::Drawing::Size(150, 40);
			this->viewAppointmentsButton->TabIndex = 2;
			this->viewAppointmentsButton->Text = L"View Appointments";
			this->viewAppointmentsButton->UseVisualStyleBackColor = false;
			this->viewAppointmentsButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::viewAppointmentsButton_Click);

			// bookAppointmentButton
			this->bookAppointmentButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->bookAppointmentButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bookAppointmentButton->ForeColor = System::Drawing::Color::White;
			this->bookAppointmentButton->Location = System::Drawing::Point(180, 100);
			this->bookAppointmentButton->Name = L"bookAppointmentButton";
			this->bookAppointmentButton->Size = System::Drawing::Size(150, 40);
			this->bookAppointmentButton->TabIndex = 3;
			this->bookAppointmentButton->Text = L"Book Appointment";
			this->bookAppointmentButton->UseVisualStyleBackColor = false;
			this->bookAppointmentButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::bookAppointmentButton_Click);

			// updateStatusButton
			this->updateStatusButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(204)), static_cast<System::Int32>(static_cast<System::Byte>(102)));
			this->updateStatusButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->updateStatusButton->ForeColor = System::Drawing::Color::White;
			this->updateStatusButton->Location = System::Drawing::Point(340, 100);
			this->updateStatusButton->Name = L"updateStatusButton";
			this->updateStatusButton->Size = System::Drawing::Size(150, 40);
			this->updateStatusButton->TabIndex = 4;
			this->updateStatusButton->Text = L"Update Availability";
			this->updateStatusButton->UseVisualStyleBackColor = false;
			this->updateStatusButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::updateStatusButton_Click);

			// logoutButton
			this->logoutButton->BackColor = System::Drawing::Color::Red;
			this->logoutButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->logoutButton->ForeColor = System::Drawing::Color::White;
			this->logoutButton->Location = System::Drawing::Point(500, 100);
			this->logoutButton->Name = L"logoutButton";
			this->logoutButton->Size = System::Drawing::Size(120, 40);
			this->logoutButton->TabIndex = 5;
			this->logoutButton->Text = L"Logout";
			this->logoutButton->UseVisualStyleBackColor = false;
			this->logoutButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::logoutButton_Click);

			// appointmentsGridView
			this->appointmentsGridView->BackgroundColor = System::Drawing::Color::White;
			this->appointmentsGridView->Location = System::Drawing::Point(20, 160);
			this->appointmentsGridView->Name = L"appointmentsGridView";
			this->appointmentsGridView->ReadOnly = true;
			this->appointmentsGridView->Size = System::Drawing::Size(600, 300);
			this->appointmentsGridView->TabIndex = 6;

			// DoctorDashboardForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(650, 500);
			this->Controls->Add(this->appointmentsGridView);
			this->Controls->Add(this->logoutButton);
			this->Controls->Add(this->updateStatusButton);
			this->Controls->Add(this->bookAppointmentButton);
			this->Controls->Add(this->viewAppointmentsButton);
			this->Controls->Add(this->welcomeLabel);
			this->Controls->Add(this->titleLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"DoctorDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Doctor Dashboard";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Doctor)!";
		}

	private: System::Void viewAppointmentsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("View Appointments - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void bookAppointmentButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("Book Appointment - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void updateStatusButton_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("Update Availability - Feature Coming Soon!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			this->Close();
		}
	}
	};
}
