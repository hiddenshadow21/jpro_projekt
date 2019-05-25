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

void losujObiekty();
void wypisz();
void ruch();
void symulujDzien();

int main(){
    srand(time(NULL));
	int rozmiar,iloscOb;
	printf("Podaj rozmiar planszy:\n");
	scanf("%d",&rozmiar);
	char plansza[rozmiar][rozmiar];
	do{
		printf("Podaj poczatkowa iloscOb obiektow:\n");
		scanf("%d",&iloscOb);
		if(iloscOb>rozmiar*rozmiar) printf("ilosc obiektow/jedzenia nie moze przekraczac ilosci pol planszy!\n");
	}while(iloscOb>rozmiar*rozmiar);

	lista *obiekty=malloc(sizeof(lista));
	losujObiekty(&obiekty,iloscOb,rozmiar,plansza);
	symulujDzien(obiekty,rozmiar,plansza);

	return 0;
}

void losujObiekty(lista **head,int iloscOb, int rozmiar, char tab[][rozmiar]){
	int i,j,x,y;
	for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            tab[i][j]='#';
        }
	}
	lista *current=*head;
	for(i=0;i<iloscOb;i++){
		current->sila=rand()%25;
		current->zycia=rand()%3+1;
		current->jedzenie=2;
		x=rand()%rozmiar;
		y=rand()%rozmiar;
		while(tab[y][x]!='#'){
            x=rand()%rozmiar;
            y=rand()%rozmiar;
		}
		tab[y][x]='O';
        current->x=x;
        current->y=y;
        current->next=malloc(sizeof(lista));
        current=current->next;
	}
	current->next=NULL;
}

void wypisz(int rozmiar, char tab[][rozmiar], lista *head){
    int i,j;
    lista *current=head;
    for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
                tab[i][j]='#';
        }
    }
    while(current->next!=NULL){
        tab[current->y][current->x]='O';
        current=current->next;
    }
    for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            printf("%c ",tab[i][j]);
        }
        puts("");
    }
}

void ruch(lista *current,int rozmiar){
    int a;
    a=rand()%4+1;
    switch(a){
        case 1:
            current->x++;
            if(current->x>rozmiar-1){
                current->x-=2;
            }
            break;
        case 2:
            current->x--;
            if(current->x<0){
                current->x+=2;
            }
            break;
        case 3:
            current->y--;
            if(current->y<0){
                current->y+=2;
            }
            break;
        case 4:
            current->y++;
            if(current->y>rozmiar-1){
                current->y-=2;
            }
            break;
    }
}

void symulujDzien(lista *head, int rozmiar, char tab[][rozmiar]){
    int i;
    lista *current=head;
    for(i=0;i<12;i++){
        while(current->next!=NULL){
            ruch(current, rozmiar);
            current=current->next;
        }
        current=head;
        wypisz(rozmiar,tab,head);
        puts("");
    }
}


