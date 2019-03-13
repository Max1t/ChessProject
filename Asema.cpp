#include "stdafx.h"
#include "Asema.h"
#include "Nappula.h"
#include <string>
#include <iostream>
using namespace std;


Nappula* Asema::vt = new Torni(L"\u2656", VT, 0);		// Valkoinen Torni 
Nappula* Asema::vr = new Ratsu(L"\u2658", VR, 0);		// Valkoinen Ratsu
Nappula* Asema::vs = new Sotilas(L"\u2659", VS, 0);	// Valkoinen Sotilas
Nappula* Asema::vd = new Kuningatar(L"\u2655", VD, 0);	// Valkoinen Kuningatar
Nappula* Asema::vk = new Kuningas(L"\u2654", VK, 0);	// Valkoinen Kuningas
Nappula* Asema::vl = new Lähetti(L"\u2657", VL, 0);	// Valkoinen Lähetti

Nappula* Asema::mt = new Torni(L"\u265C", MT, 1);		// Musta Torni 
Nappula* Asema::mr = new Ratsu(L"\u265E", MR, 1);		// Musta Ratsu
Nappula* Asema::ms = new Sotilas(L"\u265F", MS, 1);	// Musta Sotilas
Nappula* Asema::md = new Kuningatar(L"\u265B", MD, 1);	// Musta Kuningatar
Nappula* Asema::mk = new Kuningas(L"\u265A", MK, 1);	// Musta Kuningas
Nappula* Asema::ml = new Lähetti(L"\u265D", ML, 1);	// Musta Lähetti

Asema::Asema()
{
	Ohestalyönti _ohestalyönti;

	// Kenttä tyhjäksi
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = NULL;
		}
	}


	// Valkoinen puoli 1 rivi
	_lauta[7][0] = vt;
	_lauta[7][1] = vr;
	_lauta[7][2] = vl;
	_lauta[7][3] = vd;
	_lauta[7][4] = vk;
	_lauta[7][5] = vl;
	_lauta[7][6] = vr;
	_lauta[7][7] = vt;

	// Valkoinen puoli 2 rivi sotilaat
	for (int i = 0; i < 8; i++) {
		_lauta[6][i] = vs;
	}

	// Musta rivi 1
	_lauta[0][0] = mt;
	_lauta[0][1] = mr;
	_lauta[0][2] = ml;
	_lauta[0][3] = md;
	_lauta[0][4] = mk;
	_lauta[0][5] = ml;
	_lauta[0][6] = mr;
	_lauta[0][7] = mt;

	_lauta[0][4] = mk;
	// Musta rivi 2 sotilaat
	for (int i = 0; i < 8; i++) {
		_lauta[1][i] = ms;

	}

}

