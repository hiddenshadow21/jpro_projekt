#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct obiekt{
	int x;
	int y;
	int sila;
	struct obiekt *next;
}lista;

void losujObiekty();
void wypisz();
void ruch();
void symuluj();
void czyTaSamaPozycja();
void usun();
void dodajOb();
void delay();

int main(){
    srand(time(NULL));
	int rozmiar,iloscOb,maxSila;
	printf("Podaj rozmiar planszy:\n");
	scanf("%d",&rozmiar);
	char plansza[rozmiar][rozmiar];
	printf("Podaj maksymalna losowana sile:\n");
	scanf("%d",&maxSila);
	do{
		printf("Podaj poczatkowa iloscOb obiektow:\n");
		scanf("%d",&iloscOb);
		if(iloscOb>rozmiar*rozmiar) printf("ilosc obiektow nie moze przekraczac ilosci pol planszy!\n");
	}while(iloscOb>rozmiar*rozmiar);

	lista *obiekty=malloc(sizeof(lista));
	losujObiekty(&obiekty,iloscOb,rozmiar,plansza, maxSila);
	wypisz(rozmiar,plansza,obiekty); //plansza startowa
    puts("");
	symuluj(&obiekty,rozmiar,plansza,maxSila);

	return 0;
}

void losujObiekty(lista **head,int iloscOb, int rozmiar, char tab[][rozmiar], int maxSila){
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
		current->sila=rand()%4;
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

void symuluj(lista **head, int rozmiar, char tab[][rozmiar], int maxSila){
    int i;
    lista *current=*head;
    for(i=0;i<16;i++){
        while(current->next!=NULL){
            ruch(current, rozmiar);
            current=current->next;
        }
        delay(1);
        current=*head;
        wypisz(rozmiar,tab,*head);
        czyTaSamaPozycja(head, rozmiar, maxSila);
        puts("");
    }
}

void czyTaSamaPozycja(lista **head, int rozmiar, int maxSila){
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
                        dodajOb(*head, rozmiar, maxSila);
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

void dodajOb(lista *head, int rozmiar, int maxSila){
    lista *current=head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next=malloc(sizeof(lista));
    current->next->x=rand()%rozmiar;
    current->next->y=rand()%rozmiar;
    current->next->sila=rand()%maxSila;
    current->next->next=NULL;
}

void delay(unsigned int sekundy){
#ifdef _WIN32
    clock_t start=clock();
    while(clock() < start+sekundy*1000){;}
#else
    sleep(sekundy);
#endif
}
