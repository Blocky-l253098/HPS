#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace HPSapp;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    // Create and run the main dashboard
    Application::Run(gcnew MainForm());

    return 0;
}