Asema::Asema(const Asema &obj)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = obj._lauta[i][j];
		}
	}
}
void Asema::paivitaAsema(Siirto *siirto)
{
	if (siirto->onkoLyhytLinna() == true)
	{
		if (_siirtoVuoro == 1)
		{
			_lauta[0][6] = _lauta[0][4];
			_lauta[0][5] = _lauta[0][7];
			_lauta[0][4] = nullptr;
			_lauta[0][7] = nullptr;
			_ohestalyönti.setOnkoOhestaMahdollinen(false);
			_onkoMustaKuningasLiikkunut = true;
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
			_ohestalyönti.setOnkoOhestaMahdollinen(false);
			_onkoValkeaKuningasLiikkunut = true;
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
			_ohestalyönti.setOnkoOhestaMahdollinen(false);
			_onkoMustaKuningasLiikkunut = true;
			if (_siirtoVuoro == 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}

		if (_siirtoVuoro == 0)
		{
			_lauta[7][2] = _lauta[7][4];
			_lauta[7][3] = _lauta[7][0];
			_lauta[7][4] = nullptr;
			_lauta[7][0] = nullptr;
			_ohestalyönti.setOnkoOhestaMahdollinen(false);
			_onkoValkeaKuningasLiikkunut = true;
			if (_siirtoVuoro == 0) _siirtoVuoro = 1;
			else _siirtoVuoro = 0;
			return;
		}
	}
	// Jos torni syödään ennen kuin se liikkuu tämä estää linnottautumisen jos toinen torni liikkuu sen paikalle
	//---------------------------------------------------------------------------------------------------------------------
	if (_onkoMustaDTliikkunut == false && siirto->getLoppuruutu().getRivi() == 0 && siirto->getLoppuruutu().getSarake() == 0)
	{
		_onkoMustaDTliikkunut = true;
	}
	if (_onkoMustaKTliikkunut == false && siirto->getLoppuruutu().getRivi() == 0 && siirto->getLoppuruutu().getSarake() == 7)
	{
		_onkoMustaKTliikkunut = true;
	}
	if (_onkoMustaDTliikkunut == false && siirto->getLoppuruutu().getRivi() == 7 && siirto->getLoppuruutu().getSarake() == 0)
	{
		_onkoValkeaDTliikkunut = true;
	}
	if (_onkoMustaKTliikkunut == false && siirto->getLoppuruutu().getRivi() == 7 && siirto->getLoppuruutu().getSarake() == 7)
	{
		_onkoValkeaKTliikkunut = true;
	}
	//----------------------------------------------------------------------------------------------------------------------

	// Siirretäänkö Valkoista tornia ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == VT)
	{
		if (siirto->getAlkuruutu().getSarake() == 7 && _onkoValkeaKTliikkunut == false)
		{
			_onkoValkeaKTliikkunut = true;
		}

		if (siirto->getAlkuruutu().getSarake() == 0 && _onkoValkeaDTliikkunut == false)
		{
			_onkoValkeaDTliikkunut = true;
		}

	}
	// Siirretäänkö Mustaa tornia ensimmäisen kerran
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == MT)
	{
		if (siirto->getAlkuruutu().getSarake() == 7 && _onkoMustaKTliikkunut == false)
		{
			_onkoMustaKTliikkunut = true;
		}

		if (siirto->getAlkuruutu().getSarake() == 0 && _onkoMustaDTliikkunut == false)
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
	if (_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()]->getKoodi() == VK && _onkoValkeaKuningasLiikkunut == false)
	{
		_onkoValkeaKuningasLiikkunut = true;
	}

	// Jos ohestalyönti on mahdollinen päivittää aseman oikein jos ohestalyönti tapahtuu, seuraa myös ohestalyönnin mahdollisuutta
	if (siirto->onkoLyhytLinna() == false && siirto->onkoPitkaLinna() == false && _ohestalyönti.onkoOhestaMahdollinen() == true)
	{
		Nappula* tempNappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];

		if (tempNappula->getKoodi() == VS && siirto->getMiksiKorotetaan() != 0)
		{
			if (siirto->getMiksiKorotetaan() == 1) { tempNappula = vd; }	// Valkoinen Kuningatar
			if (siirto->getMiksiKorotetaan() == 2) { tempNappula = vr; }	// Valkoinen Ratsu
			if (siirto->getMiksiKorotetaan() == 3) { tempNappula = vl; }	// Valkoinen Lähettti
			if (siirto->getMiksiKorotetaan() == 4) { tempNappula = vt; }	// Valkoinen Torni
		}
		if (tempNappula->getKoodi() == MS && siirto->getMiksiKorotetaan() != 0)
		{
			if (siirto->getMiksiKorotetaan() == 1) { tempNappula = md; }	// Valkoinen Kuningatar
			if (siirto->getMiksiKorotetaan() == 2) { tempNappula = mr; }	// Valkoinen Ratsu
			if (siirto->getMiksiKorotetaan() == 3) { tempNappula = ml; }	// Valkoinen Lähettti
			if (siirto->getMiksiKorotetaan() == 4) { tempNappula = mt; }	// Valkoinen Torni
		}

		// Ohestalyöntitarkistus alku
		if (tempNappula->getKoodi() == VS || tempNappula->getKoodi() == MS) {
			if (tempNappula->getKoodi() == VS)
			{
				if (siirto->getLoppuruutu().getRivi() == (siirto->getAlkuruutu().getRivi() - 2))
				{
					_ohestalyönti.setLyöntiRivi((siirto->getAlkuruutu().getRivi() - 1));
					_ohestalyönti.setLyöntiSarake(siirto->getAlkuruutu().getSarake());
					_ohestalyönti.setKohdeRivi(siirto->getLoppuruutu().getRivi());
					_ohestalyönti.setKohdeSarake(siirto->getLoppuruutu().getSarake());
					_ohestalyönti.setOnkoOhestaMahdollinen(true);
					_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
					_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
					if (_siirtoVuoro == 0) _siirtoVuoro = 1;
					else _siirtoVuoro = 0;
					return;
				}
			}
			if (tempNappula->getKoodi() == MS)
			{
				if (siirto->getLoppuruutu().getRivi() == (siirto->getAlkuruutu().getRivi() + 2))
				{
					_ohestalyönti.setLyöntiRivi((siirto->getAlkuruutu().getRivi() + 1));
					_ohestalyönti.setLyöntiSarake(siirto->getAlkuruutu().getSarake());
					_ohestalyönti.setKohdeRivi(siirto->getLoppuruutu().getRivi());
					_ohestalyönti.setKohdeSarake(siirto->getLoppuruutu().getSarake());
					_ohestalyönti.setOnkoOhestaMahdollinen(true);
					_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
					_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
					if (_siirtoVuoro == 0) _siirtoVuoro = 1;
					else _siirtoVuoro = 0;
					return;
				}
			}
			if (siirto->getLoppuruutu().getRivi() == _ohestalyönti.getLyöntiRivi() && siirto->getLoppuruutu().getSarake() == _ohestalyönti.getLyöntiSarake())
			{
				_lauta[_ohestalyönti.getKohdeRivi()][_ohestalyönti.getKohdeSarake()] = nullptr;
			}
		}
		// Ohestalyöntitarkistus loppu
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
		_ohestalyönti.setOnkoOhestaMahdollinen(false);
		if (_siirtoVuoro == 0) _siirtoVuoro = 1;
		else _siirtoVuoro = 0;
		return;
	}

	// Default aseman päivitys, ei erikoisliikkeitä, jos sotilas liikkuu kaksi ruutua päivitetään ohestalyönnin mahdollisuus
	if (siirto->onkoLyhytLinna() == false && siirto->onkoPitkaLinna() == false)
	{
		Nappula* tempNappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];

		// Korotus 
		if (tempNappula->getKoodi() == VS && siirto->getMiksiKorotetaan() != 0)
		{
			if (siirto->getMiksiKorotetaan() == 1) { tempNappula = vd; }	// Valkoinen Kuningatar
			if (siirto->getMiksiKorotetaan() == 2) { tempNappula = vr; }	// Valkoinen Ratsu
			if (siirto->getMiksiKorotetaan() == 3) { tempNappula = vl; }	// Valkoinen Lähettti
			if (siirto->getMiksiKorotetaan() == 4) { tempNappula = vt; }	// Valkoinen Torni
		}
		if (tempNappula->getKoodi() == MS && siirto->getMiksiKorotetaan() != 0)
		{
			if (siirto->getMiksiKorotetaan() == 1) { tempNappula = md; }	// Valkoinen Kuningatar
			if (siirto->getMiksiKorotetaan() == 2) { tempNappula = mr; }	// Valkoinen Ratsu
			if (siirto->getMiksiKorotetaan() == 3) { tempNappula = ml; }	// Valkoinen Lähettti
			if (siirto->getMiksiKorotetaan() == 4) { tempNappula = mt; }	// Valkoinen Torni
		}

		if (tempNappula->getKoodi() == VS || tempNappula->getKoodi() == MS) {
			if (tempNappula->getKoodi() == VS)
			{
				if (siirto->getLoppuruutu().getRivi() == (siirto->getAlkuruutu().getRivi() - 2))
				{
					_ohestalyönti.setLyöntiRivi((siirto->getAlkuruutu().getRivi() - 1));
					_ohestalyönti.setLyöntiSarake(siirto->getAlkuruutu().getSarake());
					_ohestalyönti.setKohdeRivi(siirto->getLoppuruutu().getRivi());
					_ohestalyönti.setKohdeSarake(siirto->getLoppuruutu().getSarake());
					_ohestalyönti.setOnkoOhestaMahdollinen(true);
					_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
					_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
					if (_siirtoVuoro == 0) _siirtoVuoro = 1;
					else _siirtoVuoro = 0;
					return;
				}
			}
			if (tempNappula->getKoodi() == MS)
			{
				if (siirto->getLoppuruutu().getRivi() == (siirto->getAlkuruutu().getRivi() + 2))
				{
					_ohestalyönti.setLyöntiRivi((siirto->getAlkuruutu().getRivi() + 1));
					_ohestalyönti.setLyöntiSarake(siirto->getAlkuruutu().getSarake());
					_ohestalyönti.setKohdeRivi(siirto->getLoppuruutu().getRivi());
					_ohestalyönti.setKohdeSarake(siirto->getLoppuruutu().getSarake());
					_ohestalyönti.setOnkoOhestaMahdollinen(true);
					_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
					_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
					if (_siirtoVuoro == 0) _siirtoVuoro = 1;
					else _siirtoVuoro = 0;
					return;
				}
			}
		}
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = tempNappula;
		_ohestalyönti.setOnkoOhestaMahdollinen(false);
	}
	// Siirtovuoron vaihto
	if (_siirtoVuoro == 0) _siirtoVuoro = 1;
	else _siirtoVuoro = 0;
	return;
}

