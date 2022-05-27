#include <iostream>
#include <iomanip>
#include <locale.h>
#include <windows.h>
#include "TextTable.h"
#include "conio.h"
#include "tchar.h"

using namespace std;

class start {
public:

	void creator() {

		cout << R"(
  /$$$$$$  /$$$$$$$$ /$$   /$$ /$$$$$$$$ /$$$$$$$$ /$$   /$$
 /$$__  $$| $$_____/| $$$ | $$|__  $$__/| $$_____/| $$  /$$/
| $$  \__/| $$      | $$$$| $$   | $$   | $$      | $$ /$$/ 
| $$ /$$$$| $$$$$   | $$ $$ $$   | $$   | $$$$$   | $$$$$/  
| $$|_  $$| $$__/   | $$  $$$$   | $$   | $$__/   | $$  $$  
| $$  \ $$| $$      | $$\  $$$   | $$   | $$      | $$\  $$ 
|  $$$$$$/| $$$$$$$$| $$ \  $$   | $$   | $$$$$$$$| $$ \  $$
 \______/ |________/|__/  \__/   |__/   |________/|__/  \__/
		
	WELCOME TO BIO-HUMAN TEST SCREEN

)" << endl;


		setlocale(LC_ALL, "Russian");
		// Set CP1251 instead of default CP866 to output Cyrillic text.
		SetConsoleOutputCP(1251);
		wprintf(L"\tЯгізджан Явуз");
		SetConsoleOutputCP(1026);
		setlocale(LC_ALL, "Turkish");
		wprintf(L" (Yağızcan Yavuz)");
		SetConsoleOutputCP(866);
		cout << " - KH-221ia.e\n\n";
	}


	void startScreen() {
		//windowSettings();
		creator();
	}
};
