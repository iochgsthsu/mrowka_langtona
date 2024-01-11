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

int ruch(siatka_t* s, mrowka_t* m)
{
	wchar_t *square_white = L" ";
	wchar_t *square_black = L"█";
	if(wcscmp(s->komorki[m->x][m->y],square_white) == 0)
	{
		s->komorki[m->x][m->y] = square_black;
		m->k = ((m->k+1)%4); // obrot o 90 stopni w prawo
		
	
	}
	else if(wcscmp(s->komorki[m->x][m->y],square_black) == 0)
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
