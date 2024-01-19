#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include "siatka.h"
#include "mrowka.h"

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
	fclose(plik);


}

int wypelnij_siatke_z_pliku(siatka_t* s, mrowka_t* mr, FILE* plik)
{

	
	if(s == NULL || plik == NULL)
	{
		return 1;
	}
	wchar_t tmp1[s->ilosc_w][s->ilosc_k];
	wchar_t tmp[s->ilosc_k+1];
	for(int i = 0; i<2*s->ilosc_w; i++)
	{
		fgetws(tmp, s->ilosc_k+1, plik);
		if(i%2==0)
		{
			for(int j = 0; j<s->ilosc_k; j++)
			{
				tmp1[i/2][j] = tmp[j];
				
			}
			
		
		}
	
	}
		
	for(int i = 1; i<s->ilosc_w-1; i++)
	{
		for(int j =1; j<s->ilosc_k-1; j++)
		{
			
		
			if(tmp1[i][j] == ' ')
			{
				s->komorki[i][j] = L" ";
			}	
			else if(tmp1[i][j] == 9608) // 9608 - czarne pole
			{

				s->komorki[i][j] = L"█";
			}
			else
			{
				mr->x = i;
				mr->y = j;
				switch(tmp1[i][j])
				{
				
					case 9660: // cs w dol
					{
						s->komorki[i][j] = L"█";
						mr->k = 2;
						break;
					}
					
					case 9650: // cs w gore
					{
						s->komorki[i][j] = L"█";
						mr->k = 0;
						break;
					}
					
					case 9654: // cs w prawo
					{
						s->komorki[i][j] = L"█";
						mr->k = 1;
						break;
					}
					
					case 9664: // cs w lewo
					{
						s->komorki[i][j] = L"█";
						mr->k = 3;
						break;
					}
					
					case 9651: // bs w gore
					{
						s->komorki[i][j] = L" ";
						mr->k = 0;
						break;
					}
					
					case 9665: // bs w lewo
					{
						s->komorki[i][j] = L" ";
						mr->k = 3;
						break;
					}
					
					case 9655: // bs w prawo
					{
						s->komorki[i][j] = L" ";
						mr->k = 1;
						break;
					}
					
					case 9661: // bs w dol
					{
						
						s->komorki[i][j] = L" ";
						mr->k = 2;
						break;
					}
					
					default:
					{
						break;
					}
				
				
				}
			
			}
		
		}
	}

	
	
	

	
	
	
	
	

	
	
	return 0;

}