// Käy läpi annetun siirtolistan ja tulostaa kaikki siirrot
void Asema::printLaillisetSiirrot(std::list<Siirto>& lista)
{
	wcout << endl << L"Lailliset siirrot:" << endl;
	for (Siirto siirto : lista)
	{
		if (siirto.onkoLyhytLinna() == true)
		{
			wcout << L"0-0" << endl;
			continue;
		}
		if (siirto.onkoPitkaLinna() == true)
		{
			wcout << L"0-0-0" << endl;
			continue;
		}
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
		if (siirto.getMiksiKorotetaan() != 0)
		{
			if (siirto.getMiksiKorotetaan() == 1) toPrint.append(L" Korotus kuningattareksi");
			if (siirto.getMiksiKorotetaan() == 2) toPrint.append(L" Korotus ratsuksi");
			if (siirto.getMiksiKorotetaan() == 3) toPrint.append(L" Korotus lähetiksi");
			if (siirto.getMiksiKorotetaan() == 4) toPrint.append(L" Korotus torniksi");
		}

		wcout << toPrint << endl;

	}
}
// Käy läpi tämänhetkisen aseman kaikki nappulat läpi ja tallettaa niiden raakasiirrot listaan
void Asema::annaRaakaSiirrot(std::list<Siirto>& lista)
{
	// Käy kaikki ruudut läpi ja lisää tämänhetkisen siirtovuoroisen pelaajan siirrot listaan.
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (_lauta[i][j] != NULL)
			{
				if (_lauta[i][j]->getVari() == _siirtoVuoro)
				{
					_lauta[i][j]->annaSiirrot(lista, (&Ruutu(i, j)), this, _lauta[i][j]->getVari());
				}
			}
		}
	}
	// Linnoitus siirrot.
	// Linnoitus tarkistus tässä vaiheessa.
	// Antaa vielä linnoitussiirrot jossa kungingas uhattuna sen jälkeen.
	// Nämä siirrot häviää laillisuustarkistuksessa
	if (this->getSiirtovuoro() == 0) {
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaDTliikkunut() == false)
		{
			if (_lauta[7][1] == nullptr && _lauta[7][2] == nullptr &&_lauta[7][3] == nullptr
				&& onkoRuutuUhattuVariINT(7, 1, 1) == false
				&& onkoRuutuUhattuVariINT(7, 2, 1) == false
				&& onkoRuutuUhattuVariINT(7, 3, 1) == false
				)
			{
				lista.push_back(Siirto(false, true)); // Valkoinen pitkälinna
			}
		}
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaKTliikkunut() == false)
		{
			if (_lauta[7][6] == nullptr && _lauta[7][5] == nullptr
				&& onkoRuutuUhattuVariINT(7, 6, 1) == false
				&& onkoRuutuUhattuVariINT(7, 5, 1) == false
				)
			{
				lista.push_back(Siirto(true, false)); // Valkoinen lyhytlinna
			}
		}
	}
	if (this->getSiirtovuoro() == 1) {
		if (this->getOnkoMustaKuningasLiikkunut() == false && this->getOnkoMustaDTliikkunut() == false)
		{
			if (_lauta[0][1] == nullptr && _lauta[0][2] == nullptr &&_lauta[0][3] == nullptr
				&& onkoRuutuUhattuVariINT(0, 1, 0) == false
				&& onkoRuutuUhattuVariINT(0, 2, 0) == false
				&& onkoRuutuUhattuVariINT(0, 3, 0) == false
				)
			{
				lista.push_back(Siirto(false, true)); // Musta pitkälinna
			}
		}
		if (this->getOnkoMustaKuningasLiikkunut() == false && this->getOnkoMustaKTliikkunut() == false)
		{
			if (_lauta[0][6] == nullptr && _lauta[0][5] == nullptr
				&& onkoRuutuUhattuVariINT(0, 6, 0) == false
				&& onkoRuutuUhattuVariINT(0, 6, 0) == false
				)
			{
				lista.push_back(Siirto(true, false)); //Musta pitkälinna
			}
		}
	}
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	std::list<Siirto> tempLista;
	annaRaakaSiirrot(tempLista);
	for (auto siirto : tempLista)
	{
		Asema tempAsema;
		tempAsema = *this;
		tempAsema.paivitaAsema(&siirto);
		Ruutu kuningasRuutu = tempAsema.etsiKuningas(_siirtoVuoro);
		Ruutu* kRptr = &kuningasRuutu;
		if (!tempAsema.onkoRuutuUhattuVari(kRptr, tempAsema.getSiirtovuoro()))
		{
			lista.push_back(siirto);
		}
	}
}



