typedef struct obiekt{
	int x;
	int y;
	int sila;
	struct obiekt *next;
}lista;

unsigned int rozmiar,maxSila,iloscOb,czasSymulacji;

void readcfg(){
    FILE *plik;
    plik=fopen("cfg.txt","r");
    char linia[30],name[25];

    fgets(linia,30,plik);
    sscanf(linia,"%s %d",name,&rozmiar);
    printf("%s %d\n",name,rozmiar);
    fgets(linia,30,plik);
    sscanf(linia,"%s %d",name,&maxSila);
    printf("%s %d\n",name,maxSila);
    fgets(linia,30,plik);
    sscanf(linia,"%s %d",name,&iloscOb);
    printf("%s %d\n",name,iloscOb);
    fgets(linia,30,plik);
    sscanf(linia,"%s %d",name,&czasSymulacji);
    printf("%s %d\n",name,czasSymulacji);
    fclose(plik);
}


void makecfg(){
    FILE *plik;
    plik=fopen("cfg.txt","w");
    printf("Podaj rozmiar planszy kwadratowej:\n");
    scanf("%d",&rozmiar);
    printf("Podaj maksymalna sile:\n");
    scanf("%d",&maxSila);
    printf("Podaj startowa ilosc obiektow:\n");
    scanf("%d",&iloscOb);
    while(iloscOb>rozmiar*rozmiar-1){
        printf("Ilosc obiektow nie moze przekraczac pol planszy!\nPodaj ponownie ilosc obiektow:\n");
        scanf("%d",&iloscOb);
    }
    printf("Podaj ilosc krokow symulacji:\n");
    scanf("%d",&czasSymulacji);
    fprintf(plik,"rozmiar: %d\n",rozmiar);
    fprintf(plik,"MaksymalnaSila: %d\n",maxSila);
    fprintf(plik,"IloscObiektow: %d\n",iloscOb);
    fprintf(plik,"czasSymulacji: %d\n",czasSymulacji);
    fclose(plik);
}

void summary(lista *head){
    FILE *plik=fopen("wynik.txt","w");
    fprintf(plik,"Wynik po %d krokach:\n",czasSymulacji);
    fprintf(plik,"Ilosc ¿ywych obiektow: %d\n",iloscOb);
    fprintf(plik,"Rozklad si³:\n");
}
