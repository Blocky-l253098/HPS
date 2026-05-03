#pragma once

#include "DatabaseManager.h"
#include "Login.h"
#include <msclr/marshal_cppstd.h>
#include "AppointmentForm.h"
#include "SurgeryForm.h"
#include "BillingModule.h"

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

		// ── UI Controls ───────────────────────────────────────────────────
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

		   // Info cards in content area
	private: System::Windows::Forms::Panel^ bedCardPanel;
	private: System::Windows::Forms::Panel^ doctorCardPanel;
	private: System::Windows::Forms::Label^ bedCardTitle;
	private: System::Windows::Forms::Label^ bedStatusLabel;
	private: System::Windows::Forms::Label^ doctorCardTitle;
	private: System::Windows::Forms::Label^ doctorAssignedLabel;

	private: System::Windows::Forms::Button^ viewRecordsButton;
	private: System::Windows::Forms::Button^ bookAppointmentButton;
	private: System::Windows::Forms::Button^ bookSurgeryButton;
	private: System::Windows::Forms::Button^ viewBillButton;
	private: System::Windows::Forms::Button^ logoutButton;

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
			if (components) delete components;
			if (dbManager)  delete dbManager;
		}

	private: System::ComponentModel::Container^ components;

		   // ── Helper: sidebar button factory ────────────────────────────────
	private:
		Button^ MakeSidebarButton(String^ text, String^ icon, int yPos)
		{
			Button^ btn = gcnew Button();
			btn->Text = icon + "  " + text;
			btn->Location = System::Drawing::Point(12, yPos);
			btn->Size = System::Drawing::Size(196, 40);
			btn->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			btn->ForeColor = System::Drawing::Color::FromArgb(44, 44, 42);
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->FlatAppearance->MouseOverBackColor =
				System::Drawing::Color::FromArgb(207, 226, 245);
			btn->FlatAppearance->MouseDownBackColor =
				System::Drawing::Color::FromArgb(180, 212, 240);
			btn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular));
			btn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			btn->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			btn->Cursor = System::Windows::Forms::Cursors::Hand;
			btn->TabStop = false;
			return btn;
		}

		// Helper: info card panel
		Panel^ MakeInfoCard(int x, int y, int w, int h,
			String^ titleText, Label^% titleLbl, Label^% valueLbl,
			System::Drawing::Color accent)
		{
			Panel^ card = gcnew Panel();
			card->BackColor = System::Drawing::Color::White;
			card->Location = System::Drawing::Point(x, y);
			card->Size = System::Drawing::Size(w, h);

			// top accent bar
			Panel^ bar = gcnew Panel();
			bar->BackColor = accent;
			bar->Location = System::Drawing::Point(0, 0);
			bar->Size = System::Drawing::Size(w, 4);
			card->Controls->Add(bar);

			titleLbl = gcnew Label();
			titleLbl->AutoSize = false;
			titleLbl->Text = titleText;
			titleLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			titleLbl->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			titleLbl->Location = System::Drawing::Point(14, 14);
			titleLbl->Size = System::Drawing::Size(w - 28, 16);
			card->Controls->Add(titleLbl);

			valueLbl = gcnew Label();
			valueLbl->AutoSize = false;
			valueLbl->Text = L"Not Assigned";
			valueLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			valueLbl->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			valueLbl->Location = System::Drawing::Point(14, 34);
			valueLbl->Size = System::Drawing::Size(w - 28, 22);
			card->Controls->Add(valueLbl);

			return card;
		}

		void InitializeComponent(void)
		{
			// ── Allocate panels ───────────────────────────────────────
			this->sidebarPanel = (gcnew Panel());
			this->contentPanel = (gcnew Panel());
			this->headerPanel = (gcnew Panel());
			this->logoPanel = (gcnew Panel());

			// ── Allocate labels ───────────────────────────────────────
			this->logoLabel = (gcnew Label());
			this->logoSubLabel = (gcnew Label());
			this->sidebarDivider1 = (gcnew Label());
			this->sidebarDivider2 = (gcnew Label());
			this->sectionLabel1 = (gcnew Label());
			this->sectionLabel2 = (gcnew Label());
			this->welcomeLabel = (gcnew Label());
			this->titleLabel = (gcnew Label());
			this->contentTitleLabel = (gcnew Label());
			this->bedCardTitle = (gcnew Label());
			this->bedStatusLabel = (gcnew Label());
			this->doctorCardTitle = (gcnew Label());
			this->doctorAssignedLabel = (gcnew Label());

			// ── Allocate sidebar buttons ──────────────────────────────
			this->viewRecordsButton = MakeSidebarButton(L"View My Records", L"◉", 108);
			this->bookAppointmentButton = MakeSidebarButton(L"Book Appointment", L"✚", 152);
			this->bookSurgeryButton = MakeSidebarButton(L"Book Surgery", L"✦", 240);
			this->viewBillButton = MakeSidebarButton(L"View Bill", L"$", 284);
			this->logoutButton = (gcnew Button());

			this->SuspendLayout();

			// ══════════════════════════════════════════════════════════
			// SIDEBAR
			// ══════════════════════════════════════════════════════════
			this->sidebarPanel->BackColor = System::Drawing::Color::White;
			this->sidebarPanel->Location = System::Drawing::Point(0, 0);
			this->sidebarPanel->Size = System::Drawing::Size(220, 680);

			// ── Logo block ────────────────────────────────────────────
			this->logoPanel->BackColor = System::Drawing::Color::FromArgb(24, 95, 165);
			this->logoPanel->Location = System::Drawing::Point(0, 0);
			this->logoPanel->Size = System::Drawing::Size(220, 72);

			this->logoLabel->AutoSize = false;
			this->logoLabel->Text = L"HPS Hospital";
			this->logoLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Bold));
			this->logoLabel->ForeColor = System::Drawing::Color::White;
			this->logoLabel->Location = System::Drawing::Point(16, 12);
			this->logoLabel->Size = System::Drawing::Size(190, 24);
			this->logoLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			this->logoSubLabel->AutoSize = false;
			this->logoSubLabel->Text = L"Patient Dashboard";
			this->logoSubLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->logoSubLabel->ForeColor = System::Drawing::Color::FromArgb(180, 212, 240);
			this->logoSubLabel->Location = System::Drawing::Point(16, 38);
			this->logoSubLabel->Size = System::Drawing::Size(190, 18);

			this->logoPanel->Controls->Add(this->logoLabel);
			this->logoPanel->Controls->Add(this->logoSubLabel);

			// ── Section 1: MY HEALTH ──────────────────────────────────
			this->sectionLabel1->AutoSize = false;
			this->sectionLabel1->Text = L"MY HEALTH";
			this->sectionLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel1->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel1->Location = System::Drawing::Point(16, 88);
			this->sectionLabel1->Size = System::Drawing::Size(180, 16);

			// viewRecordsButton y=108, bookAppointmentButton y=152

			// ── Divider 1 ─────────────────────────────────────────────
			this->sidebarDivider1->AutoSize = false;
			this->sidebarDivider1->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider1->Location = System::Drawing::Point(12, 202);
			this->sidebarDivider1->Size = System::Drawing::Size(196, 1);

			// ── Section 2: PROCEDURES ─────────────────────────────────
			this->sectionLabel2->AutoSize = false;
			this->sectionLabel2->Text = L"PROCEDURES & BILLING";
			this->sectionLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel2->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel2->Location = System::Drawing::Point(16, 214);
			this->sectionLabel2->Size = System::Drawing::Size(180, 16);

			// bookSurgeryButton y=240, viewBillButton y=284

			// ── Divider 2 ─────────────────────────────────────────────
			this->sidebarDivider2->AutoSize = false;
			this->sidebarDivider2->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider2->Location = System::Drawing::Point(12, 336);
			this->sidebarDivider2->Size = System::Drawing::Size(196, 1);

			// ── Logout ────────────────────────────────────────────────
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
			this->logoutButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::logoutButton_Click);

			// ── Wire events ───────────────────────────────────────────
			this->viewRecordsButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::viewRecordsButton_Click);
			this->bookAppointmentButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::bookAppointmentButton_Click);
			this->bookSurgeryButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::bookSurgeryButton_Click);
			this->viewBillButton->Click += gcnew System::EventHandler(this, &PatientDashboardForm::viewBillButton_Click);

			// ── Add to sidebarPanel ───────────────────────────────────
			this->sidebarPanel->Controls->Add(this->logoPanel);
			this->sidebarPanel->Controls->Add(this->sectionLabel1);
			this->sidebarPanel->Controls->Add(this->viewRecordsButton);
			this->sidebarPanel->Controls->Add(this->bookAppointmentButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider1);
			this->sidebarPanel->Controls->Add(this->sectionLabel2);
			this->sidebarPanel->Controls->Add(this->bookSurgeryButton);
			this->sidebarPanel->Controls->Add(this->viewBillButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider2);
			this->sidebarPanel->Controls->Add(this->logoutButton);

			// ══════════════════════════════════════════════════════════
			// HEADER
			// ══════════════════════════════════════════════════════════
			this->headerPanel->BackColor = System::Drawing::Color::White;
			this->headerPanel->Location = System::Drawing::Point(220, 0);
			this->headerPanel->Size = System::Drawing::Size(860, 64);

			this->titleLabel->AutoSize = false;
			this->titleLabel->Text = L"Patient Dashboard";
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->titleLabel->Location = System::Drawing::Point(24, 10);
			this->titleLabel->Size = System::Drawing::Size(400, 28);
			this->titleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			this->welcomeLabel->AutoSize = false;
			this->welcomeLabel->Text = L"Welcome, Patient!";
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->welcomeLabel->Location = System::Drawing::Point(24, 38);
			this->welcomeLabel->Size = System::Drawing::Size(300, 18);

			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Controls->Add(this->welcomeLabel);

			// ══════════════════════════════════════════════════════════
			// CONTENT PANEL
			// ══════════════════════════════════════════════════════════
			this->contentPanel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->contentPanel->Location = System::Drawing::Point(220, 64);
			this->contentPanel->Size = System::Drawing::Size(860, 616);

			// ── Section heading ───────────────────────────────────────
			this->contentTitleLabel->AutoSize = false;
			this->contentTitleLabel->Text = L"YOUR OVERVIEW";
			this->contentTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->contentTitleLabel->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->contentTitleLabel->Location = System::Drawing::Point(20, 20);
			this->contentTitleLabel->Size = System::Drawing::Size(820, 16);

			// ── Info Cards ────────────────────────────────────────────
			// Bed Card
			this->bedCardPanel = gcnew Panel();
			this->bedCardPanel->BackColor = System::Drawing::Color::White;
			this->bedCardPanel->Location = System::Drawing::Point(20, 46);
			this->bedCardPanel->Size = System::Drawing::Size(390, 72);

			Panel^ bedBar = gcnew Panel();
			bedBar->BackColor = System::Drawing::Color::FromArgb(24, 95, 165);
			bedBar->Location = System::Drawing::Point(0, 0);
			bedBar->Size = System::Drawing::Size(390, 4);
			this->bedCardPanel->Controls->Add(bedBar);

			this->bedCardTitle->AutoSize = false;
			this->bedCardTitle->Text = L"ASSIGNED BED";
			this->bedCardTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->bedCardTitle->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->bedCardTitle->Location = System::Drawing::Point(14, 14);
			this->bedCardTitle->Size = System::Drawing::Size(360, 16);

			this->bedStatusLabel->AutoSize = false;
			this->bedStatusLabel->Text = L"Not Assigned";
			this->bedStatusLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->bedStatusLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->bedStatusLabel->Location = System::Drawing::Point(14, 34);
			this->bedStatusLabel->Size = System::Drawing::Size(360, 24);

			this->bedCardPanel->Controls->Add(this->bedCardTitle);
			this->bedCardPanel->Controls->Add(this->bedStatusLabel);

			// Doctor Card
			this->doctorCardPanel = gcnew Panel();
			this->doctorCardPanel->BackColor = System::Drawing::Color::White;
			this->doctorCardPanel->Location = System::Drawing::Point(430, 46);
			this->doctorCardPanel->Size = System::Drawing::Size(410, 72);

			Panel^ docBar = gcnew Panel();
			docBar->BackColor = System::Drawing::Color::FromArgb(55, 138, 221);
			docBar->Location = System::Drawing::Point(0, 0);
			docBar->Size = System::Drawing::Size(410, 4);
			this->doctorCardPanel->Controls->Add(docBar);

			this->doctorCardTitle->AutoSize = false;
			this->doctorCardTitle->Text = L"ASSIGNED DOCTOR";
			this->doctorCardTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->doctorCardTitle->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->doctorCardTitle->Location = System::Drawing::Point(14, 14);
			this->doctorCardTitle->Size = System::Drawing::Size(380, 16);

			this->doctorAssignedLabel->AutoSize = false;
			this->doctorAssignedLabel->Text = L"Not Assigned";
			this->doctorAssignedLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->doctorAssignedLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->doctorAssignedLabel->Location = System::Drawing::Point(14, 34);
			this->doctorAssignedLabel->Size = System::Drawing::Size(380, 24);

			this->doctorCardPanel->Controls->Add(this->doctorCardTitle);
			this->doctorCardPanel->Controls->Add(this->doctorAssignedLabel);

			// ── Add everything to contentPanel ────────────────────────
			this->contentPanel->Controls->Add(this->contentTitleLabel);
			this->contentPanel->Controls->Add(this->bedCardPanel);
			this->contentPanel->Controls->Add(this->doctorCardPanel);

			// ══════════════════════════════════════════════════════════
			// FORM
			// ══════════════════════════════════════════════════════════
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->ClientSize = System::Drawing::Size(1080, 680);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"PatientDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Patient Dashboard";

			this->Controls->Add(this->sidebarPanel);
			this->Controls->Add(this->headerPanel);
			this->Controls->Add(this->contentPanel);

			this->ResumeLayout(false);
			this->PerformLayout();
		}

		// ── Helpers ───────────────────────────────────────────────────────
	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			welcomeLabel->Text = "Welcome, " + username + " (Patient)";
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
			label->Left = 20; label->Top = 20; label->Text = prompt; label->Width = 250;

			TextBox^ textBox = gcnew TextBox();
			textBox->Left = 20; textBox->Top = 50; textBox->Width = 250;

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

		// ══════════════════════════════════════════════════════════════════
		// EVENT HANDLERS — all logic identical to original, untouched
		// ══════════════════════════════════════════════════════════════════

	private: void ViewPatientRecords(String^ pIdStr) {
		if (dbManager->Connect()) {
			sqlite3_stmt* stmt;
			std::string pId = msclr::interop::marshal_as<std::string>(pIdStr);

			std::string medQuery = "SELECT Diagnosis, Symptoms, Treatment, DateRecorded FROM MedicalRecords WHERE PatientID=" + pId + ";";
			std::string rxQuery = "SELECT MedicineDetails, Instructions, DateIssued FROM Prescriptions WHERE PatientID=" + pId + ";";

			String^ recordLog = "--- YOUR MEDICAL RECORDS ---\n\n";

			if (sqlite3_prepare_v2(dbManager->getDB(), medQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					String^ diag = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
					String^ symp = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
					String^ treat = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
					String^ date = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
					recordLog += "[" + date + "]\n";
					recordLog += "Diagnosis: " + diag + "\n";
					recordLog += "Symptoms: " + symp + "\n";
					recordLog += "Treatment: " + treat + "\n\n";
				}
			}
			sqlite3_finalize(stmt);

			recordLog += "\n--- YOUR PRESCRIPTIONS ---\n\n";
			if (sqlite3_prepare_v2(dbManager->getDB(), rxQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					String^ meds = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
					String^ inst = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
					String^ rxDate = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
					recordLog += "[" + rxDate + "]\n";
					recordLog += "Medication: " + meds + "\n";
					recordLog += "Instructions: " + inst + "\n\n";
				}
			}
			sqlite3_finalize(stmt);

			MessageBox::Show(recordLog, "Full Medical Profile", MessageBoxButtons::OK, MessageBoxIcon::Information);
			dbManager->Disconnect();
		}
	}

	private: System::Void viewRecordsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ pIdStr = InputBox("Enter Your Patient ID:");
		if (String::IsNullOrEmpty(pIdStr)) return;
		ViewPatientRecords(pIdStr);
	}

	private: System::Void bookAppointmentButton_Click(System::Object^ sender, System::EventArgs^ e) {
		AppointmentForm^ form = gcnew AppointmentForm();
		form->ShowDialog();
	}

	private: System::Void viewBillButton_Click(System::Object^ sender, System::EventArgs^ e) {
		HospitalManagment::BillingModule^ form1 = gcnew HospitalManagment::BillingModule();
		form1->ShowDialog();
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to logout?", "Logout",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			this->Close();
		}
	}

	private: System::Void bookSurgeryButton_Click(System::Object^ sender, System::EventArgs^ e) {
		SurgeryForm^ form = gcnew SurgeryForm();
		form->ShowDialog();
	}
	};
}