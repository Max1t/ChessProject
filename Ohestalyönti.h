#pragma once

class Ohestalyönti
{
public:
	int getLyöntiRivi() { return _lyöntiRivi; }
	int getLyöntiSarake() { return _lyöntiSarake; }
	int getKohdeRivi() { return _kohdeRivi; }
	int getKohdeSarake() { return _kohdeSarake; }
	bool onkoOhestaMahdollinen() { return _onkoOhestaMahdollinen; }

	void setLyöntiRivi(int arvo) { _lyöntiRivi = arvo; }
	void setLyöntiSarake(int arvo) { _lyöntiSarake = arvo; }
	void setKohdeRivi(int arvo) { _kohdeRivi = arvo; }
	void setKohdeSarake(int arvo) { _kohdeSarake = arvo; }
	void setOnkoOhestaMahdollinen(bool arvo) { _onkoOhestaMahdollinen = arvo; }

private:
	int _lyöntiRivi = 0; // Ruudun rivi jonka voi ohestalyödä
	int _lyöntiSarake = 0; // Ruudun sarake jonka voi ohestalyödä
	int _kohdeRivi = 0; // Kohde ruudun rivi jossa on poistettava sotilas
	int _kohdeSarake = 0; // Kohde ruudun sarake jossa on poistettava sotilas
	bool _onkoOhestaMahdollinen = false; // Onko ohestalyönti mahdollista tällä hetkellä
};