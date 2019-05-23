#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct obiekt{
	int x;
	int y;
	int zycia;
	int sila;
	int jedzenie;
	struct obiekt *next;
}lista;

void nowyObjekt(int ilosc){
	srand(time(NULL));
	int i;
	lista *obiekty=malloc(sizeof(lista));
	obiekty->next=NULL;
	lista *current=obiekty;
	for(i=1;i<ilosc;i++){
		current->sila=rand()%25;
		current->zycia=rand()%3+1;
		current->jedzenie=2;
		current->next=malloc(sizeof(lista));
		current=current->next;
	}
}

int main(){
	int rozmiar,ilosc;
	printf("Podaj rozmiar planszy:\n");
	scanf("%d",&rozmiar);
	char plansza[rozmiar][rozmiar];
	do{
		printf("Podaj poczatkowa ilosc obiektow:\n");
		scanf("%d",&ilosc);
		if(ilosc>rozmiar*rozmiar) printf("Ilosc obiektow nie moze przekraczac ilosci pol planszy!\n");
	}while(ilosc>rozmiar*rozmiar);
	nowyObjekt(ilosc);
	int i,j;
	for(i=0;i<rozmiar;i++){
		for(j=0;j<rozmiar;j++){
			plansza[i][j]=97+i+j;
			printf("%c ",plansza[i][j]);
		}
		puts("");
	}
	return 0;
}