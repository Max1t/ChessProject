#pragma once

#include <list>
#include <string>
#include "Asema.h"
#include "Ruutu.h"
#include "Siirto.h"
#include "Ohestalyönti.h"


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
			if (tempNappula == nullptr)																// Jos ruutu on tyhjä siihen voi laillisesti siirtää
			{
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_w, sarake)));
				continue;
			}
			if (tempNappula->getVari() != vari)														// Jos ruudussa on nappula testataan jos se on vihollisen nappula
			{																					// Jos nappula on vihollisen siihen voi laillisesti siirtää ja siirrytään pois loopista
				lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(delta_rivi_w, sarake)));
			}
			break;																				// Safety break
		}
		// Ruudut yläpuolelta
		for (int delta_e = 1; delta_e <= 7; delta_e++)											// Muut loopit toimii samalla tavalla muutetaan vain eri parametriä
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
		int rivi_delta;
		int sarake_delta;
		Nappula* tempNappula;

		if (asema->getSiirtovuoro() == 0)
		{
			rivi_delta = rivi - 1;
			sarake_delta = sarake;
			if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0)) {
				tempNappula = asema->_lauta[rivi_delta][sarake_delta];
				if (tempNappula == nullptr)
				{
					lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
				}
			}
			if (asema->getSiirtovuoro() == 0 && rivi == 6)
			{
				rivi_delta = rivi - 2;
				sarake_delta = sarake;
				if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0)) {
					tempNappula = asema->_lauta[rivi_delta][sarake_delta];
					if (tempNappula == nullptr)
					{
						lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
					}
				}
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
				if (asema->_ohestalyönti.onkoOhestaMahdollinen() == true)
				{
					if (
						rivi_delta == asema->_ohestalyönti.getLyöntiRivi() &&
						sarake_delta == asema->_ohestalyönti.getLyöntiSarake()
						)
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
				if (asema->_ohestalyönti.onkoOhestaMahdollinen() == true)
				{
					if (
						rivi_delta == asema->_ohestalyönti.getLyöntiRivi() &&
						sarake_delta == asema->_ohestalyönti.getLyöntiSarake()
						)
					{
						lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
					}
				}
			}
		}

		if (asema->getSiirtovuoro() == 1)
		{
			rivi_delta = rivi + 1;
			sarake_delta = sarake;
			if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0)) {
				tempNappula = asema->_lauta[rivi_delta][sarake_delta];
				if (tempNappula == nullptr)
				{
					lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
				}
			}
			if (asema->getSiirtovuoro() == 1 && rivi == 1)
			{
				rivi_delta = rivi + 2;
				sarake_delta = sarake;
				if (!(rivi_delta > 7 || rivi_delta < 0 || sarake_delta > 7 || sarake_delta < 0)) {
					tempNappula = asema->_lauta[rivi_delta][sarake_delta];
					if (tempNappula == nullptr)
					{
						lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
					}
				}
			}

			rivi_delta = rivi + 1;
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
				if (asema->_ohestalyönti.onkoOhestaMahdollinen() == true)
				{
					if (
						rivi_delta == asema->_ohestalyönti.getLyöntiRivi() &&
						sarake_delta == asema->_ohestalyönti.getLyöntiSarake()
						)
					{
						lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
					}
				}
			}

			rivi_delta = rivi + 1;
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
				if (asema->_ohestalyönti.onkoOhestaMahdollinen() == true)
				{
					if (
						rivi_delta == asema->_ohestalyönti.getLyöntiRivi() &&
						sarake_delta == asema->_ohestalyönti.getLyöntiSarake()
						)
					{
						lista.push_back(Siirto(Ruutu(rivi, sarake), Ruutu(rivi_delta, sarake_delta)));
					}
				}
			}

		}

	}
};

