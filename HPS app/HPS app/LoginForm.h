#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>
#include "AdminDashboardForm.h"
#include "DoctorDashboardForm.h"
#include "PatientDashboardForm.h"
#include <cstdlib>
#include <ctime>

namespace HPSapp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class LoginForm : public Form
	{
	private:
		DatabaseManager* dbManager;
		Login* loginSession;
		int captchaNum1;
		int captchaNum2;
		int correctAnswer;
		bool captchaPassed;

	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::Panel^ formPanel;
	private: System::Windows::Forms::TextBox^ usernameTextBox;
	private: System::Windows::Forms::TextBox^ passwordTextBox;
	private: System::Windows::Forms::Button^ loginButton;
	private: System::Windows::Forms::Label^ usernameLabel;
	private: System::Windows::Forms::Label^ passwordLabel;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ subtitleLabel;
	private: System::Windows::Forms::Label^ errorLabel;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ captchaLabel;
	private: System::Windows::Forms::TextBox^ captchaTextBox;
	private: System::Windows::Forms::Button^ refreshCaptchaButton;

	public:
		LoginForm(void)
		{
			dbManager = new DatabaseManager();
			loginSession = new Login();
			captchaPassed = false;
			srand((unsigned)time(NULL));
			InitializeComponent();
			GenerateNewCaptcha();
			ApplyModernStyle();
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

	private: System::ComponentModel::Container^ components;

	private:
		void ApplyModernStyle()
		{
			// Form background
			this->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);

			// Main Panel
			mainPanel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);

			// Form Panel - white card with subtle shadow effect via border
			formPanel->BackColor = System::Drawing::Color::White;

			// Title
			titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			titleLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);

			// Subtitle
			subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			subtitleLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);

			// Labels
			usernameLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			usernameLabel->ForeColor = System::Drawing::Color::FromArgb(95, 94, 90);

			passwordLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			passwordLabel->ForeColor = System::Drawing::Color::FromArgb(95, 94, 90);

			captchaLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			captchaLabel->ForeColor = System::Drawing::Color::FromArgb(12, 68, 124);
			captchaLabel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);

			// TextBoxes
			usernameTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			usernameTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);
			usernameTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			usernameTextBox->ForeColor = System::Drawing::Color::FromArgb(44, 44, 42);

			passwordTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			passwordTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);
			passwordTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			passwordTextBox->ForeColor = System::Drawing::Color::FromArgb(44, 44, 42);

			captchaTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			captchaTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);
			captchaTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			captchaTextBox->ForeColor = System::Drawing::Color::FromArgb(44, 44, 42);

			// Refresh button
			refreshCaptchaButton->BackColor = System::Drawing::Color::FromArgb(241, 239, 232);
			refreshCaptchaButton->ForeColor = System::Drawing::Color::FromArgb(95, 94, 90);
			refreshCaptchaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			refreshCaptchaButton->FlatStyle = FlatStyle::Flat;
			refreshCaptchaButton->FlatAppearance->BorderSize = 1;
			refreshCaptchaButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(211, 209, 199);
			refreshCaptchaButton->Cursor = System::Windows::Forms::Cursors::Hand;

			// Error label
			errorLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);

			// Login button
			loginButton->BackColor = System::Drawing::Color::FromArgb(24, 95, 165);
			loginButton->ForeColor = System::Drawing::Color::White;
			loginButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			loginButton->FlatStyle = FlatStyle::Flat;
			loginButton->FlatAppearance->BorderSize = 0;
			loginButton->Cursor = System::Windows::Forms::Cursors::Hand;
		}

		void GenerateNewCaptcha()
		{
			captchaNum1 = rand() % 50 + 1;
			captchaNum2 = rand() % 50 + 1;
			correctAnswer = captchaNum1 + captchaNum2;
			captchaPassed = false;

			String^ captchaQuestion = "  What is " + captchaNum1.ToString() + " + " + captchaNum2.ToString() + " ?";
			captchaLabel->Text = captchaQuestion;
			captchaTextBox->Clear();
			captchaTextBox->Focus();
		}

	private:
		void InitializeComponent(void)
		{
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->formPanel = (gcnew System::Windows::Forms::Panel());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->subtitleLabel = (gcnew System::Windows::Forms::Label());
			this->usernameLabel = (gcnew System::Windows::Forms::Label());
			this->usernameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->passwordLabel = (gcnew System::Windows::Forms::Label());
			this->passwordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->captchaLabel = (gcnew System::Windows::Forms::Label());
			this->captchaTextBox = (gcnew System::Windows::Forms::TextBox());
			this->refreshCaptchaButton = (gcnew System::Windows::Forms::Button());
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// ── mainPanel ──────────────────────────────────────────────
			this->mainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainPanel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->mainPanel->Name = L"mainPanel";

			// ── formPanel (white card) ─────────────────────────────────
			this->formPanel->BackColor = System::Drawing::Color::White;
			this->formPanel->Location = System::Drawing::Point(70, 30);
			this->formPanel->Name = L"formPanel";
			this->formPanel->Size = System::Drawing::Size(380, 540);
			this->formPanel->TabIndex = 0;

			// ── titleLabel ────────────────────────────────────────────
			this->titleLabel->AutoSize = false;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->titleLabel->Location = System::Drawing::Point(30, 28);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(320, 36);
			this->titleLabel->Text = L"Hospital Management";
			this->titleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			// ── subtitleLabel ─────────────────────────────────────────
			this->subtitleLabel->AutoSize = false;
			this->subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->subtitleLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->subtitleLabel->Location = System::Drawing::Point(30, 66);
			this->subtitleLabel->Name = L"subtitleLabel";
			this->subtitleLabel->Size = System::Drawing::Size(320, 20);
			this->subtitleLabel->Text = L"Sign in to your account";
			this->subtitleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			// ── usernameLabel ─────────────────────────────────────────
			this->usernameLabel->AutoSize = true;
			this->usernameLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->usernameLabel->ForeColor = System::Drawing::Color::FromArgb(95, 94, 90);
			this->usernameLabel->Location = System::Drawing::Point(30, 112);
			this->usernameLabel->Name = L"usernameLabel";
			this->usernameLabel->Text = L"USERNAME";
			this->usernameLabel->TabIndex = 5;

			// ── usernameTextBox ───────────────────────────────────────
			this->usernameTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->usernameTextBox->Location = System::Drawing::Point(30, 132);
			this->usernameTextBox->Name = L"usernameTextBox";
			this->usernameTextBox->Size = System::Drawing::Size(320, 30);
			this->usernameTextBox->TabIndex = 0;
			this->usernameTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);

			// ── passwordLabel ─────────────────────────────────────────
			this->passwordLabel->AutoSize = true;
			this->passwordLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->passwordLabel->ForeColor = System::Drawing::Color::FromArgb(95, 94, 90);
			this->passwordLabel->Location = System::Drawing::Point(30, 186);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Text = L"PASSWORD";
			this->passwordLabel->TabIndex = 6;

			// ── passwordTextBox ───────────────────────────────────────
			this->passwordTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->passwordTextBox->Location = System::Drawing::Point(30, 206);
			this->passwordTextBox->Name = L"passwordTextBox";
			this->passwordTextBox->PasswordChar = '*';
			this->passwordTextBox->Size = System::Drawing::Size(320, 30);
			this->passwordTextBox->TabIndex = 1;
			this->passwordTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);

			// ── captchaLabel (shows the question) ────────────────────
			this->captchaLabel->AutoSize = false;
			this->captchaLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->captchaLabel->ForeColor = System::Drawing::Color::FromArgb(12, 68, 124);
			this->captchaLabel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->captchaLabel->Location = System::Drawing::Point(30, 260);
			this->captchaLabel->Name = L"captchaLabel";
			this->captchaLabel->Size = System::Drawing::Size(320, 26);
			this->captchaLabel->Text = L"  Security Question: 0 + 0 = ?";
			this->captchaLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->captchaLabel->Padding = System::Windows::Forms::Padding(6, 0, 0, 0);

			// ── captchaTextBox ────────────────────────────────────────
			this->captchaTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->captchaTextBox->Location = System::Drawing::Point(30, 296);
			this->captchaTextBox->Name = L"captchaTextBox";
			this->captchaTextBox->Size = System::Drawing::Size(210, 30);
			this->captchaTextBox->TabIndex = 2;
			this->captchaTextBox->BackColor = System::Drawing::Color::FromArgb(248, 249, 252);

			// ── refreshCaptchaButton ──────────────────────────────────
			this->refreshCaptchaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->refreshCaptchaButton->Location = System::Drawing::Point(248, 296);
			this->refreshCaptchaButton->Name = L"refreshCaptchaButton";
			this->refreshCaptchaButton->Size = System::Drawing::Size(102, 30);
			this->refreshCaptchaButton->TabIndex = 3;
			this->refreshCaptchaButton->Text = L"↻ New";
			this->refreshCaptchaButton->UseVisualStyleBackColor = false;
			this->refreshCaptchaButton->Click += gcnew System::EventHandler(this, &LoginForm::refreshCaptchaButton_Click);

			// ── errorLabel ────────────────────────────────────────────
			this->errorLabel->AutoSize = false;
			this->errorLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			this->errorLabel->Location = System::Drawing::Point(30, 344);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(320, 20);
			this->errorLabel->Text = L"";
			this->errorLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			// ── loginButton ───────────────────────────────────────────
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->loginButton->Location = System::Drawing::Point(30, 374);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(320, 44);
			this->loginButton->TabIndex = 4;
			this->loginButton->Text = L"SIGN IN";
			this->loginButton->UseVisualStyleBackColor = false;
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginForm::loginButton_Click);

			// ── pictureBox1 (hidden, reserved) ────────────────────────
			this->pictureBox1->Location = System::Drawing::Point(30, 430);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(320, 1);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;

			// ── Form ──────────────────────────────────────────────────
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->ClientSize = System::Drawing::Size(520, 600);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Hospital Management System";

			// ── Add controls to formPanel ─────────────────────────────
			this->formPanel->Controls->Add(this->titleLabel);
			this->formPanel->Controls->Add(this->subtitleLabel);
			this->formPanel->Controls->Add(this->usernameLabel);
			this->formPanel->Controls->Add(this->usernameTextBox);
			this->formPanel->Controls->Add(this->passwordLabel);
			this->formPanel->Controls->Add(this->passwordTextBox);
			this->formPanel->Controls->Add(this->captchaLabel);
			this->formPanel->Controls->Add(this->captchaTextBox);
			this->formPanel->Controls->Add(this->refreshCaptchaButton);
			this->formPanel->Controls->Add(this->errorLabel);
			this->formPanel->Controls->Add(this->loginButton);
			this->formPanel->Controls->Add(this->pictureBox1);

			// ── Add formPanel to mainPanel, mainPanel to Form ─────────
			this->mainPanel->Controls->Add(this->formPanel);
			this->Controls->Add(this->mainPanel);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		// ── Event Handlers (backend untouched) ────────────────────────────

	private: System::Void refreshCaptchaButton_Click(System::Object^ sender, System::EventArgs^ e) {
		GenerateNewCaptcha();
	}

	private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ username = usernameTextBox->Text;
		String^ password = passwordTextBox->Text;
		String^ captchaAnswer = captchaTextBox->Text;

		if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password)) {
			errorLabel->Text = L"Username and password are required!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			return;
		}

		if (String::IsNullOrEmpty(captchaAnswer)) {
			errorLabel->Text = L"Please answer the security question!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			return;
		}

		int userAnswer;
		try {
			userAnswer = System::Int32::Parse(captchaAnswer);
		}
		catch (System::FormatException^) {
			errorLabel->Text = L"Security answer must be a number!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			captchaTextBox->Clear();
			GenerateNewCaptcha();
			return;
		}

		if (userAnswer != correctAnswer) {
			errorLabel->Text = L"Incorrect security answer. Please try again!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			captchaTextBox->Clear();
			GenerateNewCaptcha();
			return;
		}

		std::string unmanaged_username = msclr::interop::marshal_as<std::string>(username);
		std::string unmanaged_password = msclr::interop::marshal_as<std::string>(password);

		if (!dbManager->Connect()) {
			errorLabel->Text = L"Database connection failed!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			return;
		}

		std::string role = dbManager->ValidateUser(unmanaged_username, unmanaged_password);

		if (role == "None") {
			errorLabel->Text = L"Invalid username or password!";
			errorLabel->ForeColor = System::Drawing::Color::FromArgb(226, 75, 74);
			usernameTextBox->Clear();
			passwordTextBox->Clear();
			captchaTextBox->Clear();
			GenerateNewCaptcha();
			dbManager->Disconnect();
			return;
		}

		// Database سے Doctor یا Patient کی ID fetch کریں
		int userID = 0;
		sqlite3_stmt* stmt;
		
		if (role == "Doctor") {
			// Doctor کی ID لیں
			std::string queryID = "SELECT DoctorID FROM Doctors WHERE Name='" + unmanaged_username + "' LIMIT 1;";
			if (sqlite3_prepare_v2(dbManager->getDB(), queryID.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				if (sqlite3_step(stmt) == SQLITE_ROW) {
					userID = sqlite3_column_int(stmt, 0);
				}
				sqlite3_finalize(stmt);
			}
		}
		else if (role == "Patient") {
			// Patient کی ID لیں
			std::string queryID = "SELECT PatientID FROM Patients WHERE Name='" + unmanaged_username + "' LIMIT 1;";
			if (sqlite3_prepare_v2(dbManager->getDB(), queryID.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				if (sqlite3_step(stmt) == SQLITE_ROW) {
					userID = sqlite3_column_int(stmt, 0);
				}
				sqlite3_finalize(stmt);
			}
		}

		loginSession->setUsername(unmanaged_username);
		loginSession->setPassword(unmanaged_password);
		loginSession->setUserRole(role);
		loginSession->setUserID(userID);  // ✅ ID set کریں

		errorLabel->Text = "";

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
		captchaTextBox->Clear();
		GenerateNewCaptcha();
	}

	public:
		Login* getLoginSession() {
			return loginSession;
		}
	};
}