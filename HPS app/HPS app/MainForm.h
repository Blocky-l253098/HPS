#pragma once

// MOEED: Including your three modules here
#include "MyForm.h"
#include "BedTrackingForm.h"
#include "BillingModule.h"

namespace HPSapp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			ApplyMoeedStyles(); // Set the colors and text we chose in Dashboard.h
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ panel1;
		System::Windows::Forms::Panel^ pnlContent;
		System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
		System::Windows::Forms::Button^ button1; // Hide Sidebar
		System::Windows::Forms::Button^ button2; // Show Sidebar
		System::Windows::Forms::Button^ button6;   // Finance & Billing
		System::Windows::Forms::Button^ button5;   // Bed Tracking
		System::Windows::Forms::Button^ dashboard; // Notice Board
		System::Windows::Forms::Button^ button3;   // Exit
		System::ComponentModel::IContainer^ components;

	private:
		// --- MOEED'S STYLE INTEGRATION ---
		void ApplyMoeedStyles() {
			// Notice Board
			this->dashboard->Text = "1. NOTICE BOARD";
			this->dashboard->BackColor = Color::LightBlue;
			this->dashboard->FlatStyle = FlatStyle::Flat;

			// Bed Tracking
			this->button5->Text = "2. BED TRACKING";
			this->button5->BackColor = Color::LightGreen;
			this->button5->FlatStyle = FlatStyle::Flat;

			// Finance & Billing
			this->button6->Text = "3. FINANCE & BILLING";
			this->button6->BackColor = Color::Plum;
			this->button6->FlatStyle = FlatStyle::Flat;

			// Exit Button
			this->button3->Text = "EXIT SYSTEM";
			this->button3->BackColor = Color::MistyRose;
			this->button3->FlatStyle = FlatStyle::Flat;
		}

		// --- MOEED'S NAVIGATION LOGIC ---
		// This replaces Faizan's loadScreen because your modules are Forms, not UserControls
		void openChildForm(System::Windows::Forms::Form^ childForm) {
			if (pnlContent->Controls->Count > 0) {
				pnlContent->Controls->Clear();
			}
			childForm->TopLevel = false;
			childForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			childForm->Dock = DockStyle::Fill;
			pnlContent->Controls->Add(childForm);
			pnlContent->Tag = childForm;
			childForm->Show();
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pnlContent = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->dashboard = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->pnlContent->SuspendLayout();
			this->SuspendLayout();

			// panel1 (Sidebar)
			this->panel1->BackColor = System::Drawing::Color::DimGray;
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button6);
			this->panel1->Controls->Add(this->button5);
			this->panel1->Controls->Add(this->dashboard);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 613);
			this->panel1->TabIndex = 0;

			// button1 (Hide Sidebar)
			this->button1->Dock = System::Windows::Forms::DockStyle::Top;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(200, 48);
			this->button1->TabIndex = 0;
			this->button1->Text = L"<";
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);

			// pnlContent
			this->pnlContent->Controls->Add(this->button2);
			this->pnlContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlContent->Location = System::Drawing::Point(200, 0);
			this->pnlContent->Name = L"pnlContent";
			this->pnlContent->Size = System::Drawing::Size(380, 613);
			this->pnlContent->TabIndex = 1;

			// button2 (Show Sidebar)
			this->button2->Location = System::Drawing::Point(0, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(49, 34);
			this->button2->TabIndex = 0;
			this->button2->Text = L"=";
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);

			// sidebar buttons setup
			this->button3->Dock = System::Windows::Forms::DockStyle::Top;
			this->button3->Location = System::Drawing::Point(0, 195);
			this->button3->Size = System::Drawing::Size(200, 50);
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::OnExitClick);

			this->button6->Dock = System::Windows::Forms::DockStyle::Top;
			this->button6->Location = System::Drawing::Point(0, 146);
			this->button6->Size = System::Drawing::Size(200, 49);
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::OnBillingClick);

			this->button5->Dock = System::Windows::Forms::DockStyle::Top;
			this->button5->Location = System::Drawing::Point(0, 95);
			this->button5->Size = System::Drawing::Size(200, 51);
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::OnBedTrackingClick);

			this->dashboard->Dock = System::Windows::Forms::DockStyle::Top;
			this->dashboard->Location = System::Drawing::Point(0, 48);
			this->dashboard->Size = System::Drawing::Size(200, 47);
			this->dashboard->Click += gcnew System::EventHandler(this, &MainForm::OnNoticeBoardClick);

			// MainForm
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(580, 613);
			this->Controls->Add(this->pnlContent);
			this->Controls->Add(this->panel1);
			this->Name = L"MainForm";
			this->Text = L"HPS Dashboard - Finance & Resources";
			this->Load += gcnew System::EventHandler(this, &MainForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			this->pnlContent->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion

		// --- MOEED'S EVENT HANDLERS ---
		System::Void OnNoticeBoardClick(System::Object^ sender, System::EventArgs^ e) {
			openChildForm(gcnew HospitalManagment::MyForm());
		}

		System::Void OnBedTrackingClick(System::Object^ sender, System::EventArgs^ e) {
			openChildForm(gcnew HospitalManagment::BedTrackingForm());
		}

		System::Void OnBillingClick(System::Object^ sender, System::EventArgs^ e) {
			openChildForm(gcnew HospitalManagment::BillingModule());
		}

		System::Void OnExitClick(System::Object^ sender, System::EventArgs^ e) {
			Application::Exit();
		}

		// --- SIDEBAR TOGGLE LOGIC ---
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			panel1->Visible = 0;
			button2->Visible = 1;
		}
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			panel1->Visible = 1;
			button2->Visible = 0;
		}
		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			panel1->Visible = 0; // Starts with sidebar closed
		}
	};
}