class Lähetti : virtual public Nappula
{
public:
	Lähetti(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari) {}
	virtual void annaSiirrot(
		std::list<Siirto>& lista,
		Ruutu* ruutu,
		Asema* asema,
		int vari
	)
	{
		// Nykyiset koordinaatit
		int y = ruutu->getSarake();
		int x = ruutu->getRivi();

		// "oikealle ylös"
		for (int dx = 1; dx <= 7; dx++)
		{
			// uudet koordinatit
			int new_x = x - dx;
			int new_y = y + dx;
			// mennäänkö yli laudan reunasta?
			if (new_x < 0 || new_y > 7) break;
			// mitä tutkittavassa ruudussa on?
			Nappula* n = asema->_lauta[new_x][new_y];
			// onko tyhjä ruutu?
			if (n == nullptr)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
				continue;
			}
			// onko vastustajan nappula?
			if (n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
			break;
		}

		// vasemmalle ylös
		for (int dx = 1; dx <= 7; dx++)
		{
			// uudet koordinatit
			int new_x = x - dx;
			int new_y = y - dx;

			if (new_x < 0 || new_y < 0) break;

			// mitä tutkittavassa ruudussa on?
			Nappula* n = asema->_lauta[new_x][new_y];
			// onko tyhjä ruutu?
			if (n == nullptr)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
				continue;
			}
			// onko vastustajan nappula?
			if (n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
			break;
		}

		// vasemmalle alas
		for (int dx = 1; dx <= 7; dx++)
		{
			// uudet koordinatit
			int new_x = x + dx;
			int new_y = y - dx;

			// mennäänkö yli laudan reunasta?
			if (new_x > 7 || new_y < 0) break;

			// mitä tutkittavassa ruudussa on?
			Nappula* n = asema->_lauta[new_x][new_y];
			// onko tyhjä ruutu?
			if (n == nullptr)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
				continue;
			}
			// onko vastustajan nappula?
			if (n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
			break;
		}

		// oikealle alas
		for (int dx = 1; dx <= 7; dx++)
		{
			// uudet koordinatit
			int new_x = x + dx;
			int new_y = y + dx;

			// mennäänkö yli laudan reunasta?
			if (new_x > 7 || new_y > 7) break;

			// mitä tutkittavassa ruudussa on?
			Nappula* n = asema->_lauta[new_x][new_y];
			// onko tyhjä ruutu?
			if (n == nullptr)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
				continue;
			}
			// onko vastustajan nappula?
			if (n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
			break;
		}
	}
};

class Kuningatar : public virtual Torni, public virtual Lähetti {
public:
	Kuningatar(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari), Lähetti(unicode, koodi, vari), Torni(unicode, koodi, vari) {}
	virtual void annaSiirrot(
		std::list<Siirto>& lista,
		Ruutu* ruutu,
		Asema* asema,
		int vari
	)
	{
		Torni::annaSiirrot(lista, ruutu, asema, vari);
		Lähetti::annaSiirrot(lista, ruutu, asema, vari);
	}
};

class Kuningas : virtual public Nappula
{
public:
	Kuningas(std::wstring unicode, int koodi, int vari) : Nappula(unicode, koodi, vari) {}
	virtual void annaSiirrot(
		std::list<Siirto>& lista,
		Ruutu* ruutu,
		Asema* asema,
		int vari
	)
	{

		// Nykyiset koordinaatit
		int y = ruutu->getSarake();
		int x = ruutu->getRivi();

		// "oikealle" 
		int new_x = x + 1;
		int new_y = y;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
		}



		// oik alas
		new_x = x + 1;
		new_y = y + 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
		}


		// alas
		new_x = x;
		new_y = y + 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}

		}
		// vas alas
		new_x = x - 1;
		new_y = y + 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}

		}

		// vasemmalle
		new_x = x - 1;
		new_y = y;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
		}

		// vas ylös
		new_x = x - 1;
		new_y = y - 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
		}

		// ylös
		new_x = x;
		new_y = y - 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}

			
		}

		// oik ylös
		new_x = x + 1;
		new_y = y - 1;
		if (!(new_x > 7 || new_x < 0 || new_y > 7 || new_y < 0))
		{
			Nappula* n = asema->_lauta[new_x][new_y];
			if (n == nullptr || n->getVari() != vari)
			{
				lista.push_back(Siirto(Ruutu(x, y), Ruutu(new_x, new_y)));
			}
		}

	}
};