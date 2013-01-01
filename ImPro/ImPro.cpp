// ImPro.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "MainForm.h"

using namespace ImPro;

[STAThreadAttribute]
int main(array<System::String ^> ^args){
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew MainForm());

	_CrtDumpMemoryLeaks();
	return 0;
}
