#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h> 

int main(void) {
	int opcija;
	char* klijenti = "klijenti.bin";
	provjeraDatoteke(klijenti, &brojKlijenata);
	izbornik(klijenti, &brojKlijenata);
	return 0;
}

