#ifndef HOSPITAL_MANAGMENT_BEDTRACKINGFORM_H
#define HOSPITAL_MANAGMENT_BEDTRACKINGFORM_H

#include "sqlite3.h"
#include <msclr/marshal_cppstd.h> 
#include <string>

namespace HospitalManagment {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class BedTrackingForm : public System::Windows::Forms::Form
	{
	private:
		Label^ lblTitle;
		Label^ lblLegend;
		FlowLayoutPanel^ pnlRoomGrid;

		// --- ADMIN CONTROLS ---
		GroupBox^ grpAdmin;
		Button^ btnAddNext;     // Automatic Addition
		Button^ btnAddSpecific; // Manual Addition (For re-adding after construction)
		Button^ btnRemoveRoom;  // Permanent Removal
		TextBox^ txtRoomID;
		Label^ lblAdminInstructions;

	public:
		BedTrackingForm(void)
		{
			InitializeComponent();
			BuildBedTrackingUI();
			InitializeBedDatabase();
			RefreshBedDisplay();
		}

	private:
		void BuildBedTrackingUI() {
			this->Text = "Hospital Resource - Bed Management";
			this->Size = System::Drawing::Size(850, 650);
			this->BackColor = Color::WhiteSmoke;

			lblTitle = gcnew Label();
			lblTitle->Text = "WARD ROOM MANAGEMENT";
			lblTitle->Location = Point(20, 20);
			lblTitle->AutoSize = true;
			lblTitle->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);

			lblLegend = gcnew Label();
			lblLegend->Text = "Green = Vacant | Salmon = Occupied | Under Construction = Remove from System";
			lblLegend->Location = Point(20, 50);
			lblLegend->AutoSize = true;
			lblLegend->ForeColor = Color::Blue;

			// --- Setup Admin Panel ---
			grpAdmin = gcnew GroupBox();
			grpAdmin->Text = "Admin Ward Control";
			grpAdmin->Location = Point(520, 80);
			grpAdmin->Size = System::Drawing::Size(280, 280);

			btnAddNext = gcnew Button();
			btnAddNext->Text = "Auto-Add Next Available Number";
			btnAddNext->Location = Point(20, 30);
			btnAddNext->Size = System::Drawing::Size(240, 40);
			btnAddNext->BackColor = Color::LightBlue;
			btnAddNext->Click += gcnew EventHandler(this, &BedTrackingForm::OnAddNextClick);

			lblAdminInstructions = gcnew Label();
			lblAdminInstructions->Text = "Target Room ID:";
			lblAdminInstructions->Location = Point(20, 90);
			lblAdminInstructions->AutoSize = true;

			txtRoomID = gcnew TextBox();
			txtRoomID->Location = Point(20, 110);
			txtRoomID->Size = System::Drawing::Size(240, 25);

			btnAddSpecific = gcnew Button();
			btnAddSpecific->Text = "Add / Re-add Specific ID";
			btnAddSpecific->Location = Point(20, 150);
			btnAddSpecific->Size = System::Drawing::Size(240, 35);
			btnAddSpecific->BackColor = Color::LightGreen;
			btnAddSpecific->Click += gcnew EventHandler(this, &BedTrackingForm::OnAddSpecificClick);

			btnRemoveRoom = gcnew Button();
			btnRemoveRoom->Text = "Remove (Under Construction)";
			btnRemoveRoom->Location = Point(20, 200);
			btnRemoveRoom->Size = System::Drawing::Size(240, 35);
			btnRemoveRoom->BackColor = Color::MistyRose;
			btnRemoveRoom->Click += gcnew EventHandler(this, &BedTrackingForm::OnRemoveRoomClick);

			grpAdmin->Controls->Add(btnAddNext);
			grpAdmin->Controls->Add(lblAdminInstructions);
			grpAdmin->Controls->Add(txtRoomID);
			grpAdmin->Controls->Add(btnAddSpecific);
			grpAdmin->Controls->Add(btnRemoveRoom);

			// --- Room Grid ---
			pnlRoomGrid = gcnew FlowLayoutPanel();
			pnlRoomGrid->Location = Point(20, 80);
			pnlRoomGrid->Size = System::Drawing::Size(480, 500);
			pnlRoomGrid->AutoScroll = true;
			pnlRoomGrid->BorderStyle = BorderStyle::FixedSingle;

			this->Controls->Add(lblTitle);
			this->Controls->Add(lblLegend);
			this->Controls->Add(grpAdmin);
			this->Controls->Add(pnlRoomGrid);
		}

