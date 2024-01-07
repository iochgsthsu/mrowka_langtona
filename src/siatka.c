#include "siatka.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
siatka_t* utworz_siatke(int m, int n)
{
	siatka_t* s = (siatka_t*) malloc(sizeof(siatka_t));
	s->ilosc_w = m;
	s->ilosc_k = n;
	s->komorki = (wchar_t***)malloc(s->ilosc_w * sizeof(wchar_t**));
	for(int i = 0; i < s->ilosc_w; i++)
	{
		s->komorki[i] = (wchar_t**)malloc(s->ilosc_k * sizeof(wchar_t*));
	}
	return s;
}

int wypelnij_siatke_z_pliku(siatka_t* s, FILE* plik)
{
	if(s == NULL || plik == NULL)
	{
		return 1;
	}
	wchar_t c;
	int x = 0;
	int y = 0;
	while((c = fgetc(plik)) != EOF)
	{
		if(c == '\n')
		{
			x = 0;
			y++;
			continue;
		}
		s->komorki[x][y] = c;
		x++;
		
	}
	return 0;

}

int wypelnij_siatke_losowo(siatka_t* s, double procent)
{
	setlocale(LC_ALL, "C.UTF-8");
	wchar_t *square_white = L" ";
	wchar_t *square_black = L"█";
	if(s==NULL)
	{
		return 1;
	}
	
	for(int i = 0; i<s->ilosc_w; i++)
	{
		for(int j = 0; j<s->ilosc_k; j++)
		{
			s->komorki[i][j] = square_white;
		}
	}
	int ilosc_czarnych = (int)((s->ilosc_k*s->ilosc_w)*(procent/100));
	int aktualna_ilosc = 0;
	srand(time(0));
	int tmp_x, tmp_y;
	while(ilosc_czarnych != aktualna_ilosc)
	{
		tmp_x = rand()%(s->ilosc_w);
		tmp_y = rand()%(s->ilosc_k);
		if(s->komorki[tmp_x][tmp_y] != square_black)
		{
			s->komorki[tmp_x][tmp_y] = square_black;
			aktualna_ilosc++;
		}
	
	}
	
	
	return 0;
}

void wypisz_siatke(siatka_t* s) 
{	
	for (int i = 0; i<s->ilosc_w; i++) {
		for (int j = 0; j <s->ilosc_k; j++) {
			printf("%ls", s->komorki[i][j]);
		}
		printf("\n");
	}
}

