#pragma once
#include"stdafx.h"
#include <string>
#include "Asema.h"
#include<iostream>
#include<io.h>
#include <windows.h>
using namespace std;


class Kayttoliittyma {

public:
	Asema * _asema;
	Kayttoliittyma(Asema* asema)
	{
		_asema = asema;
	}
	void piirraLauta();
};