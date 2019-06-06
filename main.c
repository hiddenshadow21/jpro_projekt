#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "cfg.h"

void losujObiekty();
void wypisz();
void ruch();
void symuluj();
void czyTaSamaPozycja();
void usun();
void dodajOb();
void delay();

int main(){
    makecfg();
    readcfg();
    srand(time(NULL));
    char plansza[rozmiar][rozmiar];
	lista *obiekty=malloc(sizeof(lista));
	losujObiekty(&obiekty,plansza);
	wypisz(plansza,obiekty); //plansza startowa
    puts("");
	symuluj(&obiekty,plansza);
	summary(obiekty);
	return 0;
}

void losujObiekty(lista **head,char tab[][rozmiar]){
	int i,j,x,y;
	for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            tab[i][j]='#';
        }
	}
	lista *current=*head;
	current->sila=rand()%maxSila;
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
		current->sila=rand()%maxSila;
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

void wypisz(char tab[][rozmiar], lista *head){
    int i,j;
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    lista *current=head;
    for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
                tab[i][j]='#';
        }
    }
    iloscOb=0;
    while(current->next!=NULL){
        tab[current->y][current->x]='O';
        iloscOb++;
        current=current->next;
    }
    for(i=0;i<rozmiar;i++){
        for(j=0;j<rozmiar;j++){
            printf("%c ",tab[i][j]);
        }
        puts("");
    }
}

void ruch(lista *current){
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

void symuluj(lista **head, char tab[][rozmiar]){
    int i;
    lista *current=*head;
    for(i=0;i<czasSymulacji;i++){
        current=*head;
        while(current->next!=NULL){
            ruch(current);
            current=current->next;
        }
        wypisz(tab,*head);
        czyTaSamaPozycja(head);
        puts("");
        delay(1);
    }
}

void czyTaSamaPozycja(lista **head){
    lista *obj1=*head, *obj2;
    while(obj1->next!=NULL){
            obj2=obj1->next;
            while(obj2){
                if(obj1->x == obj2->x && obj1->y == obj2->y){
                    if(obj1->sila > obj2->sila && obj2->next!=NULL){
                        usun(head,obj2);
                    }
                    else if(obj1->sila < obj2->sila){
                        usun(head,obj1);
                        break;
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
    if(current==doUsuniecia){
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
    iloscOb=0;
    lista *current=head;
    while(current->next!=NULL){
        current=current->next;
        iloscOb++;
    }
    if(iloscOb<rozmiar*rozmiar-2){
        current->next=malloc(sizeof(lista));
        current->next->x=rand()%rozmiar;
        current->next->y=rand()%rozmiar;
        current->next->sila=rand()%maxSila+1;
        current->next->next=NULL;
    }
}

void delay(unsigned int sekundy){
#ifdef _WIN32
    clock_t start=clock();
    while(clock() < start+sekundy*1000){;}
#else
    sleep(sekundy);
#endif
}
