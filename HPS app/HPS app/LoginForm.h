#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>
#include "AdminDashboardForm.h"
#include "DoctorDashboardForm.h"
#include "PatientDashboardForm.h"

namespace HPSapp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LoginForm : public Form
	{
	private:
		DatabaseManager* dbManager;
		Login* loginSession;

	private: System::Windows::Forms::TextBox^ usernameTextBox;
	private: System::Windows::Forms::TextBox^ passwordTextBox;
	private: System::Windows::Forms::Button^ loginButton;
	private: System::Windows::Forms::Label^ usernameLabel;
	private: System::Windows::Forms::Label^ passwordLabel;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ errorLabel;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	public:
		LoginForm(void)
		{
			dbManager = new DatabaseManager();
			loginSession = new Login();
			InitializeComponent();
		}

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
			if (dbManager) delete dbManager;
			if (loginSession) delete loginSession;
		}

	private: System::ComponentModel::Container ^components;

	private:
		void InitializeComponent(void)
		{
			this->usernameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->passwordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->usernameLabel = (gcnew System::Windows::Forms::Label());
			this->passwordLabel = (gcnew System::Windows::Forms::Label());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// usernameTextBox
			this->usernameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->usernameTextBox->Location = System::Drawing::Point(200, 120);
			this->usernameTextBox->Name = L"usernameTextBox";
			this->usernameTextBox->Size = System::Drawing::Size(250, 26);
			this->usernameTextBox->TabIndex = 0;

			// passwordTextBox
			this->passwordTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->passwordTextBox->Location = System::Drawing::Point(200, 170);
			this->passwordTextBox->Name = L"passwordTextBox";
			this->passwordTextBox->PasswordChar = '*';
			this->passwordTextBox->Size = System::Drawing::Size(250, 26);
			this->passwordTextBox->TabIndex = 1;

			// loginButton
			this->loginButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loginButton->ForeColor = System::Drawing::Color::White;
			this->loginButton->Location = System::Drawing::Point(200, 230);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(250, 40);
			this->loginButton->TabIndex = 2;
			this->loginButton->Text = L"Login";
			this->loginButton->UseVisualStyleBackColor = false;
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginForm::loginButton_Click);

			// usernameLabel
			this->usernameLabel->AutoSize = true;
			this->usernameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->usernameLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->usernameLabel->Location = System::Drawing::Point(200, 95);
			this->usernameLabel->Name = L"usernameLabel";
			this->usernameLabel->Size = System::Drawing::Size(81, 18);
			this->usernameLabel->TabIndex = 3;
			this->usernameLabel->Text = L"Username:";

			// passwordLabel
			this->passwordLabel->AutoSize = true;
			this->passwordLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->passwordLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->passwordLabel->Location = System::Drawing::Point(200, 145);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Size = System::Drawing::Size(76, 18);
			this->passwordLabel->TabIndex = 4;
			this->passwordLabel->Text = L"Password:";

			// titleLabel
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(102)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->titleLabel->Location = System::Drawing::Point(150, 20);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(350, 31);
			this->titleLabel->TabIndex = 5;
			this->titleLabel->Text = L"Hospital Management System";

			// errorLabel
			this->errorLabel->AutoSize = true;
			this->errorLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->errorLabel->ForeColor = System::Drawing::Color::Red;
			this->errorLabel->Location = System::Drawing::Point(200, 280);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(0, 17);
			this->errorLabel->TabIndex = 6;

			// pictureBox1
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;

			// LoginForm
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(650, 350);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->errorLabel);
			this->Controls->Add(this->titleLabel);
			this->Controls->Add(this->passwordLabel);
			this->Controls->Add(this->usernameLabel);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->passwordTextBox);
			this->Controls->Add(this->usernameTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Login";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ username = usernameTextBox->Text;
		String^ password = passwordTextBox->Text;

		if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password)) {
			errorLabel->Text = L"Username and password are required!";
			errorLabel->ForeColor = System::Drawing::Color::Red;
			return;
		}

		// Convert managed strings to unmanaged strings
		std::string unmanaged_username = msclr::interop::marshal_as<std::string>(username);
		std::string unmanaged_password = msclr::interop::marshal_as<std::string>(password);

		// Connect to database if not already connected
		if (!dbManager->Connect()) {
			errorLabel->Text = L"Database connection failed!";
			errorLabel->ForeColor = System::Drawing::Color::Red;
			return;
		}

		// Validate user credentials
		std::string role = dbManager->ValidateUser(unmanaged_username, unmanaged_password);

		if (role == "None") {
			errorLabel->Text = L"Invalid username or password!";
			errorLabel->ForeColor = System::Drawing::Color::Red;
			usernameTextBox->Clear();
			passwordTextBox->Clear();
			return;
		}

		// Login successful
		loginSession->setUsername(unmanaged_username);
		loginSession->setPassword(unmanaged_password);
		loginSession->setUserRole(role);

		errorLabel->Text = "";

		// Open appropriate dashboard based on role
		System::String^ managedRole = gcnew System::String(role.c_str());

		if (managedRole == "Admin") {
			HPSapp::AdminDashboardForm^ adminForm = gcnew HPSapp::AdminDashboardForm(loginSession);
			this->Hide();
			adminForm->ShowDialog();
			this->Show();
		}
		else if (managedRole == "Doctor") {
			HPSapp::DoctorDashboardForm^ doctorForm = gcnew HPSapp::DoctorDashboardForm(loginSession);
			this->Hide();
			doctorForm->ShowDialog();
			this->Show();
		}
		else if (managedRole == "Patient") {
			HPSapp::PatientDashboardForm^ patientForm = gcnew HPSapp::PatientDashboardForm(loginSession);
			this->Hide();
			patientForm->ShowDialog();
			this->Show();
		}

		dbManager->Disconnect();
		usernameTextBox->Clear();
		passwordTextBox->Clear();
	}

	public:
		Login* getLoginSession() {
			return loginSession;
		}
	};
}
