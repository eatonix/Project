
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void provjeraDatoteke(void) {
	int podatak = 0;
	FILE* fp = NULL;
	fp = fopen("klijenti.bin", "rb+");
	if (fp == NULL) {
		printf("\nDatoteka ne postoji!\n");
		FILE* fp1 = fopen("klijenti.bin", "wb+");
		if (fp1 == NULL) {
			printf("\n");
			printf("\nDatoteku nije moguce napraviti!\n");
			printf("\n");
		}
		else {
			fwrite(&podatak, sizeof(int), 1, fp1);
			fclose(fp1);
			printf("\nDatoteka uspjesno kreirana.\n\n");
		}
	}
	void unosKlijenta(const char* const imeDatoteke){
		int i;
		FILE* fp = fopen(imeDatoteke, "rb+");
		if (fp == NULL)
			perror("Dodavanje clana (greska)");
			exit(EXIT_FAILURE);
	}

void dodavanjeKlijenata(FILE* fp){

    int i;
	int* x;
	x = (int*)calloc(1, sizeof(int));
	*x = 0;
	int n = 0;
	
	fseek(fp, 0, SEEK_SET);
	fread(&x, sizeof(int), 1, fp);

	printf("Koliko klijenata zelite dodati?");
	scanf("%d", &n);

	KLIJENT* newClients = NULL;
	newClients = (KLIJENT*)calloc(n, sizeof(KLIJENT));

	fseek(fp, 0, SEEK_END);
	

	for(i = 0; i < n; i++){

		printf("%d. klijent:\n", i + 1);
		printf("Ime: ");
		scanf("%s", (newClients + i)->ime);
		printf("Prezime: ");
		scanf("%s", (newClients + i)->prezime);
		(newClients + i)->broj_klijenata = 0;
	}
	*(x) += n;

	fwrite(newClients, sizeof(KLIJENT), n, fp);
	fseek(fp, 0, SEEK_SET);
	fwrite(&x, sizeof(int), 1, fp);
	free(x);
	free(newClients);
	fclose(fp);

	return;
}
void pregledKlijenata(FILE* fp) {

	int n;
	int x = 0;
	
	fread(&x, sizeof(int), 1, fp);
	fclose(fp);

	KLIJENT* klijenti = NULL;
	klijenti = (KLIJENT*)calloc(x, sizeof(KLIJENT));
	if (klijenti == NULL) {
		return NULL;
	}
	else {
		char odabrano[51];

		printf("Zelim:");
		printf("\n 1 sortirati studente A-Z.");
		printf("\n 2 sortirati studente Z-A.");
		printf("\n 3 pronaci odredenog studenta.");
		printf("\n 4 vratiti se na izbornik.");
		printf("\n\nOdaberite broj: ");
		scanf("%d", &n);
		system("cls");
		while (1) {

			switch (n) {

			case 1:
				//sortiranjeAZ(klijenti, x);
				break;

			case 2:
				//sortiranjeZA(ime);
				break;

			case 3:
				search(fp);
				break;

			case 4:
				choice1();
				break;

			default:
				printf("1, 2, 3 ili 4.");
			}
		}
		return;
	}
}
void search(FILE* fp) {

	int num;
	int i;

	if (fp == NULL) {
		perror("Datoteka se ne moze otvoriti");
		return;
	}
	else {
		fseek(fp, 0, SEEK_SET);
		fread(&num, sizeof(int), 1, fp);

		char tempName[51] = { '\0' };

		printf("\n Upisite ime i prezime klijenta: ");
		scanf("%30s", tempName);

		for (i = 0; i < num; i++) {
			fread(&student, sizeof(STUDENT), 1, fp);

			if (strcmp(student.name, tempName) == 0) {
				for (int j = 0; j < klijenti.broj_klijenata; j++) {
					printf("%c ", klijenti.email[j]);
					printf("%d ", broj_mobitela[j]);
				}
			}
		}
	}
}
void izbornik(char* file, unsigned int* pBrojKlijenata){
	
	unsigned int brojKlijenata = 0;
	printf("|******************************************\
                \n             Dobrodosli!                 \
                \n Odaberite opciju koju zelite izvrsiti:  \
                \n(1)Unos novog klijenta\
                \n(2)Pretraga klijenta\
                \n(3)Zavrsetak programa\
                \n******************************************|\n");

	do {
		scanf("%u", &opcija);
		if (opcija < 1 || opcija > 5) {
			printf("Unos je neispravan, molim vas pokusajte ponovo.");
		}
	} while (opcija < 1 || opcija > 5);
	switch (opcija) {
	case 1:
		unosKlijenta(char*, unsigned int*);
		break;
	}
	case 2:
		pregledKlijenata(char*, unsigned int*);
		break;
	default:
		printf("Krivi odabir!\n");
		
}
