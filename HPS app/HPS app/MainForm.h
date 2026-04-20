#pragma once

namespace HPSapp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ pnlContent;


	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ dashboard;
	private: System::Windows::Forms::Button^ button3;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
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
			// 
			// panel1
			// 
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
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Top;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(200, 48);
			this->button1->TabIndex = 0;
			this->button1->Text = L"<";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// pnlContent
			// 
			this->pnlContent->Controls->Add(this->button2);
			this->pnlContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlContent->Location = System::Drawing::Point(200, 0);
			this->pnlContent->Name = L"pnlContent";
			this->pnlContent->Size = System::Drawing::Size(380, 613);
			this->pnlContent->TabIndex = 1;
			this->pnlContent->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::pnlContent_Paint);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(0, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(49, 34);
			this->button2->TabIndex = 0;
			this->button2->Text = L"=";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Top;
			this->button3->Location = System::Drawing::Point(0, 195);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(200, 50);
			this->button3->TabIndex = 1;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// dashboard
			// 
			this->dashboard->Dock = System::Windows::Forms::DockStyle::Top;
			this->dashboard->Location = System::Drawing::Point(0, 48);
			this->dashboard->Name = L"dashboard";
			this->dashboard->Size = System::Drawing::Size(200, 47);
			this->dashboard->TabIndex = 1;
			this->dashboard->Text = L"Dashboard";
			this->dashboard->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Top;
			this->button5->Location = System::Drawing::Point(0, 95);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(200, 51);
			this->button5->TabIndex = 2;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Top;
			this->button6->Location = System::Drawing::Point(0, 146);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(200, 49);
			this->button6->TabIndex = 3;
			this->button6->Text = L"button6";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(580, 613);
			this->Controls->Add(this->pnlContent);
			this->Controls->Add(this->panel1);
			this->Name = L"MainForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			this->pnlContent->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	private:
		void loadScreen(System::Windows::Forms::UserControl^ screen) {
			if (pnlContent->Controls->Count > 0) {
				pnlContent->Controls->Clear();
			}

			screen->Dock = System::Windows::Forms::DockStyle::Fill;

			pnlContent->Controls->Add(screen);
		}

	private: System::Void btnAppointments_Click(System::Object^ sender, System::EventArgs^ e) {
		// This is what Zahab will give you later
		// loadScreen(gcnew ZahabAppointmentControl()); 
	}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = 0;
	}
	private: System::Void pnlContent_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void vScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	panel1->Visible = 0;
	button2->Visible = 1;
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	panel1->Visible = 1;
	button2->Visible = 0;
}	
};
}
