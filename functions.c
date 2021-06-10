#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "Header.h"

void provjeraDatoteke(char* file, unsigned int* brojKlijenata) {

	FILE* fp = fopen(file, "rb");

	if (fp == NULL) {

		perror("Datoteka ne postoji\n");

		fp = fopen(file, "wb");

		if (fp == NULL) {

			perror("Datoteka se ne moze kreirati");
			exit(EXIT_FAILURE);
		}
		else {

			fwrite(brojKlijenata, sizeof(unsigned int), 1, fp);
			fclose(fp);
			printf("Datoteka kreirana\n");
		}
	}
	else {

		fread(brojKlijenata, sizeof(unsigned int), 1, fp);
		printf("\nDatoteka postoji");
		fclose(fp);
	}
}

void dodavanjeKlijenata(char* file, unsigned int* brojKlijenata) {
	
	FILE* unosUDatoteku = NULL;
	unosUDatoteku = fopen(file, "rb+");

	if (unosUDatoteku == NULL) {
		perror("              Izbornik 1 - Greska dodavanja novog clana u datoteku\n");
		return;
	}
	else {
		KLIJENTI unosClan = { 0 };
		printf("\n\n   ================================================\n\n");
		printf("          Unos novih korisnickih racuna\n");
		printf("\n   ================================================\n\n");
		printf("          Unesite podatke o korisniku:\n\n");
		printf("          Ime: ");
		scanf("%21s", unosClan.ime);
		printf("          Prezime: ");
		scanf("%21s", unosClan.prezime);
		printf("          Broj mobitela: ");
		char privremeniBroj[10] = { '\0' };
		scanf("%9s", privremeniBroj);
		strcpy(unosClan.broj_mobitela, "+385");
		strcat(unosClan.broj_mobitela, privremeniBroj);
		printf("          Datum placanja clanarine: ");
		scanf("%25s", unosClan.datum_placanja);
		unosClan.id = (*brojKlijenata)++;


		fseek(unosUDatoteku, sizeof(unsigned int) + ((*brojKlijenata - 1) * sizeof(KLIJENTI)), SEEK_SET);
		fwrite(&unosClan, sizeof(KLIJENTI), 1, unosUDatoteku);
		rewind(unosUDatoteku);
		fwrite(brojKlijenata, sizeof(unsigned int), 1, unosUDatoteku);
		fclose(unosUDatoteku);
	}
}

