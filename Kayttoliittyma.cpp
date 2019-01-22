#include"stdafx.h"
#include"Kayttoliittyma.h"

void Kayttoliittyma::piirraLauta() {

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 0) wcout << (" 8  ");
			if (j == 0 && i == 1) wcout << (" 7  ");
			if (j == 0 && i == 2) wcout << (" 6  ");
			if (j == 0 && i == 3) wcout << (" 5  ");
			if (j == 0 && i == 4) wcout << (" 4  ");
			if (j == 0 && i == 5) wcout << (" 3  ");
			if (j == 0 && i == 6) wcout << (" 2  ");
			if (j == 0 && i == 7) wcout << (" 1  ");

			if (i % 2 == 0 && j % 2 != 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (i % 2 != 0 && j % 2 == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (_asema->_lauta[i][j] != nullptr) {
				wcout << " " << _asema->_lauta[i][j]->getUnicode() << " ";
			}
			else wcout << "   ";
			if (i % 2 != 0 && j % 2 == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
			}
			if (i % 2 == 0 && j % 2 != 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
			}

			if (j == 7) wcout << endl;
		}
	}
	wcout << ("     a ");
	wcout << (" b ");
	wcout << (" c ");
	wcout << (" d ");
	wcout << (" e ");
	wcout << (" f ");
	wcout << (" g ");
	wcout << (" h ");
}

