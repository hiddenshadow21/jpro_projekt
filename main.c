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

void losujObiekty(lista **head,int ilosc, int rozmiar, char tab[][rozmiar]){
	srand(time(NULL));
	int i,j,x,y;
	for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            tab[i][j]='#';
        }
	}
	lista *current=*head;
	for(i=0;i<ilosc;i++){
		current->sila=rand()%25;
		current->zycia=rand()%3+1;
		current->jedzenie=2;
		x=rand()%rozmiar;
		y=rand()%rozmiar;
		while(tab[x][y]!='#'){
            x=rand()%rozmiar;
            y=rand()%rozmiar;
		}
		tab[x][y]='O';
        current->x=x;
        current->y=y;
		current->next=malloc(sizeof(lista));
		current=current->next;
	}
	current->next=NULL;
}

void wypisz(int rozmiar, char tab[][rozmiar]){
    int i,j;
    for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            printf("%c ",tab[i][j]);
        }
        puts("");
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
	lista *obiekty=malloc(sizeof(lista));
	losujObiekty(&obiekty,ilosc,rozmiar,plansza);
	wypisz(rozmiar,plansza);
	return 0;
}
