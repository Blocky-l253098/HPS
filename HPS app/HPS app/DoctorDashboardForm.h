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
	private: System::Windows::Forms::Label^ doctorIDLabel;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ contentTitleLabel;

	private: System::Windows::Forms::Button^ viewAppointmentsButton;
	private: System::Windows::Forms::Button^ bookAppointmentButton;
	private: System::Windows::Forms::Button^ updateStatusButton;
	private: System::Windows::Forms::Button^ addRecordButton;
	private: System::Windows::Forms::Button^ addPrescriptionButton;
	private: System::Windows::Forms::Button^ logoutButton;

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
			this->doctorIDLabel = (gcnew Label());
			this->titleLabel = (gcnew Label());
			this->contentTitleLabel = (gcnew Label());

			// ── Allocate sidebar buttons ──────────────────────────────
			this->viewAppointmentsButton = MakeSidebarButton(L"View Appointments", L"◉", 108);
			this->bookAppointmentButton = MakeSidebarButton(L"Book Appointment", L"✚", 152);
			this->updateStatusButton = MakeSidebarButton(L"Update Availability", L"↻", 196);
			this->addRecordButton = MakeSidebarButton(L"Log Medical Record", L"▣", 290);
			this->addPrescriptionButton = MakeSidebarButton(L"Write Prescription", L"✎", 334);
			this->logoutButton = (gcnew Button());

			// ── Allocate grid ─────────────────────────────────────────
			this->appointmentsGridView = (gcnew DataGridView());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGridView))->BeginInit();
			this->SuspendLayout();

			// ══════════════════════════════════════════════════════════
			// SIDEBAR
			// ══════════════════════════════════════════════════════════
			this->sidebarPanel->BackColor = System::Drawing::Color::White;
			this->sidebarPanel->Location = System::Drawing::Point(0, 0);
			this->sidebarPanel->Size = System::Drawing::Size(220, 680);
			this->sidebarPanel->Name = L"sidebarPanel";

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
			this->logoSubLabel->Text = L"Doctor Dashboard";
			this->logoSubLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->logoSubLabel->ForeColor = System::Drawing::Color::FromArgb(180, 212, 240);
			this->logoSubLabel->Location = System::Drawing::Point(16, 38);
			this->logoSubLabel->Size = System::Drawing::Size(190, 18);

			this->logoPanel->Controls->Add(this->logoLabel);
			this->logoPanel->Controls->Add(this->logoSubLabel);

			// ── Section 1: APPOINTMENTS ───────────────────────────────
			this->sectionLabel1->AutoSize = false;
			this->sectionLabel1->Text = L"APPOINTMENTS";
			this->sectionLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel1->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel1->Location = System::Drawing::Point(16, 88);
			this->sectionLabel1->Size = System::Drawing::Size(180, 16);

			// viewAppointmentsButton, bookAppointmentButton, updateStatusButton
			// already positioned in MakeSidebarButton calls above

			// ── Divider 1 ─────────────────────────────────────────────
			this->sidebarDivider1->AutoSize = false;
			this->sidebarDivider1->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider1->Location = System::Drawing::Point(12, 246);
			this->sidebarDivider1->Size = System::Drawing::Size(196, 1);

			// ── Section 2: PATIENT CARE ───────────────────────────────
			this->sectionLabel2->AutoSize = false;
			this->sectionLabel2->Text = L"PATIENT CARE";
			this->sectionLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->sectionLabel2->ForeColor = System::Drawing::Color::FromArgb(160, 158, 150);
			this->sectionLabel2->Location = System::Drawing::Point(16, 258);
			this->sectionLabel2->Size = System::Drawing::Size(180, 16);

			// addRecordButton y=290, addPrescriptionButton y=334 (set above)

			// ── Divider 2 ─────────────────────────────────────────────
			this->sidebarDivider2->AutoSize = false;
			this->sidebarDivider2->BackColor = System::Drawing::Color::FromArgb(230, 228, 220);
			this->sidebarDivider2->Location = System::Drawing::Point(12, 386);
			this->sidebarDivider2->Size = System::Drawing::Size(196, 1);

			// ── Logout (bottom) ───────────────────────────────────────
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
			this->logoutButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::logoutButton_Click);

			// ── Wire events ───────────────────────────────────────────
			this->viewAppointmentsButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::viewAppointmentsButton_Click);
			this->bookAppointmentButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::bookAppointmentButton_Click);
			this->updateStatusButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::updateStatusButton_Click);
			this->addRecordButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::addRecordButton_Click);
			this->addPrescriptionButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::addPrescriptionButton_Click);

			// ── Add to sidebarPanel ───────────────────────────────────
			this->sidebarPanel->Controls->Add(this->logoPanel);
			this->sidebarPanel->Controls->Add(this->sectionLabel1);
			this->sidebarPanel->Controls->Add(this->viewAppointmentsButton);
			this->sidebarPanel->Controls->Add(this->bookAppointmentButton);
			this->sidebarPanel->Controls->Add(this->updateStatusButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider1);
			this->sidebarPanel->Controls->Add(this->sectionLabel2);
			this->sidebarPanel->Controls->Add(this->addRecordButton);
			this->sidebarPanel->Controls->Add(this->addPrescriptionButton);
			this->sidebarPanel->Controls->Add(this->sidebarDivider2);
			this->sidebarPanel->Controls->Add(this->logoutButton);

			// ══════════════════════════════════════════════════════════
			// HEADER
			// ══════════════════════════════════════════════════════════
			this->headerPanel->BackColor = System::Drawing::Color::White;
			this->headerPanel->Location = System::Drawing::Point(220, 0);
			this->headerPanel->Size = System::Drawing::Size(860, 64);

			this->titleLabel->AutoSize = false;
			this->titleLabel->Text = L"Doctor Dashboard";
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15, System::Drawing::FontStyle::Bold));
			this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(4, 44, 83);
			this->titleLabel->Location = System::Drawing::Point(24, 10);
			this->titleLabel->Size = System::Drawing::Size(400, 28);
			this->titleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			this->welcomeLabel->AutoSize = false;
			this->welcomeLabel->Text = L"Welcome, Doctor!";
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->welcomeLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->welcomeLabel->Location = System::Drawing::Point(24, 38);
			this->welcomeLabel->Size = System::Drawing::Size(300, 18);

			// Doctor ID badge — top right of header
			this->doctorIDLabel->AutoSize = false;
			this->doctorIDLabel->Text = L"Doctor ID: N/A";
			this->doctorIDLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->doctorIDLabel->ForeColor = System::Drawing::Color::FromArgb(24, 95, 165);
			this->doctorIDLabel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->doctorIDLabel->Location = System::Drawing::Point(700, 22);
			this->doctorIDLabel->Size = System::Drawing::Size(140, 22);
			this->doctorIDLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->doctorIDLabel->Padding = System::Windows::Forms::Padding(6, 0, 6, 0);

			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Controls->Add(this->welcomeLabel);
			this->headerPanel->Controls->Add(this->doctorIDLabel);

			// ══════════════════════════════════════════════════════════
			// CONTENT PANEL
			// ══════════════════════════════════════════════════════════
			this->contentPanel->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->contentPanel->Location = System::Drawing::Point(220, 64);
			this->contentPanel->Size = System::Drawing::Size(860, 616);

			this->contentTitleLabel->AutoSize = false;
			this->contentTitleLabel->Text = L"Select an action from the sidebar to view data";
			this->contentTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->contentTitleLabel->ForeColor = System::Drawing::Color::FromArgb(136, 135, 128);
			this->contentTitleLabel->Location = System::Drawing::Point(20, 16);
			this->contentTitleLabel->Size = System::Drawing::Size(820, 22);
			this->contentTitleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			// ── DataGridView ──────────────────────────────────────────
			this->appointmentsGridView->BackgroundColor = System::Drawing::Color::White;
			this->appointmentsGridView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->appointmentsGridView->ColumnHeadersDefaultCellStyle->BackColor =
				System::Drawing::Color::FromArgb(24, 95, 165);
			this->appointmentsGridView->ColumnHeadersDefaultCellStyle->ForeColor =
				System::Drawing::Color::White;
			this->appointmentsGridView->ColumnHeadersDefaultCellStyle->Font =
				(gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->appointmentsGridView->ColumnHeadersDefaultCellStyle->Padding =
				System::Windows::Forms::Padding(8, 0, 0, 0);
			this->appointmentsGridView->ColumnHeadersHeight = 36;
			this->appointmentsGridView->EnableHeadersVisualStyles = false;
			this->appointmentsGridView->DefaultCellStyle->Font =
				(gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->appointmentsGridView->DefaultCellStyle->Padding =
				System::Windows::Forms::Padding(6, 0, 0, 0);
			this->appointmentsGridView->RowTemplate->Height = 30;
			this->appointmentsGridView->AlternatingRowsDefaultCellStyle->BackColor =
				System::Drawing::Color::FromArgb(245, 248, 252);
			this->appointmentsGridView->GridColor = System::Drawing::Color::FromArgb(220, 225, 232);
			this->appointmentsGridView->Location = System::Drawing::Point(20, 50);
			this->appointmentsGridView->ReadOnly = true;
			this->appointmentsGridView->Size = System::Drawing::Size(820, 540);
			this->appointmentsGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			this->appointmentsGridView->RowHeadersVisible = false;
			this->appointmentsGridView->AllowUserToAddRows = false;
			this->appointmentsGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			this->appointmentsGridView->Name = L"appointmentsGridView";

			this->contentPanel->Controls->Add(this->contentTitleLabel);
			this->contentPanel->Controls->Add(this->appointmentsGridView);

			// ══════════════════════════════════════════════════════════
			// FORM
			// ══════════════════════════════════════════════════════════
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(235, 243, 251);
			this->ClientSize = System::Drawing::Size(1080, 680);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"DoctorDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HPS - Doctor Dashboard";

			this->Controls->Add(this->sidebarPanel);
			this->Controls->Add(this->headerPanel);
			this->Controls->Add(this->contentPanel);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		// ── Helpers ───────────────────────────────────────────────────────
	private:
		void UpdateWelcomeLabel() {
			String^ username = gcnew String(currentUser->getUsername().c_str());
			int doctorID = currentUser->getUserID();

			welcomeLabel->Text = "Welcome, " + username + " (Doctor)";

			if (doctorID > 0)
				doctorIDLabel->Text = "Doctor ID: " + doctorID.ToString();
			else
				doctorIDLabel->Text = "Doctor ID: N/A";
		}

		// ══════════════════════════════════════════════════════════════════
		// EVENT HANDLERS — all logic identical to original, untouched
		// ══════════════════════════════════════════════════════════════════

	private: System::Void viewAppointmentsButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dbManager->Connect()) {
			appointmentsGridView->Rows->Clear();
			appointmentsGridView->Columns->Clear();
			contentTitleLabel->Text = L"Appointments";

			appointmentsGridView->Columns->Add("ApptID", "Appointment ID");
			appointmentsGridView->Columns->Add("PatientID", "Patient ID");
			appointmentsGridView->Columns->Add("Time", "Time Block");
			appointmentsGridView->Columns->Add("Type", "Type");

			sqlite3_stmt* stmt;
			string query = "SELECT AppointmentID, PatientID, StartTime, EndTime, IsSurgery FROM Appointments;";
			if (sqlite3_prepare_v2(dbManager->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					String^ id = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
					String^ pId = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
					String^ st = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
					String^ et = gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
					int isSurg = sqlite3_column_int(stmt, 4);

					String^ timeBlock = st + " to " + et;
					String^ typeStr = isSurg ? "Surgery" : "Consultation";

					appointmentsGridView->Rows->Add(id, pId, timeBlock, typeStr);
				}
			}
			sqlite3_finalize(stmt);
			dbManager->Disconnect();
		}
	}

	private: System::Void bookAppointmentButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ pIdStr = InputBox("Enter Patient ID:");
		if (String::IsNullOrEmpty(pIdStr)) return;

		String^ startStr = InputBox("Enter Start Time (YYYY-MM-DD HH:MM):");
		if (String::IsNullOrEmpty(startStr)) return;

		String^ endStr = InputBox("Enter End Time (YYYY-MM-DD HH:MM):");
		if (String::IsNullOrEmpty(endStr)) return;

		String^ surgStr = InputBox("Is this a surgery? (yes/no):");
		if (String::IsNullOrEmpty(surgStr)) return;

		int pId = Convert::ToInt32(pIdStr);
		int docId = currentUser->getUserID();
		std::string startTime = msclr::interop::marshal_as<std::string>(startStr);
		std::string endTime = msclr::interop::marshal_as<std::string>(endStr);
		bool isSurgery = (surgStr->ToLower() == "yes");

		if (dbManager->Connect()) {
			if (dbManager->CheckConflict(docId, startTime, endTime, isSurgery)) {
				MessageBox::Show("Conflict detected! You are already booked at this time.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {
				if (dbManager->BookAppointment(pId, docId, startTime, endTime, isSurgery)) {
					double billAmt = isSurgery ? 5000.00 : 250.00;
					dbManager->GenerateBill(pId, billAmt, false);
					MessageBox::Show("Appointment booked successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Failed to book appointment.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void updateStatusButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ availStr = InputBox("Are you available? (1 for Yes, 0 for No):");
		if (String::IsNullOrEmpty(availStr)) return;

		int docId = currentUser->getUserID();

		if (dbManager->Connect()) {
			std::string sqlQuery = "UPDATE Doctors SET IsAvailable=" +
				msclr::interop::marshal_as<std::string>(availStr) +
				" WHERE DoctorID=" + to_string(docId) + ";";
			char* err;
			if (sqlite3_exec(dbManager->getDB(), sqlQuery.c_str(), nullptr, 0, &err) == SQLITE_OK) {
				MessageBox::Show("Availability Status Updated!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to update status.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void addRecordButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ pIdStr = InputBox("Enter Patient ID:");
		if (String::IsNullOrEmpty(pIdStr)) return;

		String^ diagnosis = InputBox("Enter Diagnosis:");
		if (String::IsNullOrEmpty(diagnosis)) return;

		String^ symptoms = InputBox("Enter Symptoms:");
		String^ treatment = InputBox("Enter Treatment/Notes:");

		int pId = Convert::ToInt32(pIdStr);
		int docId = currentUser->getUserID();

		std::string dDiag = msclr::interop::marshal_as<std::string>(diagnosis);
		std::string dSymp = msclr::interop::marshal_as<std::string>(symptoms);
		std::string dTreat = msclr::interop::marshal_as<std::string>(treatment);

		if (dbManager->Connect()) {
			if (dbManager->AddMedicalRecord(pId, docId, dDiag, dSymp, dTreat)) {
				MessageBox::Show("Medical Record logged successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to log record.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void addPrescriptionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ pIdStr = InputBox("Enter Patient ID:");
		if (String::IsNullOrEmpty(pIdStr)) return;

		String^ meds = InputBox("Enter Medicine/Drug Details:");
		if (String::IsNullOrEmpty(meds)) return;

		String^ instructions = InputBox("Enter Dosage/Instructions:");

		int pId = Convert::ToInt32(pIdStr);
		int docId = currentUser->getUserID();

		std::string sMeds = msclr::interop::marshal_as<std::string>(meds);
		std::string sInst = msclr::interop::marshal_as<std::string>(instructions);

		if (dbManager->Connect()) {
			if (dbManager->AddPrescription(pId, docId, sMeds, sInst)) {
				MessageBox::Show("Prescription issued correctly!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to issue prescription.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			dbManager->Disconnect();
		}
	}

	private: System::Void logoutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to logout?", "Logout",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
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
	};
}