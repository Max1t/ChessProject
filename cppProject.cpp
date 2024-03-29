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
	int vastaus;
	std::wcin >> vastaus;
	asema->setTekoAlyVari(vastaus);
	Siirto* siirto;
	//-------------------------------------------
	// Valkoinen AI
	while (!vastaus) {

		/* Testejä
		wcout << "Valkoinen Kuningas Ruutu index: " << asema->etsiKuningas(0).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(0).getSarake() << endl;
		wcout << "Musta Kuningas Ruutu index: " << asema->etsiKuningas(1).getRivi(); // Kuningas etsimis testi
		wcout << asema->etsiKuningas(1).getSarake() << endl;
		wcout << "Ohestalyönti: " << asema->_ohestalyönti.onkoOhestaMahdollinen() << asema->_ohestalyönti.getLyöntiRivi() << asema->_ohestalyönti.getLyöntiSarake();
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
		*/
		while (true) {
			bool undo = false;
			std::wcout << std::wstring(50, '\n'); // Clear screen
			kayttoliittyma.piirraLauta();

			asema->addCurrentToUndo();

			asema->annaLaillisetSiirrot(Siirtolista);
			asema->printLaillisetSiirrot(Siirtolista);
			/*           Ai															*/
																					//
			MinMax ai_valinta = asema->alphabeta(5,true, -1000000, 1000000);		//
			std::wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";	//
			Siirto ai_siirto = ai_valinta._parasSiirto;								//
																					//
			ai_siirto.printSiirto();												//
																					//
																					//
			while (true) {															//
				siirto = kayttoliittyma.annaSiirto();								//
				if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }	//
				else { std::wcout << "Laiton siirto, yritä uudelleen" << endl; }	//
			}																		//
			asema->paivitaAsema(siirto);											//
			/*                                                                      */
			kayttoliittyma.piirraLauta();

			//-------------------------------------------------------------------------
			// Undo
			while (true)
			{
				std::wcout << "Undo? y/n ";
				std::wstring vastaus;
				std::wcin >> vastaus;
				if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
				{
					Siirtolista.clear();
					undo = true;
					asema->Undo();
					break;

				}
				else break;
			}
			//-------------------------------------------------------------------------
			if (undo == false) break;
			else continue;
		}

		while (true) {
			bool undo = false;
			std::wcout << std::wstring(50, '\n'); // Clear screen
			kayttoliittyma.piirraLauta();//
			Siirtolista.clear();
			asema->addCurrentToUndo();
			// Vastustajan siirto.
			asema->annaLaillisetSiirrot(Siirtolista);
			asema->printLaillisetSiirrot(Siirtolista);

			while (true) {
				siirto = kayttoliittyma.annaSiirto();
				if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
				else { std::wcout << "Laiton siirto, yritä uudelleen" << endl; }
			}
			asema->paivitaAsema(siirto);
			kayttoliittyma.piirraLauta();
			Siirtolista.clear();



			//-------------------------------------------------------------------------
			// Undo
			while (true)
			{
				std::wcout << "Undo? y/n ";
				std::wstring vastaus;
				std::wcin >> vastaus;
				if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
				{
					Siirtolista.clear();
					undo = true;
					asema->Undo();
					break;

				}
				else break;
			}
			//-------------------------------------------------------------------------
			if (undo == false) break;
			else continue;
		}
	}





	/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	// Musta AI
	while (vastaus) {

		while (true) {
			bool undo = false;
			std::wcout << std::wstring(50, '\n'); // Clear screen
			kayttoliittyma.piirraLauta();//
			Siirtolista.clear();
			asema->addCurrentToUndo();
			// Vastustajan siirto.
			asema->annaLaillisetSiirrot(Siirtolista);
			asema->printLaillisetSiirrot(Siirtolista);

			while (true) {
				siirto = kayttoliittyma.annaSiirto();
				if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }
				else { std::wcout << "Laiton siirto, yritä uudelleen" << endl; }
			}
			asema->paivitaAsema(siirto);
			kayttoliittyma.piirraLauta();
			Siirtolista.clear();



			//-------------------------------------------------------------------------
			// Undo
			while (true)
			{
				std::wcout << "Undo? y/n ";
				std::wstring vastaus;
				std::wcin >> vastaus;
				if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
				{
					Siirtolista.clear();
					undo = true;
					asema->Undo();
					break;

				}
				else break;
			}
			//-------------------------------------------------------------------------
			if (undo == false) break;
			else continue;
		}

		while (true) {
			bool undo = false;
			std::wcout << std::wstring(50, '\n'); // Clear screen
			kayttoliittyma.piirraLauta();

			asema->addCurrentToUndo();

			asema->annaLaillisetSiirrot(Siirtolista);
			asema->printLaillisetSiirrot(Siirtolista);
			/*           Ai															*/
																					//
			MinMax ai_valinta = asema->alphabeta(4,true, -1000000, 1000000);				//
			std::wcout << "Minimax-arvo: " << ai_valinta._evaluointiArvo << "\n";	//
			Siirto ai_siirto = ai_valinta._parasSiirto;								//
																					//
			ai_siirto.printSiirto();												//
																					//
			while (true) {															//
				siirto = kayttoliittyma.annaSiirto();								//
				if (kayttoliittyma.onkoListassa(*siirto, Siirtolista)) { break; }	//
				else { std::wcout << "Laiton siirto, yritä uudelleen" << endl; }	//
			}																		//
			asema->paivitaAsema(siirto);											//
			/*                                                                      */
			kayttoliittyma.piirraLauta();

			//-------------------------------------------------------------------------
			// Undo
			while (true)
			{
				std::wcout << "Undo? y/n ";
				std::wstring vastaus;
				std::wcin >> vastaus;
				if (vastaus == std::wstring(L"y") || vastaus == std::wstring(L"Y"))
				{
					Siirtolista.clear();
					undo = true;
					asema->Undo();
					break;

				}
				else break;
			}
			//-------------------------------------------------------------------------
			if (undo == false) break;
			else continue;
		}
	}
}