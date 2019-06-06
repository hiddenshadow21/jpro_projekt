typedef struct obiekt{
	int x;
	int y;
	int sila;
	struct obiekt *next;
}lista;

unsigned int rozmiar,maxSila,iloscOb,czasSymulacji,typPlanszy;

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
	fgets(linia,30,plik);
	sscanf(linia,"%s %d",name,&typPlanszy);
    printf("%s %d\n",name,typPlanszy);
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
	printf("Podaj tryb wyswietlania (1 lub 2):\n");
	printf("  ###\t  ###\n1)O#O\t2)3#6\n  O##\t  9##\n");
    scanf("%d",&typPlanszy);
    fprintf(plik,"rozmiar: %d\n",rozmiar);
    fprintf(plik,"MaksymalnaSila: %d\n",maxSila);
    fprintf(plik,"IloscObiektow: %d\n",iloscOb);
    fprintf(plik,"czasSymulacji: %d\n",czasSymulacji);
	fprintf(plik,"typPlanszy: %d\n",typPlanszy);
    fclose(plik);
}

void summary(lista *head){
    FILE *plik=fopen("wynik.txt","w");
    fprintf(plik,"Wynik po %d krokach:\n",czasSymulacji);
    fprintf(plik,"Ilosc zywych obiektow: %d\n",iloscOb);
    fprintf(plik,"Rozklad sil:\n");
    int delta = 2;
    int ilosc_przedzialow = maxSila/delta+1;
    int *ilosc_liczb= calloc(ilosc_przedzialow,sizeof(int));
    int i,j;
    lista *current;
    for(i=0;i<ilosc_przedzialow;i++){
        current=head;
        for(j=0;j<iloscOb;j++){

            if(current->sila >= (i*delta) && current->sila < ((i+1)*delta))
                ilosc_liczb[i]++;
                if(current->next != NULL) current=current->next;
        }
    }
    int szerokosc=60;
    double max=ilosc_liczb[0];
    for(i=0;i<ilosc_przedzialow;i++){
        if(max<ilosc_liczb[i])
            max=ilosc_liczb[i];
    }


    for(i=0;i<ilosc_przedzialow;i++){
        fprintf(plik,"(%3d, %3d)|",i*delta,(i+1)*delta);
        j=(int)(szerokosc*ilosc_liczb[i]/max);
        while(j>0){
            fprintf(plik,"*");
            j--;
        }
        fprintf(plik,"%d\n",ilosc_liczb[i]);
    }
    free(ilosc_liczb);
    fclose(plik);
    printf("Zapisano wynik do pliku.\n");
}
