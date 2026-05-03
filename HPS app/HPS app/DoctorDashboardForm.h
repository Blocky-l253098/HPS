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

	private: System::ComponentModel::Container^ components;

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

			// addRecordButton
			Button^ addRecordButton = gcnew Button();
			addRecordButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			addRecordButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			addRecordButton->ForeColor = System::Drawing::Color::White;
			addRecordButton->Location = System::Drawing::Point(20, 470);
			addRecordButton->Name = L"addRecordButton";
			addRecordButton->Size = System::Drawing::Size(180, 40);
			addRecordButton->TabIndex = 7;
			addRecordButton->Text = L"Log Medical Record";
			addRecordButton->UseVisualStyleBackColor = false;
			addRecordButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::addRecordButton_Click);

			// addPrescriptionButton
			Button^ addPrescriptionButton = gcnew Button();
			addPrescriptionButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			addPrescriptionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			addPrescriptionButton->ForeColor = System::Drawing::Color::White;
			addPrescriptionButton->Location = System::Drawing::Point(220, 470);
			addPrescriptionButton->Name = L"addPrescriptionButton";
			addPrescriptionButton->Size = System::Drawing::Size(180, 40);
			addPrescriptionButton->TabIndex = 8;
			addPrescriptionButton->Text = L"Write Prescription";
			addPrescriptionButton->UseVisualStyleBackColor = false;
			addPrescriptionButton->Click += gcnew System::EventHandler(this, &DoctorDashboardForm::addPrescriptionButton_Click);

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
			this->ClientSize = System::Drawing::Size(650, 530);
			this->Controls->Add(addRecordButton);
			this->Controls->Add(addPrescriptionButton);
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
		if (dbManager->Connect()) {
			appointmentsGridView->Rows->Clear();
			appointmentsGridView->Columns->Clear();

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

		String^ docIdStr = InputBox("Enter Your Doctor ID:");

		int pId = Convert::ToInt32(pIdStr);
		int docId = Convert::ToInt32(docIdStr);
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
		String^ docIdStr = InputBox("Enter Your Doctor ID:");
		if (String::IsNullOrEmpty(docIdStr)) return;

		String^ availStr = InputBox("Are you available? (1 for Yes, 0 for No):");
		if (String::IsNullOrEmpty(availStr)) return;

		if (dbManager->Connect()) {
			std::string sqlQuery = "UPDATE Doctors SET IsAvailable=" + msclr::interop::marshal_as<std::string>(availStr) + " WHERE DoctorID=" + msclr::interop::marshal_as<std::string>(docIdStr) + ";";
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

		String^ docIdStr = InputBox("Enter Doctor ID (Your ID):");
		if (String::IsNullOrEmpty(docIdStr)) return;

		String^ diagnosis = InputBox("Enter Diagnosis:");
		if (String::IsNullOrEmpty(diagnosis)) return;

		String^ symptoms = InputBox("Enter Symptoms:");
		String^ treatment = InputBox("Enter Treatment/Notes:");

		int pId = Convert::ToInt32(pIdStr);
		int docId = Convert::ToInt32(docIdStr);

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

		String^ docIdStr = InputBox("Enter Doctor ID (Your ID):");
		if (String::IsNullOrEmpty(docIdStr)) return;

		String^ meds = InputBox("Enter Medicine/Drug Details:");
		if (String::IsNullOrEmpty(meds)) return;

		String^ instructions = InputBox("Enter Dosage/Instructions:");

		int pId = Convert::ToInt32(pIdStr);
		int docId = Convert::ToInt32(docIdStr);

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
