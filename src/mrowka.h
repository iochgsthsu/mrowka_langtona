#ifndef _MROWKA_H
#define _MROWKA_H

typedef struct mrowka{
// wspolrzedne mrowki na planszy: (x,y)
	int x;
	int y;
// kierunek (0 - gora, 1 - prawo, 2 - dol, 3 - lewo)
	int k;
} mrowka_t;

mrowka_t* utworz_mrowke(int, int, int);
int strzalka(siatka_t*, mrowka_t*);
int ruch(siatka_t*, mrowka_t*);

#endif

