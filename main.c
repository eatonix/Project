#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h> 

int main(void) {
	int opcija;
	char imeDatoteke[] = { "C:\\users\\student\\klijenti.bin" };
	printf("|******************************************\
                \n             Dobrodosli!                 \
                \n Odaberite opciju koju zelite izvrsiti:  \
                \n\n(1)Dodavanje novog klijenta\
                \n(2)Pretraga klijenta\
                \n(3)Ispis svih klijenata\
                \n(5)Zavrsetak programa\
                \n******************************************|\n");

	do {
		scanf("%u", &opcija);
		if (opcija < 1 || opcija > 5) {
			printf("Unos je neispravan, molim vas pokusajte ponovo.");
		}
	} while (opcija < 1 || opcija > 5);
	switch (opcija) {
	case 1:
		unosKlijenta();
		break;
	}

}

