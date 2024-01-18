#include <stdlib.h>
#include <wchar.h>
#include "siatka.h"
#include "mrowka.h"

mrowka_t* utworz_mrowke(int x, int y, int k)
{
	mrowka_t* m = (mrowka_t*) malloc(sizeof(mrowka_t));
	m->x = x;
	m->y = y;
	m->k = k;
	return m;
}

int strzalka(siatka_t* s, mrowka_t* m)
{
	int w,b;
	


	wchar_t *anw = L"△";
	wchar_t *anb = L"▲"; 
	wchar_t *aew = L"▷";
	wchar_t *aeb = L"▶";
	wchar_t *asw = L"▽";
	wchar_t *asb = L"▼";
	wchar_t *aww = L"◁";
	wchar_t *awb = L"◀";
	wchar_t *square_white = L" ";
	wchar_t *square_black = L"█";
	if(wcscmp(s->komorki[m->x][m->y],square_white) == 0)
	{
		w = 1; // biale pole
	}
	if(wcscmp(s->komorki[m->x][m->y],square_black) == 0)
	{
		b = 1; // czarne pole
	}
	
	switch(m->k)
	{
		case 0: //gora
		{ 
			
			if(w == 1)
			{
			
				s->komorki[m->x][m->y] = anw;
				
			}
			else if(b == 1)
			{
				s->komorki[m->x][m->y] = anb;
			}
			
			break;
		}
		
		case 1: //prawo
		{ 
			if(w == 1)
			{
				
				s->komorki[m->x][m->y] = aew;
			
			}
			else if(b == 1)
			{
			
				s->komorki[m->x][m->y] = aeb;	
			
			}
			break;
		}
		
		case 2: //dol
		{ 
			if(w == 1)
			{
			
				s->komorki[m->x][m->y] = asw;
			
			}
			else if(b == 1)
			{
			
				s->komorki[m->x][m->y] = asb;
			
			}
			break;
		}
		
		case 3: //lewo
		{ 
			if(w == 1)
			{
			
				s->komorki[m->x][m->y] = aww;
			
			}
			else if(b == 1)
			{
			
				s->komorki[m->x][m->y] = awb;
			
			}
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	return 0;

}

int ruch(siatka_t* s, mrowka_t* m)
{
	
	wchar_t *anw = L"△";
	wchar_t *anb = L"▲"; 
	wchar_t *aew = L"▷";
	wchar_t *aeb = L"▶";
	wchar_t *asw = L"▽";
	wchar_t *asb = L"▼";
	wchar_t *aww = L"◁";
	wchar_t *awb = L"◀";
	wchar_t *square_white = L" ";
	wchar_t *square_black = L"█";
	if(wcscmp(s->komorki[m->x][m->y],anw) == 0 || wcscmp(s->komorki[m->x][m->y],aew) == 0 || wcscmp(s->komorki[m->x][m->y],asw) == 0 || wcscmp(s->komorki[m->x][m->y],aww) == 0)
	{
		s->komorki[m->x][m->y] = square_black;
		m->k = ((m->k+1)%4); // obrot o 90 stopni w prawo
		
	
	}
	else if(wcscmp(s->komorki[m->x][m->y],anb) == 0 || wcscmp(s->komorki[m->x][m->y],aeb) == 0 || wcscmp(s->komorki[m->x][m->y],asb) == 0 || wcscmp(s->komorki[m->x][m->y],awb) == 0)
	{	
		s->komorki[m->x][m->y] = square_white;
		m->k = ((m->k-1)%4); // obrot o 90 stopni w lewo
		if(m->k==-1)
		{
			m->k = 3;	
		}
		
	}
	
	switch(m->k)
	{
		case 0: //gora
		{ 
			m->x--;
			break;
		}
		
		case 1: //prawo
		{ 
			m->y++;
			break;
		}
		
		case 2: //dol
		{ 
			m->x++;
			break;
		}
		
		case 3: //lewo
		{ 
			m->y--;
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
	
	return 0;
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

