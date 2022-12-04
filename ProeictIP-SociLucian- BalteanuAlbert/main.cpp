#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

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
        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);
        bar(B[i].D.SS.x, B[i].D.SS.y+100, B[i].D.DJ.x, B[i].D.SS.y);
        setbkcolor(BLACK);
        outtextxy(B[i].D.SS.x+25,B[i].D.SS.y+10,B[i].text);
    }

    outtextxy(300, 50, "MORPHING");
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

int trapez[] = {190,256, 384,258, 288,256, 190,256, 70,419, 500,419, 385,256};
int casa[] = {190,256, 384,258, 288,116, 190,256, 190,419, 385,419, 385,256};

void drawpoly( int number, int *polypoints );

int main()
{
    initwindow(800,600);
    deseneazaMeniul();

    int comanda, butonul_apasat;
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
    // getch();
    closegraph();
    return 0;
}
