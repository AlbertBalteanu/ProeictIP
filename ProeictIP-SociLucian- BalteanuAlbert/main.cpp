#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
ifstream fin ("input.txt");
ofstream afisecuatii ("afisecuatii.out");

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

bool apartine(punct P, dreptunghi D)
{
    return D.SS.x<=P.x && P.x<=D.DJ.x && D.SS.y<=P.y && P.y<=D.DJ.y;

}

struct buton
{
    dreptunghi D;
    int culoare;
    char text[20];
};

buton B[12];
int nrButoane=11;

void deseneazaMeniul()
{

    setcolor(WHITE);
    setfillstyle(SOLID_FILL,LIGHTGREEN);

    line (0,80 , 1400,80); //linia orizontala
    line (700,80, 700,700); // linia verticala

    int i=1;

    B[i].D.SS.x=40;
    B[i].D.SS.y=150;

    B[i].D.DJ.x=180;
    B[i].D.DJ.y=200;

    strcpy(B[i].text,"Alege imaginea 1");
    bar(B[i].D.SS.x, B[i].D.SS.y, B[i].D.DJ.x, B[i].D.DJ.y);

        outtextxy(B[i].D.SS.x+10,B[i].D.SS.y+15,B[i].text);
    setcolor(GREEN);
    rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);

     for (i=2; i<=4; i++)
    {
        setcolor(WHITE);

        B[i].D.SS.x=B[i-1].D.SS.x + 160;
        B[i].D.SS.y=150;

        B[i].D.DJ.x=B[i-1].D.DJ.x + 160;
        B[i].D.DJ.y=200;

        if(i==2)strcpy(B[i].text,"Alege imaginea 2");
            else if (i==3)strcpy(B[i].text,"START");
                else if (i==4) strcpy(B[i].text,"Iesire");

        bar(B[i].D.SS.x, B[i].D.SS.y, B[i].D.DJ.x, B[i].D.DJ.y);
        setbkcolor(BLACK);
            outtextxy(B[i].D.SS.x+10,B[i].D.SS.y+15,B[i].text);
        setcolor(GREEN);
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
    }

    setcolor(WHITE);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(564, 25, "MORPHING");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}

int butonAles()
{
    int i;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x=mousex();
        p.y=mousey();
        for (i=1; i<=nrButoane; i++)
            if (apartine(p,B[i].D))
                return i;
    }
    return 0;
}

//int trapez[] = {190,256, 384,256, 288,256, 190,256, 70,419, 500,419, 385,256};
//int casa[] = {190,256, 384,256, 288,116, 190,256, 190,419, 385,419, 385,256};
float trapez[15],casa[15];
int trapezint[15],casaint[15];

struct ecuatii
{
    float panta;
    float terlib; ///"termenul liber"
    int coefy;
} ec[8];

//void drawpoly( int number, int *polypoints );

void calculeazaEcuatia(int x1, int y1, int x2, int y2,float &panta, float &terlib, int &coefy, int &lafel)
{
    if(x1==x2&&y1==y2)
    {
        lafel=1;
    }
    else if(x1==x2)
    {
        coefy=0;
        panta=-1;
        terlib=x1;
        lafel=2;
    }
    else if(y1==y2)
    {
        panta=0;
        terlib=y1;
        coefy=-1;
        lafel=3;

    }
    else
    {
        lafel=4;
        panta=(y1-y2)/(x1-x2);
        terlib=y1-(panta*x1);
        coefy=1;
    }
}
float distante[8];
int laFel[8]; ///1=punctul nu se misca 2=pe verticala 3=pe orizontala 4=avem ecuatie cu toti coeficientii
int stdr[8];///-1 daca merge in st sau jos, "1" daca merge sus sau dreapta

void deseneazaimg1(){
    int i=5;
    B[5].D.SS.x=125;
    B[5].D.SS.y=250;

    B[5].D.DJ.x=225;
    B[5].D.DJ.y=350;


    setcolor(WHITE);
    rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);


}



