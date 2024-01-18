#include "siatka.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
siatka_t* utworz_siatke(int m, int n)
{
	siatka_t* s = (siatka_t*) malloc(sizeof(siatka_t));
	s->ilosc_w = m+2;
	s->ilosc_k = n+2;
	s->komorki = (wchar_t***)malloc(s->ilosc_w * sizeof(wchar_t**));
	for(int i = 0; i < s->ilosc_w; i++)
	{
		s->komorki[i] = (wchar_t**)malloc(s->ilosc_k * sizeof(wchar_t*));
	}
	return s;
}

int obramowanie(siatka_t* s)
{
	s->komorki[0][0] = L"┌";
	s->komorki[0][s->ilosc_k-1] = L"┐";
	s->komorki[s->ilosc_w-1][s->ilosc_k-1] = L"┘";
	s->komorki[s->ilosc_w-1][0] = L"└";
	
	for(int i = 1; i<s->ilosc_k-1; i++)
	{
		s->komorki[0][i] = L"─";
		s->komorki[s->ilosc_w-1][i] = L"─";
	}
	
	for(int i = 1; i<s->ilosc_w-1; i++)
	{
		s->komorki[i][0] = L"│";
		s->komorki[i][s->ilosc_k-1] = L"│";
	}
	
	return 1;
	
	

}

int wypelnij_siatke_z_pliku(siatka_t* s, FILE* plik)
{
	if(s == NULL || plik == NULL)
	{
		return 1;
	}
	int x = 0;
	int y = 0;
	wchar_t w,r;
	while((w = fgetwc(plik)) != WEOF)
	{
		while((r = fgetwc(w)) != WEOF)
		{
		
		if(w == '\n')
		{
			x = 0;
			y++;
			continue;
		}
		
		s->komorki[x][y] = w;
		x++;
		
		
		
		}
		
	}
	
	return 0;

}

int wypelnij_siatke_losowo(siatka_t* s, double procent)
{
	wchar_t *square_white = L" ";
	wchar_t *square_black = L"█";
	if(s==NULL)
	{
		return 1;
	}
	
	for(int i = 1; i<s->ilosc_w-1; i++)
	{
		for(int j = 1; j<s->ilosc_k-1; j++)
		{
			
			s->komorki[i][j] = square_white;
		}
	}
	int ilosc_czarnych = (int)(((s->ilosc_k-2)*(s->ilosc_w-2))*(procent/100));
	int aktualna_ilosc = 0;
	srand(time(0));
	int tmp_x, tmp_y;
	while(ilosc_czarnych != aktualna_ilosc)
	{
		tmp_x = (rand()%(s->ilosc_w-2)) +1;
		tmp_y = (rand()%(s->ilosc_k-2)) +1;
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

void zapisz_siatke(FILE *plik, siatka_t* s)
{

	for (int i = 0; i<s->ilosc_w; i++) {
		for (int j = 0; j <s->ilosc_k; j++) {
			fprintf(plik, "%ls", s->komorki[i][j]);
		}
		fprintf(plik, "\n");
	}


}

