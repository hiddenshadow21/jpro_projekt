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
void czyTaSamaPozycja();
void usun();
void dodajOb();

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
	wypisz(rozmiar,plansza,obiekty); //plansza startowa
    puts("");
	symulujDzien(&obiekty,rozmiar,plansza);

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
	current->sila=rand()%4;
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
    current->next=NULL;
	for(i=0;i<iloscOb;i++){
        current->next=malloc(sizeof(lista));
        current=current->next;
		current->sila=rand()%4;
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
        current->next=NULL;
	}
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
        printf("%d %d\n",current->x, current->y);
        tab[current->y][current->x]='O';
        current=current->next;
    }
    puts("");
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

void symulujDzien(lista **head, int rozmiar, char tab[][rozmiar]){
    int i;
    lista *current=*head;
    for(i=0;i<4;i++){
        while(current->next!=NULL){
            ruch(current, rozmiar);
            current=current->next;
        }

        current=*head;
        wypisz(rozmiar,tab,*head);
        czyTaSamaPozycja(head);
        puts("");
    }
}

void czyTaSamaPozycja(lista **head){
    lista *obj1=*head, *obj2;
    while(obj1->next!=NULL){
            obj2=obj1->next;
            while(obj2->next!=NULL){
                if(obj1->x == obj2->x && obj1->y == obj2->y){
                    if(obj1->sila > obj2->sila){
                        usun(head,obj2);
                    }
                    else if(obj1->sila < obj2->sila){
                        usun(head,obj1);
                    }
                    else{
                        dodajOb(*head);
                    }
                }
                obj2=obj2->next;
            }
            obj1=obj1->next;
    }
}

void usun(lista **head, lista *doUsuniecia){
    lista *current=*head;
    if(*head==doUsuniecia){
        current=current->next;
        free(*head);
        *head=current;
    }
    else{
        while(current->next!=doUsuniecia){
            current=current->next;
        }
        current->next=doUsuniecia->next;
        free(doUsuniecia);
    }
}

void dodajOb(lista *head){
    lista *current=head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next=malloc(sizeof(lista));
    current->next->zycia=rand()%3+1;
    current->next->x=0;
    current->next->y=0;
    current->next->sila=rand()%4;
    current->next->next=NULL;
}