// Etsii kuninkaan värin mukaan
Ruutu Asema::etsiKuningas(int vari)		// valkea = 0, musta = 1
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_lauta[i][j] != nullptr)
			{
				if (vari == 0)
				{
					if (_lauta[i][j]->getKoodi() == VK) return Ruutu(i, j);
				}
				else
				{
					if (_lauta[i][j]->getKoodi() == MK) return Ruutu(i, j);
				}
			}
		}
	}
}

// Käy annetun siirtolistan läpi tarkistamalla uhkaako mikään siirto ruutua
bool Asema::onkoRuutuUhattuLista(Ruutu ruutu, std::list<Siirto>& siirrot)
{
	for (auto s : siirrot)
	{
		if (s.getLoppuruutu() == ruutu)
		{
			return true;
		}
	}
	return false;
}

bool Asema::onkoRuutuUhattuVari(Ruutu* ruutu, int vastustajanVari)
{
	{
		std::list<Siirto> vastustajaSiirrotLista;
		//Väreittäin käydään läpi kaikki ruudut ja niissä olevan nappulan siirrot kerätään vastustajan siirtolistaan
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL) {
					continue;
				}
				if (this->_lauta[i][j]->getVari() == vastustajanVari)
					this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), this, vastustajanVari); // myöh.sidonta
			}
		}
		// Käydään vastustajaSiirtoLista läpi ja jos sieltä löytyy tarkasteltava ruutu niin tiedetään sen olevan uhattu
		for (auto s : vastustajaSiirrotLista)
		{
			if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi()) {
				return true;
			}
		}
		return false;
	}
}

