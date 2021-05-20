
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
	
