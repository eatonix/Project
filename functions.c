#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "Header.h"

void provjeraDatoteke(char* file, unsigned int* pBrojKlijenata) {

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
		printf("\nDatoteka postoji");
		fclose(fp);
	}
}

void dodavanjeKlijenata(char* file, unsigned int* pBrojKlijenata) {

	FILE* unosUDatoteku = NULL;
	unosUDatoteku = fopen(file, "rb+");

	if (unosUDatoteku == NULL) {
		perror("Greska dodavanja novog clana u datoteku\n");
		return;
	}
	else {
		KLIJENTI unosKlijenta = { 0 };
		printf("\n\n   ================================================\n\n");
		printf("          Unos novih korisnickih racuna\n");
		printf("\n   ================================================\n\n");
		printf("          Unesite podatke o korisniku:\n\n");
		printf("          Ime: ");
		scanf("%25s", unosKlijenta.ime);
		printf("          Prezime: ");
		scanf("%25s", unosKlijenta.prezime);
		printf("          Broj mobitela: ");
		char privremeniBroj[10] = { '\0' };
		scanf("%9s", privremeniBroj);
		strcpy(unosKlijenta.broj_mobitela, "+385");
		strcat(unosKlijenta.broj_mobitela, privremeniBroj);

		fseek(unosUDatoteku, sizeof(unsigned int) + ((*pBrojKlijenata - 1) * sizeof(KLIJENTI)), SEEK_SET);
		fwrite(&unosKlijenta, sizeof(KLIJENTI), 1, unosUDatoteku);
		rewind(unosUDatoteku);
		fwrite(pBrojKlijenata, sizeof(unsigned int), 1, unosUDatoteku);
		fclose(unosUDatoteku);
	}
}
void ispisKlijenata(char* file, unsigned int* pBrojKlijenata) {

	system("cls");

	FILE* pDatotekaIspis = NULL;
	pDatotekaIspis = fopen(file, "rb");

	if (pDatotekaIspis == NULL) {
		perror("Izbor 2");
		return;
	}
	else {
		KLIJENTI* sviKlijenti = NULL;

		fread(pBrojKlijenata, sizeof(unsigned int), 1, pDatotekaIspis);

		if (*pBrojKlijenata == 0) {
			printf("Nema unesenih clanova\n");
			fclose(pDatotekaIspis);
			return;
		}
		else {
			sviKlijenti = (KLIJENTI*)calloc(*pBrojKlijenata, sizeof(KLIJENTI));
			if (sviKlijenti == NULL) {
				perror("Citanje svih klijenata");
				exit(EXIT_FAILURE);
			}
			else {
				fread(sviKlijenti, sizeof(KLIJENTI), *pBrojKlijenata, pDatotekaIspis);
				fclose(pDatotekaIspis);

				for (int i = 0; i < *pBrojKlijenata; i++) {
					{
						printf("%s ", (sviKlijenti + i)->ime);
						printf("%s ", (sviKlijenti + i)->prezime);
						printf("%s ", (sviKlijenti + i)->broj_mobitela);
						printf("%s ", (sviKlijenti + i)->email);
						printf("\n");
					}
				}
				free(sviKlijenti);
			}
		}
	}
	char izbor[11];
	printf("\n\n\n          Za povratak na izbornik unesite bilo koji broj:  ");
	scanf("%s", izbor);
}

void menu(char* file, unsigned int* pBrojKlijenata) {
	system("cls");
	int opcija;
	while (1) {
		printf("|******************************************\
                \n             Dobrodosli!                 \
                \n Odaberite opciju koju zelite izvrsiti:  \
                \n(1)Unos novog klijenta\
                \n(2)Pretraga klijenta\
                \n(3)Zavrsetak programa\
                \n******************************************|\n");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1:
			dodavanjeKlijenata(file, pBrojKlijenata);
			break;
		case 2:
			ispisKlijenata(file, pBrojKlijenata);
			break;
		case 5:
			system("cls");
			izlaz();
		default:
			printf("\nPritisnite bilo koju tipku za povratak...");
			_getch();

		}
	}
}
void izlaz(void) {
	printf("Da li ste sigurni da zelite zavrsiti program? [da/ne]: \n");
	char odabir[3] = { '\0' };
	scanf(" %2s", odabir);
	if (!strcmp("da", odabir)) {
		exit(EXIT_FAILURE);
	}
	return;
}
