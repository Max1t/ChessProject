#pragma once

#include <list>
#include <string>
#include "Asema.h"
#include "Ruutu.h"
#include "Siirto.h"


// Vakioarvot nappulatyypeille.
enum
{
	VT, VR, VL, VD, VK, VS,
	MT, MR, ML, MD, MK, MS
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms.

public:
	Nappula(std::wstring code, int koodi, int vari)
	{
		setUnicode(code);
		setKoodi(koodi);
		setVari(vari);
	}
	Nappula() {}


	virtual void annaSiirrot(
		std::list<Siirto>& lista,
		Ruutu* ruutu,
		Asema* asema,
		int vari
	) = 0;

	void setUnicode(std::wstring unicode) { _unicode = unicode; }
	std::wstring getUnicode() { return _unicode; }
	void setVari(int vari) { _vari = vari; }
	// Palauttaa nappulan puolen, valkea = 0, musta = 1
	int getVari() { return _vari; }
	int getKoodi() { return _koodi; }
	void setKoodi(int koodi) { _koodi = koodi; }
};


class Torni : virtual public Nappula
{
public:
	Torni(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari) {}
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		// Nappulan koordinaatit laudalla
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();

		// Testataan ruudut nappulan alapuolelta
		for (int delta_w = 1; delta_w <= 7; delta_w++)
		{
			int delta_rivi_w = rivi + delta_w;													// Seuraavan ruudun x koordinaatti
			if (delta_rivi_w > 7) break;														// Pois loopista kun menee yli laidan
			Nappula* tempNappula = asema->_lauta[delta_rivi_w][sarake];								// Tutkittavan ruudun koordinaatit
			if (tempNappula == nullptr)																// Jos ruutu on tyhj‰ siihen voi laillisesti siirt‰‰
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_w, sarake)));
				continue;
			}
			if (tempNappula->getVari() != vari)														// Jos ruudussa on nappula testataan jos se on vihollisen nappula
			{																					// Jos nappula on vihollisen siihen voi laillisesti siirt‰‰ ja siirryt‰‰n pois loopista
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_w, sarake)));
			}
			break;																				// Safety break
		}
		// Ruudut yl‰puolelta
		for (int delta_e = 1; delta_e <= 7; delta_e++)											// Muut loopit toimii samalla tavalla muutetaan vain eri parametri‰
		{
			int delta_rivi_e = rivi - delta_e;
			if (delta_rivi_e < 0) break;
			Nappula* tempNappula = asema->_lauta[delta_rivi_e][sarake];
			if (tempNappula == nullptr)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_e, sarake)));
				continue;
			}
			if (tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_e, sarake)));
			}
			break;
		}

		// Ruudut Oikealta puolelta
		for (int delta_n = 1; delta_n <= 7; delta_n++)
		{
			int delta_sarake_n = sarake + delta_n;
			if (delta_sarake_n > 7) break;
			Nappula* tempNappula = asema->_lauta[rivi][delta_sarake_n];
			if (tempNappula == nullptr)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi, delta_sarake_n)));
				continue;
			}
			if (tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi, delta_sarake_n)));
			}
			break;
		}

		// Ruudut Vasemmalta puolelta
		for (int delta_s = 1; delta_s <= 7; delta_s++)
		{
			int delta_sarake_s = sarake - delta_s;
			if (delta_sarake_s < 0) break;
			Nappula* tempNappula = asema->_lauta[rivi][delta_sarake_s];
			if (tempNappula == nullptr)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi, delta_sarake_s)));
				continue;
			}
			if (tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi, delta_sarake_s)));
			}
			break;
		}
	}
};

class Ratsu : virtual public Nappula
{
public:
	Ratsu(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari) {}
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		// Nappulan koordinaatit laudalla
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();
		Nappula* tempNappula = nullptr;

		int rivi_delta = rivi + 2;
		int sarake_delta = sarake + 1;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}


		rivi_delta = rivi + 2;
		sarake_delta = sarake + -1;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi + 1;
		sarake_delta = sarake + 2;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi + 1;
		sarake_delta = sarake - 2;
		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi - 1;
		sarake_delta = sarake + 2;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi - 1;
		sarake_delta = sarake - 2;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi - 2;
		sarake_delta = sarake - 1;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

		rivi_delta = rivi - 2;
		sarake_delta = sarake + 1;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula == nullptr || tempNappula->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
			}
		}

	}

};

class Sotilas : virtual public Nappula
{
public:
	Sotilas(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari) {}
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		// Nappulan koordinaatit laudalla
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();

		int rivi_delta = rivi - 1;
		int sarake_delta = sarake;

		Nappula* tempNappula = asema->_lauta[rivi_delta][sarake_delta];
		if (tempNappula == nullptr)
		{
			lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
		}

		rivi_delta = rivi - 1;
		sarake_delta = sarake + 1;
		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula != nullptr) {
				if (tempNappula->getVari() != vari)
				{
					lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
				}
			}
		}

		rivi_delta = rivi - 1;
		sarake_delta = sarake - 1;

		if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0))
		{
			tempNappula = asema->_lauta[rivi_delta][sarake_delta];
			if (tempNappula != nullptr) {
				if (tempNappula->getVari() != vari)
				{
					lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
				}
			}
		}
	}
};