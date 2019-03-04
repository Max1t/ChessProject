#pragma once
#include"stdafx.h"
#include <string>
#include "Siirto.h"
#include "Ruutu.h"
#include <iostream>
#include <io.h>
#include <windows.h>
#include"Nappula.h"
using namespace std;


class Kayttoliittyma {

public:
	Asema * _asema;
	Kayttoliittyma(Asema* asema)
	{
		_asema = asema;
	}
	void piirraLauta();
	Siirto* annaSiirto();

};