		void InitializeBedDatabase() {
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS Rooms (RoomID INTEGER PRIMARY KEY, Status TEXT);", nullptr, 0, nullptr);
				sqlite3_close(DB);
			}
		}

		void RefreshBedDisplay() {
			pnlRoomGrid->Controls->Clear();
			sqlite3* DB; sqlite3_stmt* stmt;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				if (sqlite3_prepare_v2(DB, "SELECT RoomID, Status FROM Rooms ORDER BY RoomID ASC;", -1, &stmt, nullptr) == SQLITE_OK) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						int id = sqlite3_column_int(stmt, 0);
						String^ status = gcnew String((const char*)sqlite3_column_text(stmt, 1));

						Button^ btn = gcnew Button();
						btn->Size = System::Drawing::Size(90, 70);
						btn->Text = "Bed " + id + "\n" + status;
						btn->Tag = id;
						btn->BackColor = (status == "Vacant") ? Color::LightGreen : Color::Salmon;
						btn->FlatStyle = FlatStyle::Flat;
						btn->Click += gcnew EventHandler(this, &BedTrackingForm::OnRoomClick);

						pnlRoomGrid->Controls->Add(btn);
					}
				}
				sqlite3_finalize(stmt); sqlite3_close(DB);
			}
		}

		// --- 1. AUTO ADD (Finds the highest and goes up) ---
		void OnAddNextClick(Object^ sender, EventArgs^ e) {
			sqlite3* DB; sqlite3_stmt* stmt;
			int nextID = 101;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				if (sqlite3_prepare_v2(DB, "SELECT MAX(RoomID) FROM Rooms;", -1, &stmt, nullptr) == SQLITE_OK) {
					if (sqlite3_step(stmt) == SQLITE_ROW) {
						int maxID = sqlite3_column_int(stmt, 0);
						if (maxID > 0) nextID = maxID + 1;
					}
					sqlite3_finalize(stmt);
				}
				std::string sql = "INSERT INTO Rooms (RoomID, Status) VALUES (" + std::to_string(nextID) + ", 'Vacant');";
				sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB);
				RefreshBedDisplay();
			}
		}

		// --- 2. SPECIFIC ADD (For re-adding a removed number like 105) ---
		void OnAddSpecificClick(Object^ sender, EventArgs^ e) {
			if (String::IsNullOrWhiteSpace(txtRoomID->Text)) return;

			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				msclr::interop::marshal_context context;
				std::string idStr = context.marshal_as<std::string>(txtRoomID->Text);

				std::string sql = "INSERT INTO Rooms (RoomID, Status) VALUES (" + idStr + ", 'Vacant');";

				// Handle potential error if user tries to add an ID that already exists
				if (sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr) != SQLITE_OK) {
					MessageBox::Show("Error: This Room ID already exists in the system.");
				}

				sqlite3_close(DB);
				txtRoomID->Clear();
				RefreshBedDisplay();
			}
		}

		// --- 3. REMOVE (Deletes completely from DB) ---
	// --- 3. REMOVE (Deletes completely from DB with Validation) ---
		void OnRemoveRoomClick(Object^ sender, EventArgs^ e) {
			// A. Validation: Check if empty
			if (String::IsNullOrWhiteSpace(txtRoomID->Text)) {
				MessageBox::Show("Please enter a Room ID to remove.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// B. Validation: Check if it's a valid number
			int targetID;
			if (!Int32::TryParse(txtRoomID->Text, targetID)) {
				MessageBox::Show("Invalid Input! Please enter numbers only (e.g., 105).", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				txtRoomID->Clear();
				return;
			}

			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				std::string idStr = std::to_string(targetID);
				std::string sql = "DELETE FROM Rooms WHERE RoomID = " + idStr + ";";

				// Execute the delete
				char* errMsg = nullptr;
				int rc = sqlite3_exec(DB, sql.c_str(), nullptr, 0, &errMsg);

				if (rc == SQLITE_OK) {
					// C. Check if any row was actually deleted
					if (sqlite3_changes(DB) > 0) {
						MessageBox::Show("Room " + targetID + " has been successfully removed from the system.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else {
						// The ID was a number, but it wasn't in our list
						MessageBox::Show("Room " + targetID + " was not found in the list. Please check the ID and try again.", "Not Found", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
				else {
					MessageBox::Show("Database Error: " + gcnew String(errMsg), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					sqlite3_free(errMsg);
				}

				sqlite3_close(DB);
				txtRoomID->Clear();
				RefreshBedDisplay(); // Update the grid to show the change
			}
		}

		void OnRoomClick(Object^ sender, EventArgs^ e) {
			Button^ clickedBtn = (Button^)sender;
			int roomId = (int)clickedBtn->Tag;
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				std::string sql = "UPDATE Rooms SET Status = CASE WHEN Status = 'Vacant' THEN 'Occupied' ELSE 'Vacant' END WHERE RoomID = " + std::to_string(roomId) + ";";
				sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB);
				RefreshBedDisplay();
			}
		}

	protected:
		~BedTrackingForm() {}
		void InitializeComponent(void) {}
	};
}

#endif