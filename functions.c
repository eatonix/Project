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
	FILE* fileP = NULL;
	KLIJENTI* dodavanjeKlijenata = NULL;
	dodavanjeKlijenata = (KLIJENTI*)malloc(sizeof(KLIJENTI));
	int broj_klijenata;
	if (dodavanjeKlijenata == NULL) {
		return 1;
	}
	else {
		printf("\n\n   ================================================\n\n");
		printf("          Unos novih korisnickih racuna\n");
		printf("\n   ================================================\n\n");
		printf("          Unesite podatke o korisniku:\n\n");
		printf("          Ime: ");
		scanf("%25s", dodavanjeKlijenata->ime);
		printf("          Prezime: ");
		scanf("%25s", dodavanjeKlijenata->prezime);
		printf("          Broj mobitela: ");
		char privremeniBroj[10] = { '\0' };
		scanf("%9s", privremeniBroj);
		strcpy(dodavanjeKlijenata->broj_mobitela, "+385");
		strcat(dodavanjeKlijenata->broj_mobitela, privremeniBroj);
		dodavanjeKlijenata->id = (*pBrojKlijenata)++;

		fileP = fopen("klijenti.bin", "rb");
		if (fileP == NULL) {
			fileP = fopen("klijenti.bin", "wb");
			broj_klijenata = 1;
			fwrite(&broj_klijenata, sizeof(int), 1, fileP);
			fwrite(dodavanjeKlijenata, sizeof(KLIJENTI), 1, fileP);
			fclose(fileP);
		}
		else {
			fclose(fileP);
			fileP = fopen("klijenti.bin", "rb+");
			if (fileP == NULL) {
				return 1;
			}
			else {
				fseek(fileP, 0, SEEK_SET);
				fread(&broj_klijenata, sizeof(int), 1, fileP);
				broj_klijenata++;
				fseek(fileP, 0, SEEK_SET);
				fwrite(&broj_klijenata, sizeof(int), 1, fileP);
				fseek(fileP, 0, SEEK_END);
				fwrite(dodavanjeKlijenata, sizeof(KLIJENTI), 1, fileP);
				fclose(fileP);
			}
		}
	}

	free(dodavanjeKlijenata);
}

void ispisKlijenata(char* file, unsigned int* pBrojKlijenata) {

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
						printf("\n");
					}
				}
				free(sviKlijenti);
			}
		}
	}
	char izbor[11];
	printf("\n\n\n          Za povratak na izbornik unesite bilo koji znak:  ");
	scanf("%s", izbor);
}

void brisanjeDatoteke(char* file) {

	FILE* pDatotekaObrisi = NULL;
	pDatotekaObrisi = fopen(file, "rb");

	if (pDatotekaObrisi == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;
		//exit(EXIT_FAILURE);
	}
	else {
		printf("\n   ================================================\n\n");
		printf("            Brisanje datoteke\n");
		printf("\n   ================================================\n\n");

		printf("       Zelite li obrisati datoteku kupci.bin?");
		printf("\n\n	1. Da");
		printf("\n	2. Ne");

		int izbor = -1;

		printf("\n\nUnesite izbor: ");
		scanf("%d", &izbor);
		fclose(pDatotekaObrisi);
		switch (izbor) {
		case 1:
			remove(file);
			exit(EXIT_FAILURE);
		case 2:
			break;
		}
	}
}
void pretragaPoImenu(char* file, unsigned int* pBrojKlijenata) {

	FILE* pDatotekaProcitaj = NULL;
	pDatotekaProcitaj = fopen(file, "rb");

	if (pDatotekaProcitaj == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;
	}
	else {

		KLIJENTI* sviKlijenti = NULL;

		fread(pBrojKlijenata, sizeof(unsigned int), 1, pDatotekaProcitaj);

		if (*pBrojKlijenata == 0) {

			printf("          Nema unesenih clanova!\n");
			fclose(pDatotekaProcitaj);
			return;
		}
		else {

			sviKlijenti = (KLIJENTI*)calloc(*pBrojKlijenata, sizeof(KLIJENTI));

			if (sviKlijenti == NULL) {

				perror("          Citanje svih korisnika");
				exit(EXIT_FAILURE);
			}
			else {

				fread(sviKlijenti, sizeof(KLIJENTI), *pBrojKlijenata, pDatotekaProcitaj);
				fclose(pDatotekaProcitaj);

				unsigned int i;

				printf("          Unesite ime korisnika: \n");
				char privremenoIme[31] = { '\0' };
				scanf("%30s", privremenoIme);
				unsigned int statusPronalaska = 0;
				unsigned int indeksPronalaska = -1;

				for (i = 0; i < *pBrojKlijenata; i++) {

					if (!strcmp((sviKlijenti + i)->ime, privremenoIme)) {
						statusPronalaska = 1;
						indeksPronalaska = i;
					}
				}
				if (statusPronalaska) {
					system("cls");
					printf("          Korisnik pronaden:\n\n");
					printf("          %s ", (sviKlijenti + indeksPronalaska)->ime);
					printf("          %s ", (sviKlijenti + indeksPronalaska)->prezime);
					printf("          %s", (sviKlijenti + indeksPronalaska)->broj_mobitela);;
					int pom;
					scanf("%d", &pom);
				}
				else {
					int pom;
					printf("Nepostojeci korisnik\n");
					scanf("%d", &pom);
				}
				free(sviKlijenti);
			}
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
void menu(char* file, unsigned int* pBrojKlijenata) {
	system("cls");
	int opcija;
	while (1) {
		printf("|******************************************\
                \n             Dobrodosli!                 \
                \n Odaberite opciju koju zelite izvrsiti:  \
                \n(1)Unos novog klijenta\
                \n(2)Ispis svih klijenata\
				\n(3)Pretraga klijenta po imenu\
                \n(5)Brisanje datoteke s klijentima\
				\n(0)Zavrsetak programa\
                \n******************************************|\n");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1:
			system("cls");
			dodavanjeKlijenata(file, pBrojKlijenata);
			break;
		case 2:
			system("cls");
			ispisKlijenata(file, pBrojKlijenata);
			break;
		case 3:
			system("cls");
			pretragaPoImenu(file, pBrojKlijenata);
			break;
		case 5: 
			system("cls");
			brisanjeDatoteke(file);
			break;
		case 0:
			system("cls");
			izlaz();
		default:
			system("cls");
			printf("Stisnite [Enter] kako biste se vratili u izbornik.\n");
			while(getchar()!='\n'); // option TWO to clean stdin
			getchar(); // wait for ENTER

		}
	}
}
