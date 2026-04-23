#include "Dashboard.h" /
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Launch the Main Dashboard
    HospitalManagment::Dashboard mainDashboard;
    Application::Run(% mainDashboard);

    return 0;
}