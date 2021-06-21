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

void unosKlijenata(char* file, unsigned int* brojKlijenata) {

	FILE* unos = NULL;

	unos = fopen(file, "rb+");

	if (unos == NULL) {
		perror("              Izbornik 1 - Greska dodavanja novog clana u datoteku\n");
		return;
	}
	else {
		KLIJENTI unosClanova = { 0 };
		printf("\n\n   ================================================\n\n");
		printf("          Unos novih korisnickih racuna\n");
		printf("\n   ================================================\n\n");
		printf("          Unesite podatke o korisniku:\n\n");
		printf("          Ime: ");
		scanf("%21s", unosClanova.ime);
		printf("          Prezime: ");
		scanf("%21s", unosClanova.prezime);
		printf("          Broj mobitela: +385");
		char privremeniBroj[10] = { '\0' };
		scanf("%9s", privremeniBroj);
		strcpy(unosClanova.broj_mobitela, "+385");
		strcat(unosClanova.broj_mobitela, privremeniBroj);
		printf("          Datum placanja: ");
		scanf("%20s", unosClanova.datum_placanja);
		unosClanova.id = (*brojKlijenata)++;

		fseek(unos, sizeof(unsigned int) + ((*brojKlijenata- 1) * sizeof(KLIJENTI)), SEEK_SET);
		fwrite(&unosClanova, sizeof(KLIJENTI), 1, unos);
		rewind(unos);
		fwrite(brojKlijenata, sizeof(unsigned int), 1, unos);
		fclose(unos);
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
			sviKlijenti = (KLIJENTI *)calloc(*brojKlijenata, sizeof(KLIJENTI));
			if (sviKlijenti == NULL) {
				perror("Citanje svih klijenata");
				exit(EXIT_FAILURE);
			}
			else {
				fread(sviKlijenti, sizeof(KLIJENTI), *brojKlijenata, ispisDatoteke);
				fclose(ispisDatoteke);
				
				unsigned int i;

				for (i = 0; i < *brojKlijenata; i++) {
					if (i != 0) {
						printf("ID: %u  \n", (sviKlijenti + i)->id);
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

void sortiranje_izbornik() {		//ova funkcija pojednostavljuje izbornik za sortiranje, daje korisniku mogucnost izbora nacina sortiranja opet u switch caseu odabrani broj ucitava odredjenu funkciju
	KLIJENTI* klijentii = NULL;
	FILE* fileD = NULL;
	char prvi_odabir, drugi_odabir;
	//char odabir[30];

	int brojKlijenata;
	system("cls");

	fileD = fopen("file.bin", "rb");
	if (fileD == NULL) {
		printf("\nGreska.\n");
	}
	else {
		fread(&brojKlijenata, sizeof(int), 1, fileD); //citanje broja klijenata
		klijentii = (KLIJENTI*)malloc(brojKlijenata * sizeof(KLIJENTI));
		if (klijentii == NULL) {
			printf("\nNesto je poslo po krivu :(!");
		}
		else {
			fread(klijentii, sizeof(KLIJENTI), brojKlijenata, fileD);
			system("cls");
			printf("Odaberite nacin sortiranja:\n");
			printf("1. Naziv dogadjaja\n2. Cijena\n3. Broj dostupnih mjesta\n4. Godina izdanja\n");
			do {
				prvi_odabir = _getch();
			} while (prvi_odabir < '1' || prvi_odabir > '4');
			//printf("Redoslijed:\n1. Uzlazno\n2. Silazno");
			printf("Redoslijed: \n1. Od najmanje\n2. Od najvece");
			do {
				drugi_odabir = _getch();
			} while (drugi_odabir < '1' || drugi_odabir > '2');

			switch (prvi_odabir) {
			case '1':
				if (drugi_odabir == '1') {
					sortiranje_po_imenu_uzlazno(klijentii, brojKlijenata);
				}
				else {
					sortiranje_po_imenu_silazno(klijentii, brojKlijenata);
				}
				break;
			}
			fclose(fileD);
			fileD = fopen("file.bin", "wb");
			if (fileD == NULL) {
				printf("\nNesto je poslo po krivu :(!");
			}
			else {
				//ovdje azuriram datotku
				fwrite(&brojKlijenata, sizeof(int), 1, fileD);
				fwrite(klijentii, sizeof(KLIJENTI), brojKlijenata, fileD);
				fclose(fileD);
			}
			free(klijentii);
			klijentii = NULL;
		}
	}
	printf("\n\nSortiranje uspjesno obavljeno. Za rezultate pogledajte kosaricu!");
	printf("\nPritisnite bilo koju tipku za povratak...");
	_getch();
}
void sortiranje_po_imenu_silazno(KLIJENTI* klijentii, unsigned int* brojKlijenata) {		//ova funkcija sortira silazno i uzlazno pomocu sortiranja biranjem, selection sort te onda updatea datoteku zamjenom 
	KLIJENTI temp;																		// trenutnih datoteka imena, cijena, mjesta sa novim sortiranim
	char prvo_slovo, prvo_slovo_pom;
	int min;


	for (int i = 0; i < brojKlijenata - 1; i++) {
		min = i;
		prvo_slovo = (klijentii + i)->ime[0] >= 'A' && (klijentii + i)->ime[0] <= 'Z' ? (klijentii + i)->ime[0] : (klijentii + i)->ime[0] - 32;
		for (int j = i + 1; j < brojKlijenata; j++) {
			prvo_slovo_pom = (klijentii + j)->ime[0] >= 'A' && (klijentii + j)->ime[0] <= 'Z' ? (klijentii + j)->ime[0] : (klijentii + j)->ime[0] - 32;
			if (prvo_slovo < prvo_slovo_pom) {
				min = j;
				prvo_slovo = (klijentii + j)->ime[0] >= 'A' && (klijentii + j)->ime[0] <= 'Z' ? (klijentii + j)->ime[0] : (klijentii + j)->ime[0] - 32;
			}
		}
		//zamjena imena klijenata
		strcpy(temp.ime, (klijentii + i)->ime);
		strcpy((klijentii + i)->ime, (klijentii + min)->ime);
		strcpy((klijentii + min)->ime, temp.ime);
		//zamjena cijene eventa
		strcpy(temp.ime, (klijentii + i)->prezime);
		strcpy((klijentii + i)->prezime, (klijentii + min)->prezime);
		strcpy((klijentii + min)->prezime, temp.prezime);
		//zamjena dostupnih ul eventa
		strcpy(temp.broj_mobitela, (klijentii + i)->broj_mobitela);
		strcpy((klijentii + i)->broj_mobitela, (klijentii + min)->broj_mobitela);
		strcpy((klijentii + min)->broj_mobitela, temp.broj_mobitela);
		//zamjena godine izdanja
		strcpy(temp.datum_placanja, (klijentii + i)->datum_placanja);
		strcpy((klijentii + i)->datum_placanja, (klijentii + min)->datum_placanja);
		strcpy((klijentii + min)->datum_placanja, temp.datum_placanja);
	}

	return;
}
void sortiranje_po_imenu_uzlazno(KLIJENTI* klijentii, unsigned int* brojKlijenata) {		//ova funkcija sortira kao i prosla samo to radi u uzlaznom nacinu
	KLIJENTI temp;
	char prvo_slovo, prvo_slovo_pom;
	int max;

	for (int i = 0; i < brojKlijenata - 1; i++) {
		max = i;
		prvo_slovo = (klijentii + i)->ime[0] >= 'A' && (klijentii + i)->ime[0] <= 'Z' ? (klijentii + i)->ime[0] : (klijentii + i)->ime[0] - 32;
		for (int j = i + 1; j < brojKlijenata; j++) {
			prvo_slovo_pom = (klijentii + j)->ime[0] >= 'A' && (klijentii + j)->ime[0] <= 'Z' ? (klijentii + j)->ime[0] : (klijentii + j)->ime[0] - 32;
			if (prvo_slovo > prvo_slovo_pom) {
				max = j;
				prvo_slovo = (klijentii + j)->ime[0] >= 'A' && (klijentii + j)->ime[0] <= 'Z' ? (klijentii + j)->ime[0] : (klijentii + j)->ime[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime, (klijentii + i)->ime);
		strcpy((klijentii + i)->ime, (klijentii + max)->ime);
		strcpy((klijentii + max)->ime, temp.ime);
		//zamjena cijene eventa
		strcpy(temp.ime, (klijentii + i)->prezime);
		strcpy((klijentii + i)->prezime, (klijentii + max)->prezime);
		strcpy((klijentii + max)->prezime, temp.prezime);
		//zamjena dostupnih ul eventa
		strcpy(temp.broj_mobitela, (klijentii + i)->broj_mobitela);
		strcpy((klijentii + i)->broj_mobitela, (klijentii + max)->broj_mobitela);
		strcpy((klijentii + max)->broj_mobitela, temp.broj_mobitela);
		//zamjena godine izdanja
		strcpy(temp.datum_placanja, (klijentii + i)->datum_placanja);
		strcpy((klijentii + i)->datum_placanja, (klijentii + max)->datum_placanja);
		strcpy((klijentii + max)->datum_placanja, temp.datum_placanja);
	}

	return;
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
				\n(6)Sortiranje\
				\n(0)Zavrsetak programa\
                \n******************************************|\n");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1:
			system("cls");
			unosKlijenata(file, brojKlijenata);
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
		case 6:
			system("cls");
			sortiranje_izbornik();
			break;
		case 0:
			system("cls");
			izlaz();
		default:
			system("cls");
			printf("Pritisnite [Enter] kako biste se vratili u izbornik.\n");
			while(getchar()!='\n'); // option TWO to clean stdin
			getchar(); // wait for ENTER

		}
	}
}
