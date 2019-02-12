#include "stdafx.h"
#include "Asema.h"
#include "Nappula.h"
#include <string>
#include <iostream>
using namespace std;

Asema::Asema()
{
	int vt = VT;
	int vr = VR;
	int vl = VL;
	int vd = VD;
	int vk = VK;
	int vs = VS;
	int mt = MT;
	int mr = MR;
	int ml = ML;
	int mk = MK;
	int ms = MS;
	int md = MD;

	/*
	VK, L"\u2654"
	VD, L"\u2655"
	VT, L"\u2656"
	VL, L"\u2657"
	VR, L"\u2658"
	VS, L"\u2659"
	MK, L"\u265A"
	MD, L"\u265B"
	MT, L"\u265C”
	ML, L"\u265D"
	MR, L"\u265E"
	MS, L"\u265F"

	*/

	Nappula* VT = new Torni(L"\u2656", vt, 0);		// Valkoinen Torni 
	Nappula* VR = new Ratsu(L"\u2658", vr, 0);		// Valkoinen Ratsu
	Nappula* VS = new Sotilas(L"\u2659", vs, 0);	// Valkoinen Sotilas

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = NULL;
		}
	}
	_lauta[7][0] = VT;
	_lauta[7][1] = VR;
	_lauta[6][4] = VS;
	/*
	Nappula* VK =  // Valkoinen Kuningas
	Nappula* VD =  // Valkoinen Daami
	Nappula* VT =  // Valkoinen Torni
	Nappula* VL =  // Valkoinen Lähetti
	Nappula* VR =  // Valkoinen Ratsu
	Nappula* VS =  // Valkoinen Sotilas

	Nappula* MK =  // Musta Kuningas
	Nappula* MD =  // Musta Daam
	Nappula* MT =  // Musta Torni
	Nappula* ML =  // Musta Lähetti
	Nappula* MR =  // Musta Ratsu
	Nappula* MS =  // Musta Sotilas



	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = NULL;
		}
	}

	// Musta puoli 1 rivi

	_lauta[0][0] = MT;
	_lauta[0][1] = ML;
	_lauta[0][2] = MR;
	_lauta[0][3] = MD;
	_lauta[0][4] = MK;
	_lauta[0][5] = VL;
	_lauta[0][6] = MR;
	_lauta[0][7] = MT;
	// Musta puoli 2 rivi
	for (int i = 0; i < 8; i++) {
		_lauta[1][i] = MS;
	}



	// Valkoinen puoli 1 rivi
	_lauta[7][0] = VT;
	_lauta[7][1] = VR;
	_lauta[7][2] = VL;
	_lauta[7][3] = VD;
	_lauta[7][4] = VK;
	_lauta[7][5] = VL;
	_lauta[7][6] = VR;
	_lauta[7][7] = VT;


	// Valkoinen puoli 2 rivi
	for (int i = 0; i < 8; i++) {
		_lauta[6][i] = VS;

	}*/
}