void ispisKlijenata(char* file, unsigned int* brojKlijenata) {

	FILE* ispisDatoteke = NULL;
	ispisDatoteke = fopen(file, "rb");

	if (ispisDatoteke == NULL) {
		perror("Izbor 2");
		return;
	}
	else {
		KLIJENTI* sviKlijenti = NULL;

		fread(brojKlijenata, sizeof(unsigned int), 1, ispisDatoteke);

		if (*brojKlijenata == 0) {
			printf("Nema unesenih clanova\n");
			fclose(ispisDatoteke);
			return;
		}
		else {
			sviKlijenti = (KLIJENTI*)calloc(*brojKlijenata, sizeof(KLIJENTI));
			if (sviKlijenti == NULL) {
				perror("Citanje svih klijenata");
				exit(EXIT_FAILURE);
			}
			else {
				fread(sviKlijenti, sizeof(KLIJENTI), *brojKlijenata, ispisDatoteke);
				fclose(ispisDatoteke);

				for (int i = 0; i < *brojKlijenata; i++) {
					if (i != 0) {
						//printf("ID: %s \n", (sviKlijenti + i)->id);
						printf("Ime: %s \n", (sviKlijenti + i)->ime);
						printf("Prezime: %s \n", (sviKlijenti + i)->prezime);
						printf("Broj mobitela: %s \n", (sviKlijenti + i)->broj_mobitela);
						printf("Datum placanja clanarine: %s \n", (sviKlijenti + i)->datum_placanja);
						printf("\n");
					}
				}
				free(sviKlijenti);
			}
		}
	}
	printf("\nPritisnite [Enter] kako biste se vratili u izbornik.\n");
	while (getchar() != '\n'); // option TWO to clean stdin
	getchar(); // wait for ENTER
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
		printf("\n\n	(1.) Da");
		printf("\n	(2.) Ne");

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
void pretragaPoImenu(char* file, unsigned int* brojKlijenata) {

	FILE* pDatotekaProcitaj = NULL;
	pDatotekaProcitaj = fopen(file, "rb");

	if (pDatotekaProcitaj == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;
	}
	else {

		KLIJENTI* sviKlijenti = NULL;

		fread(brojKlijenata, sizeof(unsigned int), 1, pDatotekaProcitaj);

		if (*brojKlijenata == 0) {

			printf("          Nema unesenih clanova!\n");
			fclose(pDatotekaProcitaj);
			return;
		}
		else {

			sviKlijenti = (KLIJENTI*)calloc(*brojKlijenata, sizeof(KLIJENTI));

			if (sviKlijenti == NULL) {

				perror("          Citanje svih korisnika");
				exit(EXIT_FAILURE);
			}
			else {

				fread(sviKlijenti, sizeof(KLIJENTI), *brojKlijenata, pDatotekaProcitaj);
				fclose(pDatotekaProcitaj);

				unsigned int i;

				printf("          Unesite ime korisnika: \n");
				char privremenoIme[31] = { '\0' };
				scanf("%30s", privremenoIme);
				unsigned int statusPronalaska = 0;
				unsigned int indeksPronalaska = -1;

				for (i = 0; i < *brojKlijenata; i++) {

					if (!strcmp((sviKlijenti + i)->ime, privremenoIme)) {
						statusPronalaska = 1;
						indeksPronalaska = i;
					}
				}
				if (statusPronalaska) {
					system("cls");
					printf("          Korisnik pronaden:\n\n");
					printf("Ime: %s\n", (sviKlijenti + indeksPronalaska)->ime);
					printf("Prezime: %s\n", (sviKlijenti + indeksPronalaska)->prezime);
					printf("Broj mobitela: %s\n", (sviKlijenti + indeksPronalaska)->broj_mobitela);;
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
void izmjenaPodataka(char* file, unsigned int* brojKlijenata) {

	FILE* citanjeDatoteke = NULL;
	citanjeDatoteke = fopen(file, "rb");

	if (citanjeDatoteke == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;
		//exit(EXIT_FAILURE);
	}
	else {

		KLIJENTI* sviKlijenti = NULL;

		fread(brojKlijenata, sizeof(unsigned int), 1, citanjeDatoteke);

		if (*brojKlijenata == 0) {

			printf("          Nema unesenih clanova!\n");
			fclose(citanjeDatoteke);
			return;
		}
		else {

			sviKlijenti = (KLIJENTI*)calloc(*brojKlijenata, sizeof(KLIJENTI));

			if (sviKlijenti == NULL) {

				perror("          Citanje svih korisnika");
				exit(EXIT_FAILURE);
			}
			else {

				KLIJENTI privremeniKlijenti = { 0 };
				fread(sviKlijenti, sizeof(KLIJENTI), *brojKlijenata, citanjeDatoteke);

				unsigned int i;

				printf("          Unesite ID trazenog korisnika: ");
				int privremeniID = 0;
				scanf("%d", &privremeniID);
				unsigned int statusPronalaska = 0;
				unsigned int indeksPronalaska = -1;

				for (i = 0; i < *brojKlijenata; i++) {

					if (privremeniID == (sviKlijenti + i)->id) {
						statusPronalaska = 1;
						indeksPronalaska = i;
					}
				}
				if (statusPronalaska) {
					system("cls");
					printf("          Korisnik pronadjen:\n\n");
					printf("          %u\t", (sviKlijenti + indeksPronalaska)->id);
					printf("          %s ", (sviKlijenti + indeksPronalaska)->ime);
					printf("          %s ", (sviKlijenti + indeksPronalaska)->prezime);
					printf("          %s", (sviKlijenti + indeksPronalaska)->broj_mobitela);
					fclose(citanjeDatoteke);
					citanjeDatoteke = fopen(file, "rb+");

					printf("\n   ================================================\n\n");
					printf("          Izmjena podataka o korisniku\n");
					printf("\n   ================================================\n\n");

					printf("          Novo ime: ");
					scanf(" %50[^\n]", privremeniKlijenti.ime);
					printf("          Novo prezime: ");
					scanf(" %50[^\n]", privremeniKlijenti.prezime);
					printf("          Novi broj mobitela: ");
					char privremeniBroj[10] = { '\0' };
					scanf("%9s", privremeniBroj);
					strcpy(privremeniKlijenti.broj_mobitela, "+385");
					strcat(privremeniKlijenti.broj_mobitela, privremeniBroj);
					privremeniKlijenti.id = indeksPronalaska;

					fseek(citanjeDatoteke, sizeof(unsigned int) + ((indeksPronalaska) * sizeof(KLIJENTI)), SEEK_SET);
					fwrite(&privremeniKlijenti, sizeof(KLIJENTI), 1, citanjeDatoteke);
					rewind(citanjeDatoteke);
					fwrite(brojKlijenata, sizeof(unsigned int), 1, citanjeDatoteke);
					fclose(citanjeDatoteke);
					int pom;
					printf("\n\nPritisnite bilo koju tipku za nastavak: ");
					scanf("%d", &pom);
				}
				else {
					int pom;
					printf("          Nepostojeci korisnik\n");
					printf("\n\n          Unesite bilo koji broj za nastavak: ");
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
void menu(char* file, unsigned int* brojKlijenata) {
	system("cls");
	int opcija;
	while (1) {
		printf("|******************************************\
                \n             Dobrodosli!                 \
                \n Odaberite opciju koju zelite izvrsiti:  \
                \n(1)Unos novog klijenta\
                \n(2)Ispis svih klijenata\
				\n(3)Pretraga klijenta po imenu\
				\n(4)Izmjena podataka o klijentima\
                \n(5)Brisanje datoteke s klijentima\
				\n(0)Zavrsetak programa\
                \n******************************************|\n");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1:
			system("cls");
			dodavanjeKlijenata(file, brojKlijenata);
			break;
		case 2:
			system("cls");
			ispisKlijenata(file, brojKlijenata);
			break;
		case 3:
			system("cls");
			pretragaPoImenu(file, brojKlijenata);
			break;
		case 4:
			system("cls");
			izmjenaPodataka(file, brojKlijenata);
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
			printf("Pritisnite [Enter] kako biste se vratili u izbornik.\n");
			while (getchar() != '\n'); // option TWO to clean stdin
			getchar(); // wait for ENTER

		}
	}
}
