#pragma once

#include"stdafx.h"
#include <string>
#include "Siirto.h"
#include <list>    
using namespace std;

class Nappula;

class Asema
{
public:
	Asema();
	Nappula* _lauta[8][8];
	void paivitaAsema(Siirto* siirto);
	int getSiirtovuoro();
	void setSiirtovuoro(int vari);
	bool getOnkoValkeaKuningasLiikkunut();
	bool getOnkoMustaKuningasLiikunut();
	bool getOnkoValkeaDTliikkunut();
	bool getOnkoValkeaKTliikkunut();
	bool getOnkoMustaDTliikkunut();
	bool getOnkoMustaKTliikkunut();
	void annaLaillisetSiirrot(std::list<Siirto>& lista);
	void printLaillisetSiirrot(std::list<Siirto>& lista);

private:
	// Siirtovuoro 1 = musta, 0 = valkoinen
	int _siirtoVuoro = 0;
	bool _onkoValkeaKuningasLiikkunut;
	bool _onkoMustaKuningasLiikkunut;
	bool _onkoValkeaDTliikkunut;
	bool _onkoValkeaKTliikkunut;
	bool _onkoMustaDTliikkunut;
	bool _onkoMustaKTliikkunut;
};