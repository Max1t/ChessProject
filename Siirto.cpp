#include "stdafx.h"
#include "Siirto.h"
#include "Nappula.h"



Siirto::Siirto(Ruutu alku, Ruutu loppu)
{
	_alkuruutu = alku;
	_loppuRuutu = loppu;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna)
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
}

Ruutu Siirto::getAlkuruutu()
{
	return _alkuruutu;
}

Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}

bool Siirto::onkoLyhytLinna()
{
	return _lyhytLinna;
}

bool Siirto::onkoPitkaLinna()
{
	return _pitkaLinna;
}


void Siirto::printSiirto()
{
	std::wstring print;

	if (onkoLyhytLinna() == true)
	{
		wcout << L"0-0" << endl;
		return;
	}
	if (onkoPitkaLinna() == true)
	{
		wcout << L"0-0-0" << endl;
		return;
	}
	std::wstring toPrint;
	if (getAlkuruutu().getSarake() == 0) toPrint.append(L"a");
	if (getAlkuruutu().getSarake() == 1) toPrint.append(L"b");
	if (getAlkuruutu().getSarake() == 2) toPrint.append(L"c");
	if (getAlkuruutu().getSarake() == 3) toPrint.append(L"d");
	if (getAlkuruutu().getSarake() == 4) toPrint.append(L"e");
	if (getAlkuruutu().getSarake() == 5) toPrint.append(L"f");
	if (getAlkuruutu().getSarake() == 6) toPrint.append(L"g");
	if (getAlkuruutu().getSarake() == 7) toPrint.append(L"h");

	if (getAlkuruutu().getRivi() == 0) toPrint.append(L"8");
	if (getAlkuruutu().getRivi() == 1) toPrint.append(L"7");
	if (getAlkuruutu().getRivi() == 2) toPrint.append(L"6");
	if (getAlkuruutu().getRivi() == 3) toPrint.append(L"5");
	if (getAlkuruutu().getRivi() == 4) toPrint.append(L"4");
	if (getAlkuruutu().getRivi() == 5) toPrint.append(L"3");
	if (getAlkuruutu().getRivi() == 6) toPrint.append(L"2");
	if (getAlkuruutu().getRivi() == 7) toPrint.append(L"1");

	toPrint.append(L"-");

	if (getLoppuruutu().getSarake() == 0) toPrint.append(L"a");
	if (getLoppuruutu().getSarake() == 1) toPrint.append(L"b");
	if (getLoppuruutu().getSarake() == 2) toPrint.append(L"c");
	if (getLoppuruutu().getSarake() == 3) toPrint.append(L"d");
	if (getLoppuruutu().getSarake() == 4) toPrint.append(L"e");
	if (getLoppuruutu().getSarake() == 5) toPrint.append(L"f");
	if (getLoppuruutu().getSarake() == 6) toPrint.append(L"g");
	if (getLoppuruutu().getSarake() == 7) toPrint.append(L"h");

	if (getLoppuruutu().getRivi() == 0) toPrint.append(L"8");
	if (getLoppuruutu().getRivi() == 1) toPrint.append(L"7");
	if (getLoppuruutu().getRivi() == 2) toPrint.append(L"6");
	if (getLoppuruutu().getRivi() == 3) toPrint.append(L"5");
	if (getLoppuruutu().getRivi() == 4) toPrint.append(L"4");
	if (getLoppuruutu().getRivi() == 5) toPrint.append(L"3");
	if (getLoppuruutu().getRivi() == 6) toPrint.append(L"2");
	if (getLoppuruutu().getRivi() == 7) toPrint.append(L"1");

	wcout << toPrint << endl;
}