#pragma once

#include <list>
#include <string>
#include "Asema.h"
#include "Ruutu.h"
#include "Siirto.h"

class Nappula;

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