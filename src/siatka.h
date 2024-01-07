#ifndef _SIATKA_H
#define _SIATKA_H
#include <stdio.h>
#include <wchar.h>


typedef struct siatka{
	int ilosc_w;
	int ilosc_k;
	wchar_t*** komorki;
} siatka_t;

siatka_t* utworz_siatke(int, int);
int wypelnij_siatke_losowo(siatka_t*, double);
int wypelnij_siatke_z_pliku(siatka_t*, FILE*);
void wypisz_siatke(siatka_t*);

#endif
