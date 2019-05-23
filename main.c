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

lista *losujObjekty(lista **head,int ilosc){
	srand(time(NULL));
	int i;
	*head=malloc(sizeof(lista));
	lista *current=*head;
	for(i=1;i<ilosc;i++){
		current->sila=rand()%25;
		current->zycia=rand()%3+1;
		current->jedzenie=2;
		current->next=malloc(sizeof(lista));
		current=current->next;
	}
	return *head;
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
	losujObiekty(&obiekty,ilosc);
	int i,j;
	return 0;
}