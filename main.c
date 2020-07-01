
//         MUSTAFA TERZI     //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bilgi
{
    char oda_sayisi[20];
    char mkare[20];
    char esya[20];
    int fiyat;
}Bilgi;

typedef struct konut
{
    char tip[20];
    char tur[20];
    int ilan_no;
    struct bilgi *bil;
    struct konut *sonraki;
}Konut;

Konut *ilk=NULL,*son,*gecici,*iter;

void yazdir();
void ara();
void sil();
void ekle();
void guncelle();

int main()
{
    ilk = NULL;
    son = NULL;
    gecici = NULL;

    FILE *dosya;
    dosya = fopen("emlak.txt","r");
    if(dosya == NULL)
    {
        printf("Dosya okumak icin acilamadi!");
        return -1;
    }

    while(!feof(dosya))
    {
        gecici = (Konut*)malloc(sizeof(Konut));
        gecici->bil=(Bilgi*)malloc(sizeof(Bilgi));
        fscanf(dosya,"%d %s %s %s %s %d %s",&gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,&gecici->bil->fiyat,gecici->bil->esya);
        if(ilk == NULL)
        {
            ilk = gecici;
            son = gecici;
            son->sonraki = NULL;
        }
        else
        {
            son->sonraki = gecici;
            son = gecici;
            son->sonraki = NULL;
        }
    }
    fclose(dosya);

   // printf("Veriler bagli listeye aktarildi\n");
   // getch();
    menu();

    return 0;
}
void menu()
{
    int secim;
    anaMenu:
    system("cls");
    printf("\n\n");
    printf("[1] .. Listeyi Yazdir\n");
    printf("[2] .. Listede Arama Yap\n");
    printf("[3] .. Listeden Veri Sil\n");
    printf("[4] .. Listeye Kayit Ekle\n");
    printf("[5] .. Listeyi Guncelle\n");
    printf("[6] .. Cikis\n");
    printf("\n\n");
    printf("Lutfen Secim Yapiniz:");
    scanf("%d",&secim);

    switch(secim)
    {
    case 1:
        yazdir();
        break;
    case 2:
        ara();
        break;
    case 3:
        sil();
        break;
    case 4:
        ekle();
        break;
    case 5:
        guncelle();
        break;
    case 6:
        exit(6);
    default:
        printf("\nYanlis Secim!!\n");
        getch();
        goto anaMenu;
    }
}

void yazdir()
{
    printf("\n\n");
    for(gecici=ilk;gecici!=NULL;gecici = gecici->sonraki)
    {
        printf("%d %s %s %s %s %d %s\n",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);
    }
    getch();
    menu();
}

void ara()
{
    printf("\n\n");
    int no;
    char ad[20];
    printf("Aranacak ilan no giriniz:");
    scanf("%d",&no);

    for(gecici = ilk; gecici != NULL; gecici = gecici->sonraki)
    {
        if(gecici->ilan_no == no)
        {
            printf("\nAranan kayit:");
            printf("%d %s %s %s %s %d %s",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);
        }
    }

    getch();
    menu();
}

void sil()
{
    int no;
    printf("\n\n");
    printf("Silinecek kaydin ilan no'sunu giriniz:");
    scanf("%d",&no);
    gecici = ilk;

    Konut *onceki;
    onceki = NULL;

    while(gecici != NULL)
    {
        if(gecici->ilan_no==no)
            break;
        onceki = gecici;
        gecici = gecici->sonraki;
    }
    if(gecici != NULL)
    {
        if(onceki == NULL)
        {
            if(ilk == son)
            {
                ilk=NULL;
                son=NULL;
            }
            else
                ilk = ilk->sonraki;
        }
        else
        {
            onceki->sonraki = gecici->sonraki;
            if(onceki->sonraki == NULL)
                son = onceki;

        }
    }

    else
        printf("Silmek istenilen veri listede bulunamadi!\n");

    printf("\nListenin son hali:\n");

    FILE *dosya;
    dosya = fopen("emlak.txt","w");
    if(dosya == NULL)
    {
        printf("Dosya yazilmak icin acilamadi!!\n");
        return -1;
    }

    for(gecici = ilk; gecici != NULL; gecici = gecici->sonraki)
    {
        fprintf(dosya,"%d %s %s %s %s %d %s\n",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);
    }
    fclose(dosya);
    yazdir();
    getch();
    menu();
}

