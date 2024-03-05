#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#include "siatka.h"
#include "mrowka.h"
#include "wczytzap.h"
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "C.UTF-8");
	//ilosc wierszy planszy
	int o_m = 0;
	int m;
	//ilosc kolumn planszy
	int o_n = 0;
	int n;
	//ilosc iteracji
	int o_i = 0;
	int il_i;
	// poczatkowy kierunek
	int o_pk = 0;
	int pk;
	// wybor trybu wczytania planszy
	int o_wcz = 0;
	// procent wypelnienia planszy
	double procent_w;
	int o_pr = 0;
	// nazwa pliku do zapisu
	char* nazwapliku_zapis;
	int o_z = 0;
	// nazwa pliku do wczytania
	char* nazwapliku_wczytanie;	
	// poczatkowe wspolrzedne mrowki
	int px,py;
	int o_px = 0;
	int o_py = 0;
	

	/*
	 m - liczba wierszy planszy
	 n - liczba kolumn planszy 
	 i - liczba iteracji 
	 p - wygenerowanie mapy (procent)
	 w - wczytanie mapy (nazwa pliku)
	 z - zapis rezultatu (nazwa pliku)
	 k - poczatkowy kierunek mrowki (0,1,2,3)
       	 x - poczatkowy wiersz mrowki (domyslnie m/2)
	 y - poczatkowa kolumna mrowki (domyslnie n/2)	 
	 */
	int opcja;
	while((opcja = getopt(argc, argv, "m:n:i:p:w:z:k:x:y:")) != -1)
	{
		switch(opcja)
		{
			case 'm':
			{
				o_m = 1;
				m = atoi(optarg);
				break;
			}
			case 'n':
			{
				o_n = 1;
				n = atoi(optarg);
				break;
			}
			case 'i':
			{
				o_i = 1;
				il_i = atoi(optarg);
				break;
			}
			case 'p':
			{
				//wygenerowanie
				o_pr = 1;
				procent_w = atof(optarg);
				break;
			}	
			case 'w':
			{
				//wczytanie
				o_wcz = 1;
				nazwapliku_wczytanie = optarg;
				break;
			}
			case 'z':
			{
				o_z = 1;
				nazwapliku_zapis = optarg;
				break;

			}
			case 'k':
			{
				o_pk = 1;
				pk = atoi(optarg);

				break;

			}
			case 'x':
			{
				o_px = 1;
				px = atoi(optarg);
				break;
			}
			case 'y':
			{
				o_py = 1;
				py = atoi(optarg);
			}

			default:
			{
				break;
			}
		}

	}
	int ob_i = 0; // obecna ilosc iteracji;
	
	// bledy
	if((o_i == 0 || il_i<0) && o_i == 0)
	{
		fprintf(stderr, "Nie podano ilosci iteracji lub jest nieprawidlowa\n");
		return 1;
	}
	
	if(o_m == 0 || m<0)
	{
		fprintf(stderr, "Nie podano ilosci wierszy lub jest nieprawidlowa\n");
		return 1;
	}
	if(o_n == 0 || n<0)
	{
		fprintf(stderr, "Nie podano ilosci kolumn lub jest nieprawidlowa\n");
		return 1;
	}
	if((o_pk == 0 || pk>3 || pk<0) && o_wcz == 0)
	{
		fprintf(stderr, "Nie podano poczatkowego kierunku lub jest nieprawidlowy\n");
		return 1;
	}
	if((o_wcz == 1 && o_pr == 1))
	{
		fprintf(stderr, "Podany tryb wczytania planszy nie zostal podany lub jest nieprawidlowy\n");
		return 1;
	}
	
	if(o_pr == 1 && (procent_w>100 || procent_w<0))
	{
		fprintf(stderr, "Nieprawidlowa ilosc procent zapelnienia planszy czarnymi polami\n");
		return 1;
	}
	
	if(o_wcz == 1 && (o_px == 1 || o_py == 1))
	{
		fprintf(stderr, "Podano tryb wczytania planszy, wiec ignoruje podane wspolrzedne");
	
	}
	
	if(o_pr == 0 && o_wcz == 0)
	{
		procent_w =0;	
	}
	
	// koniec bledow
	
	siatka_t* plansza = utworz_siatke(m,n);
	obramowanie(plansza);
	if(o_px == 0 && o_wcz == 0 )
	{
		px = (int)(m/2);

	}	

	if(o_py == 0 && o_wcz == 0)
	{
		py = (int)(n/2);
	}
	
	mrowka_t* mr = utworz_mrowke(px, py, pk);

	if(o_wcz == 1)
	{
		FILE* plik = fopen(nazwapliku_wczytanie, "r");
		if(plik == NULL)
		{
			fprintf(stderr, "%s: Nie mozna otworzyc pliku\n", argv[0]);
			return 1;
		}
		wypelnij_siatke_z_pliku(plansza, mr, plik);
		fclose(plik);
	}
	else
	{
		wypelnij_siatke_losowo(plansza, procent_w);
	}


	
	
	while(ob_i!=il_i+1)
	{
		
		strzalka(plansza, mr);
		if(o_z == 1)
		{
	
			char *tmp = malloc(128*sizeof(char));
			sprintf(tmp, "%s_%d", nazwapliku_zapis, ob_i);
			FILE *zapis = fopen(tmp, "w");
			zapisz_siatke(zapis, plansza);
			free(tmp);
			
		
		}
		else
		{
			printf("%d:\n",ob_i);
			wypisz_siatke(plansza);
		}
		
		ruch(plansza, mr);
		ob_i++;
		
		if(mr->x == 0 || mr->x == plansza->ilosc_w-1 || mr->y == 0 || mr->y == plansza->ilosc_k-1) // czy mrowka nie wyszla za plansze
		{
			printf("Mrowka wyszla za plansze\n");
			break;
		}
		
		
	
	}
	ob_i--;
	printf("Koncowa ilosc iteracji: %d\n", ob_i);
	
	
	
	
	
	
	
	
	
	
	return 0;
	
	
}
