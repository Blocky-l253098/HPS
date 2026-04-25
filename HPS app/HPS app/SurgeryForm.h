#pragma once
#include "DatabaseManager.h"
#include "Login.h"
#include "SessionManager.h"
#include <msclr/marshal_cppstd.h>

namespace HPSapp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class SurgeryForm : public Form
	{
	private:
		DatabaseManager* dbManager;

	private: System::Windows::Forms::Label^          titleLabel;
	private: System::Windows::Forms::Label^          subtitleLabel;
	private: System::Windows::Forms::Label^          patientIdLabel;
	private: System::Windows::Forms::Label^          patientIdValueLabel;
	private: System::Windows::Forms::Label^          doctorIdLabel;
	private: System::Windows::Forms::TextBox^        doctorIdTextBox;
	private: System::Windows::Forms::Label^          dateLabel;
	private: System::Windows::Forms::DateTimePicker^ datePicker;
	private: System::Windows::Forms::Label^          startTimeLabel;
	private: System::Windows::Forms::TextBox^        startTimeTextBox;
	private: System::Windows::Forms::Label^          endTimeLabel;
	private: System::Windows::Forms::TextBox^        endTimeTextBox;
	private: System::Windows::Forms::Button^         scheduleButton;
	private: System::Windows::Forms::Button^         viewButton;
	private: System::Windows::Forms::Button^         closeButton;
	private: System::Windows::Forms::DataGridView^   surgeriesGrid;
	private: System::Windows::Forms::Label^          gridTitleLabel;

	public:
		SurgeryForm()
		{
			dbManager = new DatabaseManager();
			dbManager->Connect();
			InitializeComponent();
			// Auto fill patient ID from session
			patientIdValueLabel->Text = SessionManager::CurrentUserId.ToString();
		}

	protected:
		~SurgeryForm()
		{
			if (components) delete components;
			if (dbManager) { dbManager->Disconnect(); delete dbManager; }
		}

	private: System::ComponentModel::Container^ components;

	private:
		void InitializeComponent(void)
		{
			this->titleLabel          = gcnew Label();
			this->subtitleLabel       = gcnew Label();
			this->patientIdLabel      = gcnew Label();
			this->patientIdValueLabel = gcnew Label();
			this->doctorIdLabel       = gcnew Label();
			this->doctorIdTextBox     = gcnew TextBox();
			this->dateLabel           = gcnew Label();
			this->datePicker          = gcnew DateTimePicker();
			this->startTimeLabel      = gcnew Label();
			this->startTimeTextBox    = gcnew TextBox();
			this->endTimeLabel        = gcnew Label();
			this->endTimeTextBox      = gcnew TextBox();
			this->scheduleButton      = gcnew Button();
			this->viewButton          = gcnew Button();
			this->closeButton         = gcnew Button();
			this->surgeriesGrid       = gcnew DataGridView();
			this->gridTitleLabel      = gcnew Label();

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->surgeriesGrid))->BeginInit();
			this->SuspendLayout();

			// titleLabel
			this->titleLabel->Text      = L"Surgery Scheduling";
			this->titleLabel->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 16, FontStyle::Bold);
			this->titleLabel->ForeColor = Color::FromArgb(153, 0, 0);
			this->titleLabel->Location  = Point(20, 15);
			this->titleLabel->Size      = System::Drawing::Size(400, 30);

			// subtitleLabel
			this->subtitleLabel->Text      = L"Conflict check is automatic - overlapping surgeries will be blocked.";
			this->subtitleLabel->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 9, FontStyle::Italic);
			this->subtitleLabel->ForeColor = Color::Gray;
			this->subtitleLabel->Location  = Point(20, 48);
			this->subtitleLabel->Size      = System::Drawing::Size(560, 18);

			// patientIdLabel
			this->patientIdLabel->Text     = L"Your Patient ID:";
			this->patientIdLabel->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->patientIdLabel->Location = Point(20, 80);
			this->patientIdLabel->Size     = System::Drawing::Size(130, 22);

			// patientIdValueLabel
			this->patientIdValueLabel->Text      = L"";
			this->patientIdValueLabel->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->patientIdValueLabel->ForeColor = Color::FromArgb(153, 0, 0);
			this->patientIdValueLabel->Location  = Point(160, 80);
			this->patientIdValueLabel->Size      = System::Drawing::Size(150, 22);

			// doctorIdLabel
			this->doctorIdLabel->Text     = L"Doctor ID:";
			this->doctorIdLabel->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->doctorIdLabel->Location = Point(20, 115);
			this->doctorIdLabel->Size     = System::Drawing::Size(130, 22);

			// doctorIdTextBox
			this->doctorIdTextBox->Location = Point(160, 112);
			this->doctorIdTextBox->Size     = System::Drawing::Size(150, 22);
			this->doctorIdTextBox->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);

			// dateLabel
			this->dateLabel->Text     = L"Surgery Date:";
			this->dateLabel->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->dateLabel->Location = Point(20, 150);
			this->dateLabel->Size     = System::Drawing::Size(130, 22);

			// datePicker
			this->datePicker->Location = Point(160, 147);
			this->datePicker->Size     = System::Drawing::Size(150, 22);
			this->datePicker->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->datePicker->Format   = DateTimePickerFormat::Short;

			// startTimeLabel
			this->startTimeLabel->Text     = L"Start Time (HH:MM):";
			this->startTimeLabel->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->startTimeLabel->Location = Point(20, 185);
			this->startTimeLabel->Size     = System::Drawing::Size(135, 22);

			// startTimeTextBox
			this->startTimeTextBox->Location = Point(160, 182);
			this->startTimeTextBox->Size     = System::Drawing::Size(150, 22);
			this->startTimeTextBox->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);

			// endTimeLabel
			this->endTimeLabel->Text     = L"End Time (HH:MM):";
			this->endTimeLabel->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);
			this->endTimeLabel->Location = Point(20, 220);
			this->endTimeLabel->Size     = System::Drawing::Size(135, 22);

			// endTimeTextBox
			this->endTimeTextBox->Location = Point(160, 217);
			this->endTimeTextBox->Size     = System::Drawing::Size(150, 22);
			this->endTimeTextBox->Font     = gcnew Drawing::Font(L"Microsoft Sans Serif", 10);

			// scheduleButton
			this->scheduleButton->Text      = L"Schedule Surgery";
			this->scheduleButton->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->scheduleButton->BackColor = Color::FromArgb(153, 0, 0);
			this->scheduleButton->ForeColor = Color::White;
			this->scheduleButton->Location  = Point(20, 260);
			this->scheduleButton->Size      = System::Drawing::Size(160, 38);
			this->scheduleButton->FlatStyle = FlatStyle::Flat;
			this->scheduleButton->Click    += gcnew EventHandler(this, &SurgeryForm::scheduleButton_Click);

			// viewButton
			this->viewButton->Text      = L"View My Surgeries";
			this->viewButton->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->viewButton->BackColor = Color::FromArgb(0, 102, 204);
			this->viewButton->ForeColor = Color::White;
			this->viewButton->Location  = Point(190, 260);
			this->viewButton->Size      = System::Drawing::Size(160, 38);
			this->viewButton->FlatStyle = FlatStyle::Flat;
			this->viewButton->Click    += gcnew EventHandler(this, &SurgeryForm::viewButton_Click);

			// closeButton
			this->closeButton->Text      = L"Close";
			this->closeButton->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold);
			this->closeButton->BackColor = Color::Gray;
			this->closeButton->ForeColor = Color::White;
			this->closeButton->Location  = Point(360, 260);
			this->closeButton->Size      = System::Drawing::Size(100, 38);
			this->closeButton->FlatStyle = FlatStyle::Flat;
			this->closeButton->Click    += gcnew EventHandler(this, &SurgeryForm::closeButton_Click);

			// gridTitleLabel
			this->gridTitleLabel->Text      = L"My Scheduled Surgeries:";
			this->gridTitleLabel->Font      = gcnew Drawing::Font(L"Microsoft Sans Serif", 11, FontStyle::Bold);
			this->gridTitleLabel->ForeColor = Color::FromArgb(153, 0, 0);
			this->gridTitleLabel->Location  = Point(20, 313);
			this->gridTitleLabel->Size      = System::Drawing::Size(250, 22);

			// surgeriesGrid
			this->surgeriesGrid->Location                                  = Point(20, 340);
			this->surgeriesGrid->Size                                      = System::Drawing::Size(560, 180);
			this->surgeriesGrid->BackgroundColor                           = Color::White;
			this->surgeriesGrid->ReadOnly                                  = true;
			this->surgeriesGrid->AutoSizeColumnsMode                       = DataGridViewAutoSizeColumnsMode::Fill;
			this->surgeriesGrid->ColumnHeadersDefaultCellStyle->BackColor  = Color::FromArgb(153, 0, 0);
			this->surgeriesGrid->ColumnHeadersDefaultCellStyle->ForeColor  = Color::White;
			this->surgeriesGrid->ColumnHeadersDefaultCellStyle->Font       = gcnew Drawing::Font(L"Microsoft Sans Serif", 9, FontStyle::Bold);
			this->surgeriesGrid->EnableHeadersVisualStyles                 = false;

			// Form
			this->Text            = L"HPS - Surgery Scheduling";
			this->ClientSize      = System::Drawing::Size(610, 540);
			this->BackColor       = Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox     = false;
			this->StartPosition   = FormStartPosition::CenterScreen;

			this->Controls->Add(this->titleLabel);
			this->Controls->Add(this->subtitleLabel);
			this->Controls->Add(this->patientIdLabel);
			this->Controls->Add(this->patientIdValueLabel);
			this->Controls->Add(this->doctorIdLabel);
			this->Controls->Add(this->doctorIdTextBox);
			this->Controls->Add(this->dateLabel);
			this->Controls->Add(this->datePicker);
			this->Controls->Add(this->startTimeLabel);
			this->Controls->Add(this->startTimeTextBox);
			this->Controls->Add(this->endTimeLabel);
			this->Controls->Add(this->endTimeTextBox);
			this->Controls->Add(this->scheduleButton);
			this->Controls->Add(this->viewButton);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->gridTitleLabel);
			this->Controls->Add(this->surgeriesGrid);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->surgeriesGrid))->EndInit();
			this->ResumeLayout(false);
		}

	private: System::Void scheduleButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Validate inputs
		if (doctorIdTextBox->Text->Trim() == "" ||
			startTimeTextBox->Text->Trim() == "" ||
			endTimeTextBox->Text->Trim() == "")
		{
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

		// Get patient ID from session
		int patientId = SessionManager::CurrentUserId;

		// Build StartTime and EndTime: "YYYY-MM-DD HH:MM"
		String^ dateStr   = datePicker->Value.ToString("yyyy-MM-dd");
		String^ startFull = dateStr + " " + startTimeTextBox->Text->Trim();
		String^ endFull   = dateStr + " " + endTimeTextBox->Text->Trim();

		std::string startStd = msclr::interop::marshal_as<std::string>(startFull);
		std::string endStd   = msclr::interop::marshal_as<std::string>(endFull);

		// Validate start < end
		if (startStd >= endStd) {
			MessageBox::Show("End time must be after start time!", "Validation Error",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Check surgery conflict (isSurgery = true)
		if (dbManager->CheckConflict(doctorId, startStd, endStd, true)) {
			MessageBox::Show(
				"Conflict Detected!\nThis doctor already has a surgery or appointment overlapping this time.\nPlease choose a different slot.",
				"Surgery Conflict", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Book surgery (isSurgery = true)
		if (dbManager->BookAppointment(patientId, doctorId, startStd, endStd, true)) {
			MessageBox::Show("Surgery scheduled successfully!", "Success",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
			doctorIdTextBox->Text  = "";
			startTimeTextBox->Text = "";
			endTimeTextBox->Text   = "";
		}
		else {
			MessageBox::Show("Failed to schedule surgery. Please try again.", "Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void viewButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		surgeriesGrid->Rows->Clear();
		surgeriesGrid->Columns->Clear();

		surgeriesGrid->Columns->Add("SurgID",    "Surgery ID");
		surgeriesGrid->Columns->Add("DoctorID",  "Doctor ID");
		surgeriesGrid->Columns->Add("StartTime", "Start Time");
		surgeriesGrid->Columns->Add("EndTime",   "End Time");

		sqlite3* db;
		sqlite3_open("hospital.db", &db);

		int patientId   = SessionManager::CurrentUserId;
		std::string sql = "SELECT AppointmentID, DoctorID, StartTime, EndTime "
						  "FROM Appointments WHERE PatientID = " +
						  std::to_string(patientId) + " AND IsSurgury = 1 ORDER BY StartTime ASC;";

		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				int appId         = sqlite3_column_int(stmt, 0);
				int docId         = sqlite3_column_int(stmt, 1);
				std::string start = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
				std::string end   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

				surgeriesGrid->Rows->Add(
					appId.ToString(),
					docId.ToString(),
					gcnew String(start.c_str()),
					gcnew String(end.c_str())
				);
			}
			sqlite3_finalize(stmt);
		}
		sqlite3_close(db);

		if (surgeriesGrid->Rows->Count == 0)
			MessageBox::Show("No surgeries scheduled yet.", "Info",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	};
}