int main()
{
    for(int i=0; i<14; i++)
        {
        fin>>trapez[i];
        trapezint[i]=trapez[i];
        }
    for(int i=0; i<14; i++)
        {
        fin>>casa[i];
        casaint[i]=casa[i];
        }

    initwindow(1400,700);
    deseneazaMeniul();

    for(int i=0; i<7; i++) ///for ul asta imi calculeaza mie o gramada de chestii n ai trb cu el
    {
        int lafel=0;
        calculeazaEcuatia(trapez[i*2],trapez[i*2+1],casa[i*2],casa[i*2+1],ec[i].panta,ec[i].terlib,ec[i].coefy,lafel);

        if(lafel==1)
        {
            afisecuatii<<"fara"<<'\n';
            laFel[i]=1;
        }
        else
        {
            afisecuatii<<"0="<<ec[i].coefy<<"y+"<<ec[i].panta<<"x+"<<ec[i].terlib<<endl;
            laFel[i]=lafel;
        }

        distante[i]=float(trapez[2*i]-casa[2*i])/100;
        if(laFel[i]==2)
            distante[i]=float(trapez[2*i+1]-casa[2*i+1])/100;
        if(distante[i]<0)distante[i]*=-1;
        cout<<distante[i]<<' ';

        if(laFel[i]==3||laFel[i]==4)
            if((casa[i*2]-trapez[i*2])>0)
                stdr[i]=1;
        if(laFel[i]==2)
            if((casa[i*2+1]-trapez[i*2+1])>0)
                stdr[i]=1;

    }

    /// ----------------------------------------------------------------------

    int comanda=0, butonul_apasat=0;
    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
        {
            comanda=butonul_apasat;
            cout<<"Comanda "<<comanda<<endl;

            if(butonul_apasat==1){
                deseneazaimg1();
            }

            if(butonul_apasat==3)
            {
                setviewport(700,80, 700,1400, 0);

                drawpoly(7,casaint);
                delay(700);

                /* while(trapez[8]!=casa[8])  // while -> subprogram (cord img1, cord img 2)
                 {
                     delay(500);
                     clearviewport();
                     casa[8]=casa[8]-30; //diferenta calculata in notepad -> algoritm de calcul
                     casa[10]=casa[10]+28;
                     casa[5]=casa[5]+35;
                     drawpoly(7,casa);
                 } */
                 ///MERGE!!!!! bag pl in el algoritm e ora 3 dimineata nb

                for(int i=1; i<=100; i++)
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(2,2,698,698);
                    for(int j=0; j<7; j++)
                    {
                        if(stdr[j]!=1)
                        {
                            if(laFel[j]==2)
                                casa[j*2+1]=casa[j*2+1]+distante[j];
                            if(laFel[j]==3)
                                casa[j*2]=casa[j*2]+distante[j];
                            if(laFel[j]==4)
                            {
                                casa[j*2]=casa[j*2]+distante[j];
                                casa[j*2+1]=casa[j*2]*ec[j].panta+ec[j].terlib;
                            }
                        }
                        else
                        {
                            if(laFel[j]==2)
                                casa[j*2+1]=casa[j*2+1]-distante[j];
                            if(laFel[j]==3)
                                casa[j*2]=casa[j*2]-distante[j];
                            if(laFel[j]==4)
                            {
                                casa[j*2]=casa[j*2]-distante[j];
                                casa[j*2+1]=casa[j*2]*ec[j].panta+ec[j].terlib;
                            }
                        }
                    }
                    for(int k=0;k<15;k++)
                        casaint[k]=casa[k];
                    drawpoly(7,casaint);
                    delay(1);
                }
                clearviewport();
                drawpoly(7,trapezint);
            }
        }
    }
    while (comanda!=4);
    //getch();
    closegraph();
    return 0;
}
/*
Albert:
ce mai am de facut:
trebuie sa bag tot algoritmul de morphing intr o functie
sa folosesc structura punct in loc de inlantuirea vectorului, totusi nu cred pot pt ca drawpoly foloseste vector ca sa construiasca linia
sa fie imaginile formate din mai multe linii poligonale
sa se poata morfa din oricare imagine in oricare alta imagine din cele 3 (asata trebuie vazut si cu partea de frontend)
*/
