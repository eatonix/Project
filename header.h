
#ifndef HEADER_H
#define HEADER_H

typedef struct klijenti {
	int broj_klijenata;
	char ime[25];
	char prezime[25];
	char broj_mobitela[20];
	char email[25];
}KLIJENTI;

void provjeraDatoteke(char*, unsigned int*);
void dodavanjeKlijenata(char*, unsigned int*);
void ispisKlijenata(char*, unsigned int*);
void search(char*, unsigned int*);

#endif HEADER_H
