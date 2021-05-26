
#ifndef HEADER_H
#define HEADER_H

typedef struct klijenti {
	int broj_klijenata;
	char ime[51];
	char broj_mobitela[20];
	char email[50];
}KLIJENTI;

void stvaranjeDatoteke(void);
void dodavanjeKlijenata(char*, unsigned int*);
void pregledKlijenata(char*, unsigned int*));
void search(char*, unsigned int*);

#endif
