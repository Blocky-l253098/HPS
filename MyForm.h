#ifndef HOSPITAL_MANAGMENT_MYFORM_H
#define HOSPITAL_MANAGMENT_MYFORM_H

#include "sqlite3.h"
#include <msclr/marshal_cppstd.h> 
#include <string>
namespace HospitalManagment {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		TextBox^ txtNoticeInput;
		Button^ btnPostNotice;
		Button^ btnDeleteSelected;
		Button^ btnEditSelected;
		Button^ btnSaveChanges;
		ListBox^ lstNotices;
		Label^ lblTitle;
		String^ oldNoticeText = "";

	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeNoticeBoardUI();
			InitializeDatabase();
			LoadAllNotices();
		}

	private:
		void InitializeNoticeBoardUI() {
			this->Text = "Hospital Management - Notice Board";
			this->Size = System::Drawing::Size(280, 320);
			lblTitle = gcnew Label();
			lblTitle->Text = "HOSPITAL ANNOUNCEMENTS";
			lblTitle->Location = Point(20, 10);
			lblTitle->AutoSize = true;
			lblTitle->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
			txtNoticeInput = gcnew TextBox();
			txtNoticeInput->Location = Point(20, 40);
			txtNoticeInput->Size = System::Drawing::Size(220, 50);
			txtNoticeInput->Multiline = true;
			btnPostNotice = gcnew Button();
			btnPostNotice->Text = "Post New";
			btnPostNotice->Location = Point(20, 100);
			btnPostNotice->Size = System::Drawing::Size(105, 30);
			btnPostNotice->BackColor = Color::LightBlue;
			btnPostNotice->Click += gcnew EventHandler(this, &MyForm::OnPostNoticeClick);
			btnSaveChanges = gcnew Button();
			btnSaveChanges->Text = "Save Edit";
			btnSaveChanges->Location = Point(135, 100);
			btnSaveChanges->Size = System::Drawing::Size(105, 30);
			btnSaveChanges->BackColor = Color::LightGreen;
			btnSaveChanges->Click += gcnew EventHandler(this, &MyForm::OnUpdateNoticeClick);
			lstNotices = gcnew ListBox();
			lstNotices->Location = Point(20, 140);
			lstNotices->Size = System::Drawing::Size(220, 80);
			lstNotices->BackColor = Color::LemonChiffon;
			btnEditSelected = gcnew Button();
			btnEditSelected->Text = "Edit Item";
			btnEditSelected->Location = Point(20, 230);
			btnEditSelected->Size = System::Drawing::Size(105, 30);
			btnEditSelected->Click += gcnew EventHandler(this, &MyForm::OnEditClick);

			btnDeleteSelected = gcnew Button();
			btnDeleteSelected->Text = "Delete Item";
			btnDeleteSelected->Location = Point(135, 230);
			btnDeleteSelected->Size = System::Drawing::Size(105, 30);
			btnDeleteSelected->BackColor = Color::MistyRose;
			btnDeleteSelected->Click += gcnew EventHandler(this, &MyForm::OnDeleteSelectedClick);

			this->Controls->Add(lblTitle);
			this->Controls->Add(txtNoticeInput);
			this->Controls->Add(btnPostNotice);
			this->Controls->Add(btnSaveChanges);
			this->Controls->Add(lstNotices);
			this->Controls->Add(btnEditSelected);
			this->Controls->Add(btnDeleteSelected);
		}
		void InitializeDatabase() {
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS Notices (ID INTEGER PRIMARY KEY AUTOINCREMENT, Content TEXT);", nullptr, 0, nullptr);
				sqlite3_close(DB);
			}
		}
		void LoadAllNotices() {
			sqlite3* DB; sqlite3_stmt* stmt; lstNotices->Items->Clear();
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				if (sqlite3_prepare_v2(DB, "SELECT Content FROM Notices ORDER BY ID DESC;", -1, &stmt, nullptr) == SQLITE_OK) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						lstNotices->Items->Add(gcnew String((const char*)sqlite3_column_text(stmt, 0)));
					}
				}
				sqlite3_finalize(stmt); sqlite3_close(DB);
			}
		}

		void OnPostNoticeClick(Object^ sender, EventArgs^ e) {
			if (String::IsNullOrWhiteSpace(txtNoticeInput->Text)) return;
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				msclr::interop::marshal_context context;
				std::string content = context.marshal_as<std::string>(txtNoticeInput->Text);
				sqlite3_exec(DB, ("INSERT INTO Notices (Content) VALUES ('" + content + "');").c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB);
				txtNoticeInput->Text = ""; LoadAllNotices();
			}
		}

		void OnEditClick(Object^ sender, EventArgs^ e) {
			if (lstNotices->SelectedItem != nullptr) {
				oldNoticeText = lstNotices->SelectedItem->ToString();
				txtNoticeInput->Text = oldNoticeText;
			}
		}

		void OnUpdateNoticeClick(Object^ sender, EventArgs^ e) {
			if (String::IsNullOrEmpty(oldNoticeText)) return;
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				msclr::interop::marshal_context context;
				std::string newT = context.marshal_as<std::string>(txtNoticeInput->Text);
				std::string oldT = context.marshal_as<std::string>(oldNoticeText);
				std::string sql = "UPDATE Notices SET Content = '" + newT + "' WHERE Content = '" + oldT + "';";
				sqlite3_exec(DB, sql.c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB);
				oldNoticeText = ""; txtNoticeInput->Text = ""; LoadAllNotices();
			}
		}
		void OnDeleteSelectedClick(Object^ sender, EventArgs^ e) {
			if (lstNotices->SelectedItem == nullptr) return;
			sqlite3* DB;
			if (sqlite3_open("hospital.db", &DB) == SQLITE_OK) {
				msclr::interop::marshal_context context;
				std::string target = context.marshal_as<std::string>(lstNotices->SelectedItem->ToString());
				sqlite3_exec(DB, ("DELETE FROM Notices WHERE Content = '" + target + "';").c_str(), nullptr, 0, nullptr);
				sqlite3_close(DB); LoadAllNotices();
			}
		}
	protected:
		~MyForm() {}
		void InitializeComponent(void) {}
	};
}

#endif 