
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void stvaranjeDatoteke(void) {
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