bool Asema::onkoRuutuUhattuVariINT(int rivi, int sarake, int vastustajanVari)
{
	std::list<Siirto> vastustajaSiirrotLista;
	//Väreittäin käydään läpi kaikki ruudut ja niissä olevan nappulan siirrot kerätään vastustajan siirtolistaan
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(rivi, sarake), this, vastustajanVari); // myöh.sidonta
		}
	}
	// Käydään vastustajaSiirtoLista läpi ja jos sieltä löytyy tarkasteltava ruutu niin tiedetään sen olevan uhattu
	for (auto s : vastustajaSiirrotLista)
	{
		if (sarake == s.getLoppuruutu().getSarake() && rivi == s.getLoppuruutu().getRivi()) {
			return true;
		}
	}
	return false;
}



double Asema::evaluoi()
{
	const double materiaaliKerroin = 2.0;
	const double linjaKerroin = 0.2;
	const double ratsuliikkuvuusKerroin = 0.2;
	const double lahettiKerroin = 0.2;

	//double materiaali = laskeNappuloidenArvo(0) - laskeNappuloidenArvo(1);
	//return (materiaaliKerroin * materiaali);

	if (_tekoAlyVari == 0)
	{
		double materiaali = laskeNappuloidenArvo(0) - laskeNappuloidenArvo(1);
		double linja = laskeLinjaArvo(0) - laskeLinjaArvo(1);
		double liikkuvuus = laskeRatsuLiikkuvuusArvo(0) - laskeRatsuLiikkuvuusArvo(1);
		double lahettiPariArvo = lahettiPari(0) - lahettiPari(1);
		return materiaaliKerroin * materiaali + linja * linjaKerroin + liikkuvuus * ratsuliikkuvuusKerroin + lahettiPariArvo * lahettiKerroin;
	}
	if (_tekoAlyVari == 1)
	{
		double materiaali = laskeNappuloidenArvo(1) - laskeNappuloidenArvo(0);
		double linja = laskeLinjaArvo(1) - laskeLinjaArvo(0);
		double liikkuvuus = laskeRatsuLiikkuvuusArvo(1) - laskeRatsuLiikkuvuusArvo(0);
		double lahettiPariArvo = lahettiPari(1) - lahettiPari(0);
		return materiaaliKerroin * materiaali + linja * linjaKerroin + liikkuvuus * ratsuliikkuvuusKerroin + lahettiPariArvo * lahettiKerroin;
	}
}


