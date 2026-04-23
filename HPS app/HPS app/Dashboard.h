#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "MyForm.h"
#include "BedTrackingForm.h"

namespace HospitalManagment {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Dashboard : public System::Windows::Forms::Form
	{
	private:
		Button^ btnOpenNotices;
		Button^ btnOpenBeds;
		Label^ lblWelcome;

	public:
		Dashboard(void)
		{
			InitializeComponent();
			BuildDashboardUI();
		}

	private:
		void BuildDashboardUI() {
			this->Text = "Hospital Management System - Dashboard";
			this->Size = System::Drawing::Size(400, 250);
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::FromArgb(45, 45, 48); // Dark professional theme

			lblWelcome = gcnew Label();
			lblWelcome->Text = "RESOURCES & FINANCE DASHBOARD";
			lblWelcome->ForeColor = Color::White;
			lblWelcome->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblWelcome->Location = Point(40, 30);
			lblWelcome->AutoSize = true;

			// Button 1: Notice Board
			btnOpenNotices = gcnew Button();
			btnOpenNotices->Text = "HOSPITAL NOTICE BOARD";
			btnOpenNotices->Location = Point(50, 80);
			btnOpenNotices->Size = System::Drawing::Size(300, 40);
			btnOpenNotices->BackColor = Color::LightBlue;
			btnOpenNotices->FlatStyle = FlatStyle::Flat;
			btnOpenNotices->Click += gcnew EventHandler(this, &Dashboard::OnNoticeClick);

			// Button 2: Bed Tracking
			btnOpenBeds = gcnew Button();
			btnOpenBeds->Text = "BED & ROOM TRACKING";
			btnOpenBeds->Location = Point(50, 140);
			btnOpenBeds->Size = System::Drawing::Size(300, 40);
			btnOpenBeds->BackColor = Color::LightGreen;
			btnOpenBeds->FlatStyle = FlatStyle::Flat;
			btnOpenBeds->Click += gcnew EventHandler(this, &Dashboard::OnBedClick);

			this->Controls->Add(lblWelcome);
			this->Controls->Add(btnOpenNotices);
			this->Controls->Add(btnOpenBeds);
		}

		// --- LOGIC: Launching Modules ---
		void OnNoticeClick(Object^ sender, EventArgs^ e) {
			MyForm^ noticeForm = gcnew MyForm();
			noticeForm->Show(); // Opens in a new window
		}

		void OnBedClick(Object^ sender, EventArgs^ e) {
			BedTrackingForm^ bedForm = gcnew BedTrackingForm();
			bedForm->Show(); // Opens in a new window
		}

	protected:
		~Dashboard() {}
		void InitializeComponent(void) {}
	};
}

#endif