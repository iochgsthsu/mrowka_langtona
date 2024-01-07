#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include "siatka.h"
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "C.UTF-8");
	int m,n,il_i,pk;
	int opcja;
	int p_tryb;
	double procent_w;
	char* nazwapliku_zapis, nazwapliku_wczytanie;
	

	/*
	 m - liczba wierszy planszy
	 n - liczba kolumn planszy
	 i - liczba iteracji
	 p - wygenerowanie mapy
	 w - wczytanie mapy
	 n - nazwa pliku
	 k - poczatkowy kierunek  
	 */
	while((opcja = getopt(argc, argv, "m:n:i:p:w:e:k:")) != -1)
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
			case 'e':
			{
				nazwapliku_zapis = optarg;
				break;

			}
			case 'k':
			{

				break;

			}
			default:
			{
				break;
			}
		}

	}

	//printf("m:%d, n:%d, i:%d", m,n,il_i);
	siatka_t* plansza = utworz_siatke(m,n);
	wypelnij_siatke_losowo(plansza, procent_w);
	wypisz_siatke(plansza);

	







}