void Asema::paivitaAsema(Siirto* siirto)
{
	if (siirto->onkoLyhytLinna() == true)
	{
		if (_siirtoVuoro == 1)
		{
			_lauta[0][6] = _lauta[0][4];
			_lauta[0][5] = _lauta[0][7];
			_lauta[0][4] = nullptr;
			_lauta[0][7] = nullptr;
			if (_siirtoVuoro == 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}

		if (_siirtoVuoro == 0)
		{
			_lauta[7][6] = _lauta[7][4];
			_lauta[7][5] = _lauta[7][7];
			_lauta[7][4] = nullptr;
			_lauta[7][7] = nullptr;
			if (_siirtoVuoro == 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}
	}

	if (siirto->onkoPitkaLinna() == true)
	{
		if (_siirtoVuoro == 1)
		{
			_lauta[0][2] = _lauta[0][4];
			_lauta[0][3] = _lauta[0][0];
			_lauta[0][4] = nullptr;
			_lauta[0][0] = nullptr;
			if (_siirtoVuoro = 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}

		if (_siirtoVuoro == 0)
		{
			_lauta[7][6] = _lauta[7][4];
			_lauta[7][5] = _lauta[7][7];
			_lauta[7][4] = nullptr;
			_lauta[7][7] = nullptr;
			if (_siirtoVuoro = 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}
	}
	// Siirretäänkö Valkoista tornia ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == VT)
	{
		if (siirto->getAlkuruutu().getSarake() == 0 && _onkoValkeaKTliikkunut == false)
		{
			_onkoValkeaKTliikkunut = true;
		}

		if (siirto->getAlkuruutu().getSarake() == 7 && _onkoValkeaDTliikkunut == false)
		{
			_onkoValkeaDTliikkunut = true;
		}

	}
	// Siirretäänkö Mustaa tornia ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == MT)
	{
		if (siirto->getAlkuruutu().getSarake() == 0 && _onkoMustaKTliikkunut == false)
		{
			_onkoMustaKTliikkunut = true;
		}

		if (siirto->getAlkuruutu().getSarake() == 7 && _onkoMustaDTliikkunut == false)
		{
			_onkoMustaDTliikkunut = true;
		}

	}
	// Siirretäänkö mustaa kuningasta ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == MK && _onkoMustaKuningasLiikkunut == false)
	{
		_onkoMustaKuningasLiikkunut = true;
	}

	// Siirretäänkö valkoista kuningasta ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == VK && _onkoMustaKuningasLiikkunut == false)
	{
		_onkoMustaKuningasLiikkunut = true;
	}


	if (siirto->onkoLyhytLinna() == false && siirto->onkoPitkaLinna() == false)
	{
		Nappula* tempNappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
	}

	/*if (_siirtoVuoro == 0) _siirtoVuoro = 1;
	else _siirtoVuoro = 0;*/
	return;
}


void Asema::printLaillisetSiirrot(std::list<Siirto>& lista)
{
	wcout << endl << L"Lailliset siirrot:" << endl;
	for (Siirto siirto : lista)
	{
		std::wstring toPrint;
		if (siirto.getAlkuruutu().getSarake() == 0) toPrint.append(L"a");
		if (siirto.getAlkuruutu().getSarake() == 1) toPrint.append(L"b");
		if (siirto.getAlkuruutu().getSarake() == 2) toPrint.append(L"c");
		if (siirto.getAlkuruutu().getSarake() == 3) toPrint.append(L"d");
		if (siirto.getAlkuruutu().getSarake() == 4) toPrint.append(L"e");
		if (siirto.getAlkuruutu().getSarake() == 5) toPrint.append(L"f");
		if (siirto.getAlkuruutu().getSarake() == 6) toPrint.append(L"g");
		if (siirto.getAlkuruutu().getSarake() == 7) toPrint.append(L"h");

		if (siirto.getAlkuruutu().getRivi() == 0) toPrint.append(L"8");
		if (siirto.getAlkuruutu().getRivi() == 1) toPrint.append(L"7");
		if (siirto.getAlkuruutu().getRivi() == 2) toPrint.append(L"6");
		if (siirto.getAlkuruutu().getRivi() == 3) toPrint.append(L"5");
		if (siirto.getAlkuruutu().getRivi() == 4) toPrint.append(L"4");
		if (siirto.getAlkuruutu().getRivi() == 5) toPrint.append(L"3");
		if (siirto.getAlkuruutu().getRivi() == 6) toPrint.append(L"2");
		if (siirto.getAlkuruutu().getRivi() == 7) toPrint.append(L"1");

		toPrint.append(L"-");

		if (siirto.getLoppuruutu().getSarake() == 0) toPrint.append(L"a");
		if (siirto.getLoppuruutu().getSarake() == 1) toPrint.append(L"b");
		if (siirto.getLoppuruutu().getSarake() == 2) toPrint.append(L"c");
		if (siirto.getLoppuruutu().getSarake() == 3) toPrint.append(L"d");
		if (siirto.getLoppuruutu().getSarake() == 4) toPrint.append(L"e");
		if (siirto.getLoppuruutu().getSarake() == 5) toPrint.append(L"f");
		if (siirto.getLoppuruutu().getSarake() == 6) toPrint.append(L"g");
		if (siirto.getLoppuruutu().getSarake() == 7) toPrint.append(L"h");

		if (siirto.getLoppuruutu().getRivi() == 0) toPrint.append(L"8");
		if (siirto.getLoppuruutu().getRivi() == 1) toPrint.append(L"7");
		if (siirto.getLoppuruutu().getRivi() == 2) toPrint.append(L"6");
		if (siirto.getLoppuruutu().getRivi() == 3) toPrint.append(L"5");
		if (siirto.getLoppuruutu().getRivi() == 4) toPrint.append(L"4");
		if (siirto.getLoppuruutu().getRivi() == 5) toPrint.append(L"3");
		if (siirto.getLoppuruutu().getRivi() == 6) toPrint.append(L"2");
		if (siirto.getLoppuruutu().getRivi() == 7) toPrint.append(L"1");

		wcout << toPrint << endl;

	}
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	Asema* asema = this;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_lauta[i][j] != NULL)
			{
				if (_lauta[i][j]->getVari() == _siirtoVuoro)
				{
					_lauta[i][j]->annaSiirrot(lista, (new Ruutu(i, j)), asema, _lauta[i][j]->getVari());
				}
			}
		}
	}
}

bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}

bool Asema::getOnkoMustaKuningasLiikunut()
{
	return _onkoMustaKuningasLiikkunut;
}

bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}

bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}

bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}

bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}

int Asema::getSiirtovuoro()
{
	return _siirtoVuoro;
}

void Asema::setSiirtovuoro(int vari)
{
	_siirtoVuoro = vari;
}