double Asema::lahettiPari(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;
	int valkLahetticount = 0;
	int mustaLahetticount = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] != nullptr) {
				int nappulanNimi = this->_lauta[i][j]->getKoodi();
				if (nappulanNimi == VL)
				{
					valkLahetticount++;
				}
				if (nappulanNimi == ML)
				{
					mustaLahetticount++;
				}
			}
		}
	}
	if (valkLahetticount == 2) valkeaArvo++;
	if (mustaLahetticount == 2) mustaArvo++;
	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}

double Asema::laskeRatsuLiikkuvuusArvo(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] != nullptr) {
				int nappulanNimi = this->_lauta[i][j]->getKoodi();
				if (nappulanNimi == VR) {
					if (j + 1 < 7) valkeaArvo++;
				}
				if (nappulanNimi == MR) {
					if (j - 1 > 0) mustaArvo++;
				}
			}
		}
	}

	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}

double Asema::laskeLinjaArvo(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] != nullptr) {
				int nappulanNimi = this->_lauta[i][j]->getKoodi();
				if (nappulanNimi == VT) {
					for (int delta = 1; delta <= 7; delta++)
					{
						int delta_rivi = i - delta;
						if (delta_rivi < 0)
						{
							valkeaArvo = valkeaArvo + 1;
							break;
						}
						if (this->_lauta[delta_rivi][j] == nullptr)
						{
							continue;
						}
						if (this->_lauta[delta_rivi][j] != nullptr)
						{
							if (this->_lauta[delta_rivi][j]->getVari() != vari) valkeaArvo = valkeaArvo + 2;
							break;

						}
					}
				}
				if (nappulanNimi == MT) {
					for (int delta = 1; delta <= 7; delta++)
					{
						int delta_rivi = i + delta;
						if (delta_rivi > 7)
						{
							mustaArvo = mustaArvo + 1;
							break;
						}
						if (this->_lauta[delta_rivi][j] == nullptr)
						{
							continue;
						}
						if (this->_lauta[delta_rivi][j] != nullptr)
						{
							if (this->_lauta[delta_rivi][j]->getVari() != vari) mustaArvo = mustaArvo + 2;
							break;
						}
					}
				}
			}
		}
	}
	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}


double Asema::laskeNappuloidenArvo(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] != nullptr) {
				int nappulanNimi = this->_lauta[i][j]->getKoodi();
				//Valkoiset
				if (nappulanNimi == VD)
					valkeaArvo += 15; // 9
				if (nappulanNimi == VT)
					valkeaArvo += 5;
				if (nappulanNimi == VL)
					valkeaArvo += 3.25;
				if (nappulanNimi == VR)
					valkeaArvo += 3;
				if (nappulanNimi == VS)
					valkeaArvo += 1;
				//Mustat
				if (nappulanNimi == MD)
					mustaArvo += 15;
				if (nappulanNimi == MT)
					mustaArvo += 5;
				if (nappulanNimi == ML)
					mustaArvo += 3.25;
				if (nappulanNimi == MR)
					mustaArvo += 3;
				if (nappulanNimi == MS)
					mustaArvo += 1;
			}
		}
	}
	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}

