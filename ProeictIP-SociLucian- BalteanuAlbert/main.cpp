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

buton B[6];
int nrButoane=2;
void deseneazaMeniul()
{

    setcolor(WHITE);
    setfillstyle(SOLID_FILL,LIGHTCYAN);
    int i;
    for (i=1; i<=nrButoane; i++)
    {
        B[i].D.SS.x=150*i;
        B[i].D.DJ.x=150*(i+1)-10;
        B[i].D.SS.y=150;
        B[i].D.DJ.y=250;
        switch(i)
        {
        case 1:
            strcpy(B[i].text,"Exemplu 1");
            break;
        case 2:
            strcpy(B[i].text,"Iesire");
            break;

        }
      //  rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        bar3d(B[i].D.SS.x, B[i].D.SS.y+100, B[i].D.DJ.x, B[i].D.SS.y,5,0);
        setbkcolor(BLACK);
        outtextxy(B[i].D.SS.x+40,B[i].D.SS.y+40,B[i].text);
    }

    outtextxy(364, 100, "MORPHING");
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

//int trapez[] = {190,256, 384,258, 288,256, 190,256, 70,419, 500,419, 385,256};
//int casa[] = {190,256, 384,258, 288,116, 190,256, 190,419, 385,419, 385,256};
int trapez[15],casa[15];
struct ecautii
{
    float panta;
    float terlib; ///"termenul liber"
}ec[8];
//void drawpoly( int number, int *polypoints );
void calculeazaEcuatia(int x1, int y1, int x2, int y2,float &panta, float &terlib)
{
    panta=(y1-y2)/(x1-x2);// impartire la 0
   // afisecuatii<<panta;
    terlib=y1-(panta*x1);
    afisecuatii<<"y="<<panta<<"x+"<<terlib;
}

int main()
{
    for(int i=0;i<14;i++)
        fin>>trapez[i];
    for(int i=0;i<14;i++)
        fin>>casa[i];
    initwindow(800,600);
    deseneazaMeniul();

   // for(int i=0;i<8;i++);
   int i=0;
        calculeazaEcuatia(trapez[i*2],trapez[i*2+1],casa[i*2],casa[i*2+1],ec[i].panta,ec[i].terlib);

    int comanda=0, butonul_apasat=0;
    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
            {
                comanda=butonul_apasat;
                cout<<"Comanda "<<comanda<<endl;

                if(butonul_apasat==1){
                    initwindow(600,600);

                    drawpoly(7,casa);
                    delay(1000);

                    while(trapez[8]!=casa[8]){ // while -> subprogram (cord img1, cord img 2)
                        delay(500);
                        clearviewport();
                        casa[8]=casa[8]-30; //diferenta calculata in notepad -> algoritm de calcul
                        casa[10]=casa[10]+28;
                        casa[5]=casa[5]+35;
                        drawpoly(7,casa);
                    }

                    getch();
                    closegraph();
                }
            }
    }
    while (comanda!=2);
    getch();
    closegraph();
    return 0;
}
