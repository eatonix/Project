#ifndef HEADER_H
#define HEADER_H

typedef struct klijenti {
	int id;
	int broj_klijenata;
	char ime[25];
	char prezime[25];
	char broj_mobitela[20];
}KLIJENTI;

void provjeraDatoteke(char*, unsigned int*);
void dodavanjeKlijenata(char*, unsigned int*);
void ispisKlijenata(char*, unsigned int*);
void izlaz(void);
void brisanjeDatoteke(char* file);
void pretragaPoImenu(char* file, unsigned int* pBrojKlijenata);

#endif HEADER_H

