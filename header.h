#ifndef HEADER_H
#define HEADER_H


typedef struct klijenti {
	int id;
	int broj_klijenata;
	char ime[25];
	char prezime[25];
	char broj_mobitela[20];
	char datum_placanja[20];
}KLIJENTI;

void provjeraDatoteke(char*, unsigned int*);
void unosKlijenata(char*, unsigned int*);
void ispisKlijenata(char*, unsigned int*);
void izlaz(void);
void brisanjeDatoteke(char* file);
void pretragaPoImenu(char* file, unsigned int* brojKlijenata);
void pretragaPoID(char* file, unsigned int* brojKlijenata);
void izmjenaPodataka(char* file , unsigned int* brojKlijenata);
void sortiranje(char* file, unsigned int* brojKlijenata);

#endif HEADER_H

