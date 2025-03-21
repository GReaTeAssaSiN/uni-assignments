#include "LOG_IN.h"

using namespace CinemaServiceApplication;

//Точка входа в программу.
[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	CinemaServiceApplication::LOG_IN log_in_winform;
	Application::Run(% log_in_winform);
	return 0;
}