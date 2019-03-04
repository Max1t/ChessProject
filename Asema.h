#pragma once

#include "stdafx.h"
#include <string>
#include "Siirto.h"
#include "Ohestalyönti.h"
#include <list>   
#include "MinMax.h"

using namespace std;

class Nappula;
class Ohestalyönti;

class Asema
{
public:
	Asema();
	Asema(const Asema &obj);

	double evaluoi();
	double laskeNappuloidenArvo(int vari);
	double laskeLinjaArvo(int vari);
	double laskeSiirrotArvo(int vari);
	double lopputulos();
	MinMax minmax(int syvyys);
	static Nappula *vk, *vd, *vt, *vl, *vr, *vs;	// Valkeat nappulat.
	static Nappula *mk, *md, *mt, *ml, *mr, *ms;	// Mustat nappulat.

	Nappula* _lauta[8][8];
	Ohestalyönti _ohestalyönti; // Seuraa ohestalyönti mahdollisuutta
	void paivitaAsema(Siirto *siirto);
	int getSiirtovuoro();
	void setSiirtovuoro(int vari);
	bool getOnkoValkeaKuningasLiikkunut();
	bool getOnkoMustaKuningasLiikkunut();
	bool getOnkoValkeaDTliikkunut();
	bool getOnkoValkeaKTliikkunut();
	bool getOnkoMustaDTliikkunut();
	bool getOnkoMustaKTliikkunut();
	void annaLaillisetSiirrot(std::list<Siirto>& lista);
	void annaVihollisenLaillisetSiirrot(std::list<Siirto>& lista);
	void annaRaakaSiirrot(std::list<Siirto>& lista);
	void printLaillisetSiirrot(std::list<Siirto>& lista);
	Ruutu etsiKuningas(int vari); // valkea = 0, musta = 1
	bool onkoRuutuUhattuLista(Ruutu ruutu, std::list<Siirto>& siirrot);
	bool onkoRuutuUhattuVari(Ruutu* ruutu, int vari);
	bool onkoRuutuUhattuVariINT(int rivi, int sarake, int vastustajanVari);

private:
	// Siirtovuoro 1 = musta, 0 = valkoinen
	int _siirtoVuoro = 0;
	bool _onkoValkeaKuningasLiikkunut = false;
	bool _onkoMustaKuningasLiikkunut = false;
	bool _onkoValkeaDTliikkunut = false;
	bool _onkoValkeaKTliikkunut = false;
	bool _onkoMustaDTliikkunut = false;
	bool _onkoMustaKTliikkunut = false;
};