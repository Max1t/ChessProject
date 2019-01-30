#pragma once

#include"stdafx.h"
#include <string>
#include "Nappula.h" 
#include "Siirto.h"
using namespace std;



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