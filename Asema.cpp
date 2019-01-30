#include "stdafx.h"
#include "Asema.h"
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


	Nappula* VK = new Nappula(L"\u2654", 0, vk); // Valkoinen Kuningas
	Nappula* VD = new Nappula(L"\u2655", 0, vd); // Valkoinen Daami
	Nappula* VT = new Nappula(L"\u2656", 0, vt); // Valkoinen Torni
	Nappula* VL = new Nappula(L"\u2657", 0, vl); // Valkoinen Lähetti
	Nappula* VR = new Nappula(L"\u2658", 0, vr); // Valkoinen Ratsu
	Nappula* VS = new Nappula(L"\u2659", 0, vs); // Valkoinen Sotilas

	Nappula* MK = new Nappula(L"\u265A", 1, mk); // Musta Kuningas
	Nappula* MD = new Nappula(L"\u265B", 1, md); // Musta Daami
	Nappula* MT = new Nappula(L"\u265C", 1, mt); // Musta Torni
	Nappula* ML = new Nappula(L"\u265D", 1, ml); // Musta Lähetti
	Nappula* MR = new Nappula(L"\u265E", 1, mr); // Musta Ratsu
	Nappula* MS = new Nappula(L"\u265F", 1, ms); // Musta Sotilas



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

	}
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

	if (_siirtoVuoro == 0) _siirtoVuoro = 1;
	else _siirtoVuoro = 0;
	return;
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
