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




int main()
{

	
	_setmode(_fileno(stdout), 0x00020000);
	Asema* asema = new Asema();
	Kayttoliittyma kayttoliittyma = Kayttoliittyma(asema);
	//wcout << kayttoliittyma._asema->_lauta[1][1]->getUnicode();
	kayttoliittyma.piirraLauta();
	return 0;
}