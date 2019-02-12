// cppProject.cpp : Defines the entry point for the console application.
//

#include"stdafx.h"
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
		Siirto* siirto = kayttoliittyma.annaVastustajanSiirto();
		asema->paivitaAsema(siirto);
		kayttoliittyma.piirraLauta();
		asema->annaLaillisetSiirrot(Siirtolista);
		asema->printLaillisetSiirrot(Siirtolista);
	}
	
	return 0;
}