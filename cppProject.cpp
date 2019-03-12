#include "stdafx.h"
#include "Nappula.h"
#include "Asema.h"
#include<string>
#include<iostream>
#include<io.h>
#include"Kayttoliittyma.h"
#include <windows.h>
#include <algorithm>
using namespace std;


int main()
{
	std::list<Siirto> Siirtolista;
	_setmode(_fileno(stdout), 0x00020000);
	Asema* asema = new Asema();
	Kayttoliittyma kayttoliittyma = Kayttoliittyma(asema);
	// Vari kelle tekoäly miettii siirtoja 0 = valk, 1 = musta
	asema->setTekoAlyVari(0);
	Siirto* siirto;
	//-------------------------------------------
	// Valkoinen AI
	while (1) {

		/* Testejä
		wcout << "Valkoinen Kuningas Ruutu index: " << asema->etsiKuningas(0).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(0).getSarake() << endl;
		wcout << "Musta Kuningas Ruutu index: " << asema->etsiKuningas(1).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(1).getSarake() << endl;
		wcout << "Ohestalyönti: " << asema->_ohestalyönti.onkoOhestaMahdollinen() << asema->_ohestalyönti.getLyöntiRivi() << asema->_ohestalyönti.getLyöntiSarake();
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		*/

		kayttoliittyma.piirraLauta();

		asema->addCurrentToUndo();

		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		/*           Ai															*/
		//MinMax ai_valinta = asema->minmax(2);									//
		MinMax ai_valinta = asema->alphabeta(3, true, -1000000, 1000000);		//
		wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";		//
		Siirto ai_siirto = ai_valinta._parasSiirto;								//
		ai_siirto.printSiirto();												//
		while (true) {
			siirto = kayttoliittyma.annaSiirto();
			if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
			else { wcout << "Laiton siirto, yritä uudelleen" << endl; }
		}
		asema->paivitaAsema(siirto);
		/*                                                                      */
		kayttoliittyma.piirraLauta();

		wcout << std::wstring(50, '\n'); // Clear screen
		kayttoliittyma.piirraLauta();//
		Siirtolista.clear();

		// Vastustajan siirto.
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);

		while (true) {
			siirto = kayttoliittyma.annaSiirto();
			if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
			else { wcout << "Laiton siirto, yritä uudelleen" << endl; }
		}
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();
		Siirtolista.clear();

		wcout << std::wstring(50, '\n'); // Clear screen
	}



	/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	// Musta AI
	while (0) {

		asema->addCurrentToUndo();

		kayttoliittyma.piirraLauta();
		// Vastustajan siirto. Jos ai pelaa mustalla laita loopin alkuun!
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);

		while (true) {
			siirto = kayttoliittyma.annaSiirto();
			if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
			else { wcout << "Laiton siirto, yritä uudelleen" << endl; }
		}
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();
		Siirtolista.clear();

		/*
		//-------------------------------------------------------------------------
		// Undo
		while (true)
		{
			wcout << "Undo? y/n ";
			std::wstring vastaus;
			wcin >> vastaus;
			if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
			{
				asema->Undo();
				break;
			}
			else break;
		}
		//-------------------------------------------------------------------------
		*/

		wcout << std::wstring(50, '\n'); // Clear screen



		kayttoliittyma.piirraLauta();
		asema->addCurrentToUndo();

		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		/*           Ai                                                         */
		MinMax ai_valinta = asema->alphabeta(4, true, -1000000, 1000000);									//
		wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";		//
		Siirto ai_siirto = ai_valinta._parasSiirto;								//
		ai_siirto.printSiirto();
		while (true) {
			siirto = kayttoliittyma.annaSiirto();
			if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
			else { wcout << "Laiton siirto, yritä uudelleen" << endl; }
		}//
		asema->paivitaAsema(siirto);

		kayttoliittyma.piirraLauta();//
		Siirtolista.clear();
		/*                                                                      */
		/*
		//-------------------------------------------------------------------------
		// Undo
		while (true)
		{
			wcout << "Undo? y/n ";
			std::wstring vastaus;
			wcin >> vastaus;
			if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
			{
				asema->Undo();
				break;
			}
			else break;
		}
		*/
		//-------------------------------------------------------------------------
		wcout << std::wstring(50, '\n'); // Clear screen
	}

	// Tekoäly vs tekoäly //////////////////////////////////////////////////////////////////////////////////////////////////////
	while (0) {



		asema->setTekoAlyVari(1);

		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		/*           Ai                                                         */
		MinMax ai_valinta2 = asema->minmax(2);									//
		wcout << "Minimax-arvo: " << ai_valinta2._evaluointiArvo << "\n";		//
		Siirto ai_siirto2 = ai_valinta2._parasSiirto;								//
		ai_siirto2.printSiirto();
		wcout << asema->getSiirtovuoro() << endl;
		std::wstring lol;
		wcin >> lol;
		asema->paivitaAsema(&ai_siirto2);

		kayttoliittyma.piirraLauta();//
		Siirtolista.clear();


		asema->setTekoAlyVari(0);
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		/*           Ai															*/
		//MinMax ai_valinta = asema->minmax(2);									//
		MinMax ai_valinta = asema->alphabeta(4, true, -1000000, 1000000);		//
		wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";		//
		Siirto ai_siirto = ai_valinta._parasSiirto;								//
		ai_siirto.printSiirto();
		wcout << asema->getSiirtovuoro() << endl;

		wcin >> lol;
		asema->paivitaAsema(&ai_siirto);
		/*                                                                      */
		kayttoliittyma.piirraLauta();

		Siirtolista.clear();
	}
	return 0;
}



