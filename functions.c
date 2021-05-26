
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void provjeraDatoteke(char* file, unsigned int* pBrojKlijenata) {
	system ("cls");
	
	FILE* fp = fopen(file, "rb");

	if (fp == NULL) {

		perror("Datoteka ne postoji\n");

		fp = fopen(file, "wb");

		if (fp == NULL) {

			perror("Datoteka se ne moze kreirati");
			exit(EXIT_FAILURE);
		}
		else {

			fwrite(pBrojKlijenata, sizeof(unsigned int), 1, fp);
			fclose(fp);
			printf("Datoteka kreirana\n");
		}
	}
	else {

		fread(pBrojKlijenata, sizeof(unsigned int), 1, fp);
		fclose(fp);

	}
}

void dodavanjeKlijenata(char* file, unsigned int* pBrojKlijenata){

   FILE* fp = NULL;
	
	fp = fopen(file, "rb+");

	if (fp == NULL) {
		perror("Dodavanje novog klijenta");
		return;
		
	}
	else {

		KLIJENTI pKlijent = { 0 };
		printf("Unesite ime klijenta\n");
		scanf("%25s", pKlijent.ime);
		printf("Unesite prezime klijenta\n");
		scanf("%25s", pKlijent.prezime);
		printf("Unesite broj mobitela klijenta\n");
		scanf(" %20s", pKlijent.brojMobitela);
		printf("Unesite email klijenta\n");
		scanf("%25s", pKlijent.email);
		
		pKlijent.id = (*pBrojDevelopera)++;

		fseek(fp, sizeof(unsigned int) + ((*pBrojKlijenata - 1) * sizeof(KLIJENTI)), SEEK_SET);
		fwrite(&pKlijent, sizeof(KLIJENTI), 1, fp);
		rewind(fp);
		fwrite(pBrojKlijenata, sizeof(unsigned int), 1, fp);
		fclose(fp);
	}
}
void ispisKlijenata(char* file, unsigned int* pBrojKlijenata) {

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
void search(char* file, unsigned int* pBrojKlijenata) {

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
