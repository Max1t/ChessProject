
#include"stdafx.h"
#include"Kayttoliittyma.h"

void Kayttoliittyma::piirraLauta() {

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 0) wcout << (" 8 ");
			if (j == 0 && i == 1) wcout << (" 7 ");
			if (j == 0 && i == 2) wcout << (" 6 ");
			if (j == 0 && i == 3) wcout << (" 5 ");
			if (j == 0 && i == 4) wcout << (" 4 ");
			if (j == 0 && i == 5) wcout << (" 3 ");
			if (j == 0 && i == 6) wcout << (" 2 ");
			if (j == 0 && i == 7) wcout << (" 1 ");

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
	wcout << ("    a ");
	wcout << (" b ");
	wcout << (" c ");
	wcout << (" d ");
	wcout << (" e ");
	wcout << (" f ");
	wcout << (" g ");
	wcout << (" h ") << endl;
}


Siirto* Kayttoliittyma::annaSiirto()
{
	std::wstring syotto;

	int alkuSarake;
	int alkuRivi;

	int loppuSarake;
	int loppuRivi;
	while (true) {
		wcout << "Siirtovuoro: " << _asema->getSiirtovuoro() << endl;
		wcout << "Anna siirto muodossa nappulankirjain,alkuruutu,loppuruutu" << endl;
		wcout << "Esim \"Rg1-f3\", lyhyt linna = \"0-0\" pitkä linna = \"0-0-0\"" << endl;
		wcin >> syotto;


		if (syotto == std::wstring(L"0-0"))
		{
			return new Siirto(true, false);
		}
		if (syotto == std::wstring(L"0-0-0"))
		{
			return new Siirto(false, true);
		}

		std::wstring Nappula = syotto.substr(0, 1);
		std::wstring Alkuruutusarake = syotto.substr(1, 1);
		std::wstring Alkuruuturivi = syotto.substr(2, 1);
		std::wstring Loppuruutusarake = syotto.substr(4, 1);
		std::wstring Loppuruuturivi = syotto.substr(5, 1);

		if (Alkuruutusarake == std::wstring(L"a")) alkuSarake = 0;
		else if (Alkuruutusarake == std::wstring(L"b")) alkuSarake = 1;
		else if (Alkuruutusarake == std::wstring(L"c")) alkuSarake = 2;
		else if (Alkuruutusarake == std::wstring(L"d")) alkuSarake = 3;
		else if (Alkuruutusarake == std::wstring(L"e")) alkuSarake = 4;
		else if (Alkuruutusarake == std::wstring(L"f")) alkuSarake = 5;
		else if (Alkuruutusarake == std::wstring(L"g")) alkuSarake = 6;
		else if (Alkuruutusarake == std::wstring(L"h")) alkuSarake = 7;
		else
		{
			wcout << "Siirto annettu väärässä muodossa. Yritä uudelleen" << endl;
			continue;
		}

		if (Alkuruuturivi == std::wstring(L"1")) alkuRivi = 7;
		else if (Alkuruuturivi == std::wstring(L"2")) alkuRivi = 6;
		else if (Alkuruuturivi == std::wstring(L"3")) alkuRivi = 5;
		else if (Alkuruuturivi == std::wstring(L"4")) alkuRivi = 4;
		else if (Alkuruuturivi == std::wstring(L"5")) alkuRivi = 3;
		else if (Alkuruuturivi == std::wstring(L"6")) alkuRivi = 2;
		else if (Alkuruuturivi == std::wstring(L"7")) alkuRivi = 1;
		else if (Alkuruuturivi == std::wstring(L"8")) alkuRivi = 0;
		else
		{
			wcout << "Siirto annettu väärässä muodossa. Yritä uudelleen" << endl;
			continue;
		}

		if (Loppuruutusarake == std::wstring(L"a")) loppuSarake = 0;
		else if (Loppuruutusarake == std::wstring(L"b")) loppuSarake = 1;
		else if (Loppuruutusarake == std::wstring(L"c")) loppuSarake = 2;
		else if (Loppuruutusarake == std::wstring(L"d")) loppuSarake = 3;
		else if (Loppuruutusarake == std::wstring(L"e")) loppuSarake = 4;
		else if (Loppuruutusarake == std::wstring(L"f")) loppuSarake = 5;
		else if (Loppuruutusarake == std::wstring(L"g")) loppuSarake = 6;
		else if (Loppuruutusarake == std::wstring(L"h")) loppuSarake = 7;
		else
		{
			wcout << "Siirto annettu väärässä muodossa. Yritä uudelleen" << endl;
			continue;
		}

		if (Loppuruuturivi == std::wstring(L"1")) loppuRivi = 7;
		else if (Loppuruuturivi == std::wstring(L"2")) loppuRivi = 6;
		else if (Loppuruuturivi == std::wstring(L"3")) loppuRivi = 5;
		else if (Loppuruuturivi == std::wstring(L"4")) loppuRivi = 4;
		else if (Loppuruuturivi == std::wstring(L"5")) loppuRivi = 3;
		else if (Loppuruuturivi == std::wstring(L"6")) loppuRivi = 2;
		else if (Loppuruuturivi == std::wstring(L"7")) loppuRivi = 1;
		else if (Loppuruuturivi == std::wstring(L"8")) loppuRivi = 0;
		else
		{
			wcout << "Siirto annettu väärässä muodossa. Yritä uudelleen" << endl;
			continue;
		}

		Ruutu AlkuRuutu = Ruutu(alkuRivi, alkuSarake);
		Ruutu LoppuRuutu = Ruutu(loppuRivi, loppuSarake);

		Siirto* VastustajanSiirto = new Siirto(AlkuRuutu, LoppuRuutu);

		return VastustajanSiirto;
	}

}