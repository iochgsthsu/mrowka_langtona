#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include "siatka.h"
#include "mrowka.h"
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "C.UTF-8");
	int m,n,il_i,pk;
	int p_tryb;
	int opcja;
	double procent_w;
	char* nazwapliku_zapis;	
	char* nazwapliku_wczytanie;
	

	/*
	 m - liczba wierszy planszy
	 n - liczba kolumn planszy 
	 i - liczba iteracji 
	 p - wygenerowanie mapy (procent)
	 w - wczytanie mapy (nazwa pliku)
	 z - zapis rezultatu (nazwa pliku)
	 k - poczatkowy kierunek (0,1,2,3)  
	 */
	while((opcja = getopt(argc, argv, "m:n:i:p:w:z:k:")) != -1)
	{
		switch(opcja)
		{
			case 'm':
			{
				m = atoi(optarg);
				break;
			}
			case 'n':
			{
				n = atoi(optarg);
				break;
			}
			case 'i':
			{
				il_i = atoi(optarg);
				break;
			}
			case 'p':
			{
				//wygenerowanie
				p_tryb = 1;
				procent_w = atof(optarg);
				break;
			}	
			case 'w':
			{
				//wczytanie
				nazwapliku_wczytanie = optarg;
				p_tryb = 0;
				break;
			}
			case 'z':
			{
				nazwapliku_zapis = optarg;
				break;

			}
			case 'k':
			{
				pk = atoi(optarg);

				break;

			}
			default:
			{
				break;
			}
		}

	}
	int ob_i = 0; // obecna ilosc iteracji;
	siatka_t* plansza = utworz_siatke(m,n);
	
	//int px_m = rand()%(plansza->ilosc_w); // poczatkowe wspolrzedne x i y
	//int py_m = rand()%(plansza->ilosc_k);
	int px_m = 50;
	int py_m = 50;
	mrowka_t* mr = utworz_mrowke(px_m, py_m, pk);
	if(p_tryb == 0)
	{
		FILE* plik = fopen(nazwapliku_wczytanie, "r");
		wypelnij_siatke_z_pliku(plansza, plik);
	}
	else if(p_tryb == 1 )
	{
		wypelnij_siatke_losowo(plansza, procent_w);
	}
	
	while(ob_i!=il_i)
	{
		ruch(plansza, mr);
		if((plansza->ilosc_w < mr->y) || (mr->y<0) || (mr->x<0) || (plansza->ilosc_k < mr->x)) // czy mrowka nie wyszla za plansze
		{
			break;
		}
		wypisz_siatke(plansza);
		ob_i++;
		printf("mx:%d, my:%d, k:%d, i:%d\n", mr->x, mr->y, mr->k, ob_i);
		usleep(10000);
		system("clear");
		
	
	}
	return 0;
	
	
}
