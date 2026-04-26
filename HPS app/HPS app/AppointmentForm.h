#pragma once
#include "DatabaseManager.h"
#include "Login.h"
#include "SessionManager.h"
#include <msclr/marshal_cppstd.h>

namespace HPSapp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class AppointmentForm : public Form
	{
	private:
		DatabaseManager* dbManager;

	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ patientIdLabel;
	private: System::Windows::Forms::Label^ patientIdValueLabel;
	private: System::Windows::Forms::Label^ doctorIdLabel;
	private: System::Windows::Forms::TextBox^ doctorIdTextBox;
	private: System::Windows::Forms::Label^ dateLabel;
	private: System::Windows::Forms::DateTimePicker^ datePicker;
	private: System::Windows::Forms::Label^ timeLabel;
	private: System::Windows::Forms::TextBox^ timeTextBox;
	private: System::Windows::Forms::Button^ bookButton;
	private: System::Windows::Forms::Button^ viewButton;
	private: System::Windows::Forms::Button^ closeButton;
	private: System::Windows::Forms::DataGridView^ appointmentsGrid;
	private: System::Windows::Forms::Label^ gridTitleLabel;

	public:
		AppointmentForm()
		{
			dbManager = new DatabaseManager();
			dbManager->Connect();
			InitializeComponent();
			patientIdValueLabel->Text = SessionManager::CurrentUserId.ToString();
		}

	protected:
		~AppointmentForm()
		{
			if (components) delete components;
			if (dbManager) { dbManager->Disconnect(); delete dbManager; }
		}

	private: System::ComponentModel::Container^ components;

	private:
		void InitializeComponent(void)
		{
			this->titleLabel = gcnew Label();
			this->patientIdLabel = gcnew Label();
			this->patientIdValueLabel = gcnew Label();
			this->doctorIdLabel = gcnew Label();
			this->doctorIdTextBox = gcnew TextBox();
			this->dateLabel = gcnew Label();
			this->datePicker = gcnew DateTimePicker();
			this->timeLabel = gcnew Label();
			this->timeTextBox = gcnew TextBox();
			this->bookButton = gcnew Button();
			this->viewButton = gcnew Button();
			this->closeButton = gcnew Button();
			this->appointmentsGrid = gcnew DataGridView();
			this->gridTitleLabel = gcnew Label();

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGrid))->BeginInit();
			this->SuspendLayout();

			// titleLabel
			this->titleLabel->Text = L"Book an Appointment";
			this->titleLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			this->titleLabel->ForeColor = Color::FromArgb(0, 102, 204);
			this->titleLabel->Location = Point(20, 15);
			this->titleLabel->Size = System::Drawing::Size(400, 30);

			// patientIdLabel
			this->patientIdLabel->Text = L"Your Patient ID:";
			this->patientIdLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->patientIdLabel->Location = Point(20, 65);
			this->patientIdLabel->Size = System::Drawing::Size(130, 22);

			// patientIdValueLabel
			this->patientIdValueLabel->Text = L"";
			this->patientIdValueLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->patientIdValueLabel->ForeColor = Color::FromArgb(0, 102, 204);
			this->patientIdValueLabel->Location = Point(160, 65);
			this->patientIdValueLabel->Size = System::Drawing::Size(150, 22);

			// doctorIdLabel
			this->doctorIdLabel->Text = L"Doctor ID:";
			this->doctorIdLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->doctorIdLabel->Location = Point(20, 100);
			this->doctorIdLabel->Size = System::Drawing::Size(130, 22);

			// doctorIdTextBox
			this->doctorIdTextBox->Location = Point(160, 97);
			this->doctorIdTextBox->Size = System::Drawing::Size(150, 22);
			this->doctorIdTextBox->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);

			// dateLabel
			this->dateLabel->Text = L"Date:";
			this->dateLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->dateLabel->Location = Point(20, 135);
			this->dateLabel->Size = System::Drawing::Size(130, 22);

			// datePicker
			this->datePicker->Location = Point(160, 132);
			this->datePicker->Size = System::Drawing::Size(150, 22);
			this->datePicker->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->datePicker->Format = DateTimePickerFormat::Short;

			// timeLabel
			this->timeLabel->Text = L"Time (HH:MM):";
			this->timeLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->timeLabel->Location = Point(20, 170);
			this->timeLabel->Size = System::Drawing::Size(130, 22);

			// timeTextBox
			this->timeTextBox->Location = Point(160, 167);
			this->timeTextBox->Size = System::Drawing::Size(150, 22);
			this->timeTextBox->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);

			// bookButton
			this->bookButton->Text = L"Book Appointment";
			this->bookButton->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->bookButton->BackColor = Color::FromArgb(0, 102, 204);
			this->bookButton->ForeColor = Color::White;
			this->bookButton->Location = Point(20, 210);
			this->bookButton->Size = System::Drawing::Size(160, 38);
			this->bookButton->FlatStyle = FlatStyle::Flat;
			this->bookButton->Click += gcnew EventHandler(this, &AppointmentForm::bookButton_Click);

			// viewButton
			this->viewButton->Text = L"View My Appointments";
			this->viewButton->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->viewButton->BackColor = Color::FromArgb(0, 153, 76);
			this->viewButton->ForeColor = Color::White;
			this->viewButton->Location = Point(190, 210);
			this->viewButton->Size = System::Drawing::Size(180, 38);
			this->viewButton->FlatStyle = FlatStyle::Flat;
			this->viewButton->Click += gcnew EventHandler(this, &AppointmentForm::viewButton_Click);

			// closeButton
			this->closeButton->Text = L"Close";
			this->closeButton->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->closeButton->BackColor = Color::Red;
			this->closeButton->ForeColor = Color::White;
			this->closeButton->Location = Point(380, 210);
			this->closeButton->Size = System::Drawing::Size(100, 38);
			this->closeButton->FlatStyle = FlatStyle::Flat;
			this->closeButton->Click += gcnew EventHandler(this, &AppointmentForm::closeButton_Click);

			// gridTitleLabel
			this->gridTitleLabel->Text = L"My Appointments:";
			this->gridTitleLabel->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 11, FontStyle::Bold);
			this->gridTitleLabel->ForeColor = Color::FromArgb(0, 102, 204);
			this->gridTitleLabel->Location = Point(20, 263);
			this->gridTitleLabel->Size = System::Drawing::Size(200, 22);

			// appointmentsGrid
			this->appointmentsGrid->Location = Point(20, 290);
			this->appointmentsGrid->Size = System::Drawing::Size(560, 180);
			this->appointmentsGrid->BackgroundColor = Color::White;
			this->appointmentsGrid->ReadOnly = true;
			this->appointmentsGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			this->appointmentsGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(0, 102, 204);
			this->appointmentsGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			this->appointmentsGrid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 9, FontStyle::Bold);
			this->appointmentsGrid->EnableHeadersVisualStyles = false;

			// Form
			this->Text = L"HPS - Book Appointment";
			this->ClientSize = System::Drawing::Size(610, 490);
			this->BackColor = Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->StartPosition = FormStartPosition::CenterScreen;

			this->Controls->Add(this->titleLabel);
			this->Controls->Add(this->patientIdLabel);
			this->Controls->Add(this->patientIdValueLabel);
			this->Controls->Add(this->doctorIdLabel);
			this->Controls->Add(this->doctorIdTextBox);
			this->Controls->Add(this->dateLabel);
			this->Controls->Add(this->datePicker);
			this->Controls->Add(this->timeLabel);
			this->Controls->Add(this->timeTextBox);
			this->Controls->Add(this->bookButton);
			this->Controls->Add(this->viewButton);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->gridTitleLabel);
			this->Controls->Add(this->appointmentsGrid);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->appointmentsGrid))->EndInit();
			this->ResumeLayout(false);
		}

	private: System::Void bookButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (doctorIdTextBox->Text->Trim() == "" || timeTextBox->Text->Trim() == "") {
			MessageBox::Show("Please fill all fields!", "Validation Error",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int doctorId = 0;
		try { doctorId = Int32::Parse(doctorIdTextBox->Text->Trim()); }
		catch (...) {
			MessageBox::Show("Doctor ID must be a number!", "Validation Error",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int patientId = SessionManager::CurrentUserId;

		// Build time: "YYYY-MM-DD HH:MM"
		String^ dateStr = datePicker->Value.ToString("yyyy-MM-dd");
		String^ startFull = dateStr + " " + timeTextBox->Text->Trim();

		// Appointment EndTime = StartTime + 1 hour (default)
		String^ endFull = dateStr + " " + timeTextBox->Text->Trim();

		std::string startStd = msclr::interop::marshal_as<std::string>(startFull);
		std::string endStd = msclr::interop::marshal_as<std::string>(endFull);

		// Check conflict
		if (dbManager->CheckConflict(doctorId, startStd, endStd, false)) {
			MessageBox::Show("This doctor is not available at this time!\nPlease choose a different time.",
				"Conflict Detected", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Book appointment
		if (dbManager->BookAppointment(patientId, doctorId, startStd, endStd, false)) {
			MessageBox::Show("Appointment booked successfully!", "Success",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
			doctorIdTextBox->Text = "";
			timeTextBox->Text = "";
		}
		else {
			MessageBox::Show("Failed to book appointment. Please try again.", "Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void viewButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		appointmentsGrid->Rows->Clear();
		appointmentsGrid->Columns->Clear();

		appointmentsGrid->Columns->Add("AppID", "Appt ID");
		appointmentsGrid->Columns->Add("DoctorID", "Doctor ID");
		appointmentsGrid->Columns->Add("Time", "Time");

		sqlite3* db;
		sqlite3_open("hospital.db", &db);

		int patientId = SessionManager::CurrentUserId;
		std::string sql = "SELECT AppointmentID, DoctorID, StartTime FROM Appointments "
			"WHERE PatientID = " + std::to_string(patientId) +
			" AND IsSurgury = 0 ORDER BY StartTime ASC;";

		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int appId = sqlite3_column_int(stmt, 0);
				int docId = sqlite3_column_int(stmt, 1);
				std::string time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

				appointmentsGrid->Rows->Add(
					appId.ToString(),
					docId.ToString(),
					gcnew String(time.c_str())
				);
			}
			sqlite3_finalize(stmt);
		}
		sqlite3_close(db);

		if (appointmentsGrid->Rows->Count == 0)
			MessageBox::Show("No appointments found.", "Info",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	};
}