void ekle()

{
    gecici=(Konut*) malloc(sizeof(Konut));
    gecici->bil=(Bilgi*)malloc(sizeof(Bilgi));

    printf("\n\n");

    printf("Ilan no'sunu giriniz : ");
    scanf("%d",&gecici->ilan_no);
    printf("Ilanin Tipini giriniz : ");
    scanf("%s",&gecici->tip);
    printf("Ilanin Tur'unu giriniz : ");
    scanf("%s",&gecici->tur);
    printf("Evin Oda sayisini giriniz : ");
    scanf("%s",&gecici->bil->oda_sayisi);
    printf("Evin Metre karasini giriniz : ");
    scanf("%s",&gecici->bil->mkare);
    printf("Evin fiyatini giriniz : ");
    scanf("%d",&gecici->bil->fiyat);
    printf("Evin Esya durumunu giriniz : ");
    scanf("%s",&gecici->bil->esya);

    if(ilk!=NULL)
    {
        gecici->sonraki=NULL;
        ilk = gecici;
    }
    else
    {
        iter = ilk;
        while(iter->sonraki!=NULL)
        {
            iter=iter->sonraki;
        }
        iter->sonraki = gecici;
    }



    FILE *dosya;
    dosya = fopen("emlak.txt","a");
    if(dosya == NULL)
    {
        printf("Dosya yazilmak icin acilamadi!!\n");
        return -1;
    }

    fprintf(dosya,"%d %s %s %s %s %d %s\n",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);

    fclose(dosya);
    main();
    menu();
}

void guncelle()
{
    int no;
    gecici=(Konut*)malloc(sizeof(Konut));
    gecici->bil=(Bilgi*)malloc(sizeof(Bilgi));
    printf("\n\n");
    printf("Guncelleme yapilacak evin ilan no'sunu giriniz : ");
    scanf("%d",&no);
    printf("\n\n");
    gecici=ilk;
    while(gecici!=NULL)
    {
        if(gecici->ilan_no==no)
    {
        printf("%d %s %s %s %s %d %s",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);
        printf("\nIlan no'sunu giriniz : ");
        scanf("%d",&gecici->ilan_no);
        printf("\nEvin tip'ini giriniz : ");
        scanf("%s",&gecici->tip);
        printf("\nEvin tur'unu giriniz : ");
        scanf("%s",&gecici->tur);
        printf("\nOda sayisini giriniz : ");
        scanf("%s",&gecici->bil->oda_sayisi);
        printf("\nMetre karesini giriniz : ");
        scanf("%s",&gecici->bil->mkare);
        printf("\nFiyat giriniz : ");
        scanf("%d",&gecici->bil->fiyat);
        printf("\nEsya durumunu giriniz : ");
        scanf("%s",&gecici->bil->esya);
        break;
    }
    gecici=gecici->sonraki;
    }

    FILE *dosya;
    dosya = fopen("emlak.txt","w");
    if(dosya == NULL)
    {
        printf("Dosya yazilmak icin acilamadi!!\n");
        return -1;
    }
    for(gecici = ilk; gecici != NULL; gecici = gecici->sonraki)
    {
        fprintf(dosya,"%d %s %s %s %s %d %s\n",gecici->ilan_no,gecici->tip,gecici->tur,gecici->bil->oda_sayisi,gecici->bil->mkare,gecici->bil->fiyat,gecici->bil->esya);
    }
    fclose(dosya);
    menu();
}