double Asema::lopputulos()
{
	// Asemassa ei ole enää laillisia siirtoja. Etsitään siirtovuoroisen pelaajan
	// kuningas; jos kuningas on uhattu, on pelaaja hävinnyt (muuten tasapeli, "patti").

	// Kuninkaan sijainti (x,y).

	if (onkoRuutuUhattuVari(&etsiKuningas(_siirtoVuoro), _siirtoVuoro == 0 ? 1 : 0))
		return 0; // tasapeli (patti)
	else
		return _siirtoVuoro == 0 ? -1000000 : 1000000;	// matti
}

MinMax Asema::minmax(int syvyys)
{
	MinMax paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu koska laillisia siirtoja ei ole.
	if (siirrot.size() == 0)
	{
		paluuarvo._evaluointiArvo = lopputulos();
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydessä
	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	paluuarvo._evaluointiArvo = (_siirtoVuoro == 0 ? -1000000 : 1000000);
	for (auto s : siirrot)
	{
		// Seuraaja-asema (tehdään nykyisessä asemassa siirto s).
		Asema* uusi_asema = new Asema;
		*uusi_asema = *this;
		uusi_asema->paivitaAsema(&s);

		// Rekursiivinen kutsu.
		MinMax arvo = uusi_asema->minmax(syvyys - 1);
		delete uusi_asema;
		// Tutkitaan ollaan löydetty uusi paras siirto.
		if
			(
			(_siirtoVuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo) ||
				(_siirtoVuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo)
				)
		{
			// Löydettiin uusi paras siirto.
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = s;
		}
	}
	return paluuarvo;
}

MinMax Asema::alphabeta(int syvyys,bool maximizingPlayer, double alpha, double beta)
{
	MinMax paluuarvo;
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	if (siirrot.size() == 0)
	{
		paluuarvo._evaluointiArvo = lopputulos();
		return paluuarvo;
	}
	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (maximizingPlayer) {
		paluuarvo._evaluointiArvo = -1000000;
		for (auto s : siirrot)
		{
			Asema* uusi_asema = new Asema;
			*uusi_asema = *this;
			uusi_asema->paivitaAsema(&s);
			MinMax arvo = uusi_asema->alphabeta(syvyys - 1,false, alpha, beta);
			delete uusi_asema;
			if (arvo._evaluointiArvo >= beta)
			{
				paluuarvo._evaluointiArvo = beta;
				paluuarvo._parasSiirto = s;
				return paluuarvo;
			}

			if (arvo._evaluointiArvo > alpha)
			{
				alpha = arvo._evaluointiArvo;
				paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
				paluuarvo._parasSiirto = s;
			}
		}
		return paluuarvo;
	}
	else {
		paluuarvo._evaluointiArvo = 1000000;
		for (auto s : siirrot)
		{
			Asema* uusi_asema = new Asema;
			*uusi_asema = *this;
			uusi_asema->paivitaAsema(&s);
			MinMax arvo = uusi_asema->alphabeta(syvyys - 1,true, alpha, beta);
			delete uusi_asema;
			if (arvo._evaluointiArvo <= alpha)
			{
				paluuarvo._evaluointiArvo = alpha;
				paluuarvo._parasSiirto = s;
				return paluuarvo;
			}
			if (arvo._evaluointiArvo < beta)
			{
				alpha = arvo._evaluointiArvo;
				paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
				paluuarvo._parasSiirto = s;
			}
		}
		return paluuarvo;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}

bool Asema::getOnkoMustaKuningasLiikkunut()
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

void Asema::setTekoAlyVari(int vari)
{
	_tekoAlyVari = vari;
}

void Asema::addCurrentToUndo()
{
	_undoAsema = new Asema;
	*_undoAsema = *this;


}

void Asema::Undo()
{
	*this = *_undoAsema;

}