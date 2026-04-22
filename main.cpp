#include "pch.h"
#include <Windows.h>
#include "LoginForm.h"
#include "AdminDashboardForm.h"
#include "DoctorDashboardForm.h"
#include "PatientDashboardForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace HPSapp;

[STAThreadAttribute]
int main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	LoginForm^ loginForm = gcnew LoginForm();
	Application::Run(loginForm);

	return 0;
}
