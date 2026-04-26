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
			this->Text = "Hospital Resource - Bed Tracking";
			this->Size = System::Drawing::Size(800, 600);
			this->BackColor = Color::WhiteSmoke;

			lblTitle = gcnew Label();
			lblTitle->Text = "WARD ROOM MANAGEMENT";
			lblTitle->Location = Point(20, 20);
			lblTitle->AutoSize = true;
			lblTitle->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);

			lblLegend = gcnew Label();
			lblLegend->Text = "Green = Vacant | Red = Occupied";
			lblLegend->Location = Point(20, 50);
			lblLegend->AutoSize = true;
			lblLegend->ForeColor = Color::Blue;

			pnlRoomGrid = gcnew FlowLayoutPanel();
			pnlRoomGrid->Location = Point(20, 80);
			pnlRoomGrid->Size = System::Drawing::Size(300, 250);
			pnlRoomGrid->AutoScroll = true;

			this->Controls->Add(lblTitle);
			this->Controls->Add(lblLegend);
			this->Controls->Add(pnlRoomGrid);
		}

		void InitializeBedDatabase() {
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS Rooms (RoomID INTEGER PRIMARY KEY, Status TEXT);", nullptr, 0, nullptr);
				for (int i = 101; i <= 130; i++) {
					std::string sql = "INSERT OR IGNORE INTO Rooms (RoomID, Status) VALUES (" + std::to_string(i) + ", 'Vacant');";
					sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr);
				}
				sqlite3_close(DB);
			}
		}

		void RefreshBedDisplay() {
			pnlRoomGrid->Controls->Clear();
			sqlite3* DB; sqlite3_stmt* stmt;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				if (sqlite3_prepare_v2(DB, "SELECT RoomID, Status FROM Rooms;", -1, &stmt, nullptr) == SQLITE_OK) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						int id = sqlite3_column_int(stmt, 0);
						String^ status = gcnew String((const char*)sqlite3_column_text(stmt, 1));
						Button^ btn = gcnew Button();
						btn->Size = System::Drawing::Size(80, 60);
						btn->Text = "Room " + id + "\n" + status;
						btn->Tag = id;
						btn->BackColor = (status == "Vacant") ? Color::LightGreen : Color::Salmon;
						btn->Click+= gcnew EventHandler(this, &BedTrackingForm::OnRoomClick);
						pnlRoomGrid->Controls->Add(btn);
					}
				}
				sqlite3_finalize(stmt); sqlite3_close(DB);
			}
		}

		void OnRoomClick(Object^ sender, EventArgs^ e) {
			Button^ clickedBtn = (Button^)sender;
			int roomId = (int)clickedBtn->Tag;
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				std::string sql = "UPDATE Rooms SET Status = CASE WHEN Status = 'Vacant' THEN 'Occupied' ELSE 'Vacant' END WHERE RoomID = " + std::to_string(roomId) + ";";
				sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB); RefreshBedDisplay();
			}
		}

	protected:
		~BedTrackingForm() {}
		void InitializeComponent(void) {}
	};
}

#endif 