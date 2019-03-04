#include "stdafx.h"
#include "Nappula.h"
#include "Asema.h"
#include<string>
#include<iostream>
#include<io.h>
#include"Kayttoliittyma.h"
#include <windows.h>
using namespace std;


/*
Siirtovuoro ei vaihdu tällä hetkellä!


*/

int main()
{
	std::list<Siirto> Siirtolista;
	_setmode(_fileno(stdout), 0x00020000);
	Asema* asema = new Asema();
	Kayttoliittyma kayttoliittyma = Kayttoliittyma(asema);
	kayttoliittyma.piirraLauta();
	while (true) {
		
		/*Siirto* siirto = kayttoliittyma.annaSiirto();
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();*/

		wcout << "Valkoinen Kuningas Ruutu index: " << asema->etsiKuningas(0).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(0).getSarake() << endl;
		wcout << "Musta Kuningas Ruutu index: " << asema->etsiKuningas(1).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(1).getSarake() << endl;
		wcout << "Ohestalyönti: " << asema->_ohestalyönti.onkoOhestaMahdollinen() << asema->_ohestalyönti.getLyöntiRivi() << asema->_ohestalyönti.getLyöntiSarake();
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);

		/*           Ai                                                         */
		MinMax ai_valinta = asema->minmax(3);									//
		wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";		//
		Siirto ai_siirto = ai_valinta._parasSiirto;								//
		ai_siirto.printSiirto();												//
		/*                                                                      */
		Siirto* siirto = kayttoliittyma.annaSiirto();
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();
		Siirtolista.clear();

		// Vihollisen siirto. Jos pelaa mustalla laita loopin alkuun!
		siirto = kayttoliittyma.annaSiirto();
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();
		
	}
	return 0;
}



