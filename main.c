#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <conio.h>
#include "header.h"

int main(void) {
	char* klijenti = "klijenti.bin";
	unsigned int brojKlijenata = 1;
	provjeraDatoteke(klijenti, &brojKlijenata);
	menu(klijenti, &brojKlijenata);

	return 0;
}
