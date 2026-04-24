#ifndef HOSPITAL_MANAGMENT_BILLINGMODULE_H
#define HOSPITAL_MANAGMENT_BILLINGMODULE_H

#include "sqlite3.h"
#include <msclr/marshal_cppstd.h>
#include <string>

namespace HospitalManagment {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class BillingModule : public System::Windows::Forms::Form
	{
	private:
		Label^ lblID;
		Label^ lblDays;
		TextBox^ txtIDInput;
		TextBox^ txtDaysInput;
		Button^ btnGenerate;
		RichTextBox^ rtbDisplay;

		// --- UPDATED FINANCE RATES ---
		const double ROOM_RATE_PER_DAY = 1500.0;
		const double DOCTOR_VISIT_FEE = 1000.0;
		const double SURGERY_BASE_FEE = 25000.0; // Added Surgery Fee

	public:
		BillingModule(void) {
			InitializeComponent();
			BuildUI();
		}

	private:
		void BuildUI() {
			this->Text = "Comprehensive Billing & Finance";
			this->Size = System::Drawing::Size(450, 580);
			this->BackColor = Color::White;

			lblID = gcnew Label();
			lblID->Text = "Patient ID:";
			lblID->Location = Point(20, 25);
			lblID->AutoSize = true;

			txtIDInput = gcnew TextBox();
			txtIDInput->Location = Point(20, 45);
			txtIDInput->Size = System::Drawing::Size(180, 25);

			lblDays = gcnew Label();
			lblDays->Text = "Days in Room:";
			lblDays->Location = Point(220, 25);
			lblDays->AutoSize = true;

			txtDaysInput = gcnew TextBox();
			txtDaysInput->Location = Point(220, 45);
			txtDaysInput->Size = System::Drawing::Size(180, 25);
			txtDaysInput->Text = "0";

			btnGenerate = gcnew Button();
			btnGenerate->Text = "Generate Final Invoice (Includes Surgery)";
			btnGenerate->Location = Point(20, 85);
			btnGenerate->Size = System::Drawing::Size(380, 35);
			btnGenerate->BackColor = Color::LightSteelBlue;
			btnGenerate->FlatStyle = FlatStyle::Flat;
			btnGenerate->Click += gcnew EventHandler(this, &BillingModule::OnCalculateTotalBill);

			rtbDisplay = gcnew RichTextBox();
			rtbDisplay->Location = Point(20, 135);
			rtbDisplay->Size = System::Drawing::Size(380, 380);
			rtbDisplay->ReadOnly = true;
			rtbDisplay->Font = gcnew System::Drawing::Font("Consolas", 9);
			rtbDisplay->BackColor = Color::GhostWhite;

			this->Controls->Add(lblID);
			this->Controls->Add(txtIDInput);
			this->Controls->Add(lblDays);
			this->Controls->Add(txtDaysInput);
			this->Controls->Add(btnGenerate);
			this->Controls->Add(rtbDisplay);
		}

		void OnCalculateTotalBill(Object^ sender, EventArgs^ e) {
			if (String::IsNullOrWhiteSpace(txtIDInput->Text)) return;

			int daysStayed = 0;
			Int32::TryParse(txtDaysInput->Text, daysStayed);

			sqlite3* DB;
			sqlite3_stmt* stmt;
			String^ pName = "Unknown";
			int apptCount = 0;
			int surgeryCount = 0;
			double medTotal = 0;

			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				msclr::interop::marshal_context context;
				std::string pID = context.marshal_as<std::string>(txtIDInput->Text);

				// 1. Fetch Patient Name
				std::string sql1 = "SELECT Name FROM Patients WHERE PatientID = " + pID + ";";
				if (sqlite3_prepare_v2(DB, sql1.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
					if (sqlite3_step(stmt) == SQLITE_ROW) pName = gcnew String((const char*)sqlite3_column_text(stmt, 0));
					sqlite3_finalize(stmt);
				}

				// 2. Fetch Medication Sum (Assume Prescriptions table from earlier logic)
				std::string sql2 = "SELECT SUM(Price) FROM Prescriptions WHERE PatientID = " + pID + ";";
				if (sqlite3_prepare_v2(DB, sql2.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
					if (sqlite3_step(stmt) == SQLITE_ROW) medTotal = sqlite3_column_double(stmt, 0);
					sqlite3_finalize(stmt);
				}

				// 3. Fetch Appointment Count
				std::string sql3 = "SELECT COUNT(*) FROM Appointments WHERE PatientID = " + pID + ";";
				if (sqlite3_prepare_v2(DB, sql3.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
					if (sqlite3_step(stmt) == SQLITE_ROW) apptCount = sqlite3_column_int(stmt, 0);
					sqlite3_finalize(stmt);
				}

				// 4. NEW: Fetch Surgery Count (Using partner's 'IsSurgury' column)
				std::string sql4 = "SELECT COUNT(*) FROM Appointments WHERE PatientID = " + pID + " AND IsSurgury = 1;";
				if (sqlite3_prepare_v2(DB, sql4.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
					if (sqlite3_step(stmt) == SQLITE_ROW) surgeryCount = sqlite3_column_int(stmt, 0);
					sqlite3_finalize(stmt);
				}

				// --- CALCULATIONS ---
				double roomBill = daysStayed * ROOM_RATE_PER_DAY;
				double docBill = apptCount * DOCTOR_VISIT_FEE;
				double surgeryBill = surgeryCount * SURGERY_BASE_FEE;
				double grandTotal = roomBill + docBill + medTotal + surgeryBill;

				// Save to Billing table
				std::string sqlSave = "INSERT INTO Billing (PatientID, Amount, Paid) VALUES (" + pID + ", " + std::to_string(grandTotal) + ", 0);";
				sqlite3_exec(DB, sqlSave.c_str(), nullptr, 0, nullptr);

				// --- OUTPUT ---
				rtbDisplay->Clear();
				rtbDisplay->AppendText("==========================================\n");
				rtbDisplay->AppendText("        HOSPITAL COMPREHENSIVE BILL       \n");
				rtbDisplay->AppendText("==========================================\n");
				rtbDisplay->AppendText("Patient: " + pName + " (ID: " + txtIDInput->Text + ")\n\n");

				rtbDisplay->AppendText("1. ROOM CHARGES (" + daysStayed + " Days)\n");
				rtbDisplay->AppendText("   Total: $" + roomBill.ToString("F2") + "\n\n");

				rtbDisplay->AppendText("2. DOCTOR CONSULTATIONS (" + apptCount + " Visits)\n");
				rtbDisplay->AppendText("   Total: $" + docBill.ToString("F2") + "\n\n");

				rtbDisplay->AppendText("3. SURGERY FEES (" + surgeryCount + " Performed)\n");
				rtbDisplay->AppendText("   Total: $" + surgeryBill.ToString("F2") + "\n\n");

				rtbDisplay->AppendText("4. PHARMACY & MEDICINES\n");
				rtbDisplay->AppendText("   Total: $" + medTotal.ToString("F2") + "\n\n");

				rtbDisplay->AppendText("------------------------------------------\n");
				rtbDisplay->SelectionFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
				rtbDisplay->AppendText("GRAND TOTAL: $" + grandTotal.ToString("F2") + "\n");
				rtbDisplay->AppendText("------------------------------------------\n");
				rtbDisplay->AppendText("Status: UNPAID | Processed by Finance Dept\n");

				sqlite3_close(DB);
			}
		}

	protected:
		~BillingModule() {}
		void InitializeComponent(void) {}
	};
}

#endif