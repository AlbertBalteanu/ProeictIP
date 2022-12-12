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

buton B[15];
int nrButoane=12;

void deseneazaMeniul()
{
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,LIGHTGREEN);

    line (0,80, 1400,80);  //linia orizontala
    line (700,80, 700,700); // linia verticala
    line (0,250, 700,250);

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

    i=5; //primul buton imagine
    int nivel=300;

    B[i].D.SS.x=13;
    B[i].D.SS.y=nivel;

    B[i].D.DJ.x=13+150;
    B[i].D.DJ.y=nivel+150; //150 este latura patratului

    rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);//creeaza primul patrat/buton imagine ca referinta

    readimagefile("poza1.jpeg",B[i].D.SS.x+1, B[i].D.SS.y+1,B[i].D.DJ.x-1,B[i].D.DJ.y-1); /// POZAA


    for(i=6; i<=nrButoane; i++)
    {
        if(i==9) // schimbarea de nivel dupa 4 butoane imagine
        {
            nivel=500;
            B[i].D.SS.x=13;
            B[i].D.SS.y=nivel;

            B[i].D.DJ.x=13+150;
            B[i].D.DJ.y=nivel+150;
        }
        else
        {
            B[i].D.SS.x=B[i-1].D.SS.x + 175 ;
            B[i].D.SS.y=nivel;

            B[i].D.DJ.x=B[i-1].D.DJ.x + 175;
            B[i].D.DJ.y=nivel+150;
        }

        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);

    } // creeaza restul butoanelor imagini


    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(564, 25, "MORPHING");

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

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

float img[8][50];
int imgint[8][50];

void calculeazaEcuatia(int x1, int y1, int x2, int y2,float &panta, float &terlib, int &coefy, int &lafel)
{
    if(x1==x2&&y1==y2)
    {
        lafel=1;
        afisecuatii<<"fara"<<endl;
    }
    else
    {
        if(x1==x2)
        {
            coefy=0;
            panta=1;
            terlib=x1;
            lafel=2;
            afisecuatii<<"coefy "<<coefy<<" panta "<<panta<<" terlib "<<terlib<<endl;
        }
        else
        {
            if(y1==y2)
            {
                panta=0;
                terlib=y1;
                coefy=1;
                lafel=3;
                afisecuatii<<"coefy "<<coefy<<" panta "<<panta<<" terlib "<<terlib<<endl;

            }
            else
            {
                lafel=4;
                panta=(((float)y2-(float)y1)/((float)x1-(float)x2));
                terlib=(-(float)y1-(panta*(float)x1));
                coefy=1;
                afisecuatii<<"coefy "<<coefy<<" panta "<<panta<<" terlib "<<terlib<<endl;
            }
        }
    }
}


void morph(float a[],float b[],int aint[], int bint[],int n)
{
    int laFel[n]= {0}; ///1=punctul nu se misca 2=pe verticala 3=pe orizontala 4=avem ecuatie cu toti coeficientii

    int stdr[n]= {0},susjos[n]= {0}; ///"0" daca merge in st sau jos, "1" daca merge sus sau dreapta

    float distante[n]= {0};

    struct ecuatii
    {
        float panta;
        float terlib; ///"termenul liber"
        int coefy;
    } ec[25]= {0};

    for(int i=0; i<n; i++) ///am mutat forul asta in fucntie
    {
        int lafel=0;
        calculeazaEcuatia(a[i*2],a[i*2+1],b[i*2],b[i*2+1],ec[i].panta,ec[i].terlib,ec[i].coefy,lafel);

        laFel[i]=lafel;

        distante[i]=float(a[2*i]-b[2*i])/(float)100;

        if(laFel[i]==2)
            distante[i]=float(a[2*i+1]-b[2*i+1])/(float)100;

        if(distante[i]<0)distante[i]*=-1;
        cout<<" dis:"<<distante[i]<<' ';

        if(laFel[i]==2)
            if((b[i*2+1]-a[i*2+1])<0)
                susjos[i]=1;

        if(laFel[i]==3)
            if((b[i*2]-a[i*2])>0)
                stdr[i]=1;

        if(laFel[i]==4)
        {
            if((b[i*2+1]-a[i*2+1])<0)
                susjos[i]=1;
            if((b[i*2]-a[i*2])>0)
                stdr[i]=1;
        }
        cout<<" stdr:"<<stdr[i]<<' '<<" susjos:"<<susjos[i];
    }

    float aux[2*n]= {0};
    int auxint[2*n]= {0};
    for(int i=0; i<2*n; i++)
        aux[i]=a[i];
    drawpoly(n,aint);
    delay(700);

    for(int i=1; i<=100; i++)
    {
        setfillstyle(SOLID_FILL,BLACK);
        for(int j=0; j<n; j++)
        {
            if(laFel[i]==2)
            {
                if(susjos[i]>1)
                    aux[j*2+1]=aux[j*2+1]-distante[j];
                else
                    aux[j*2+1]=aux[j*2+1]+distante[j];
            }
            if(laFel[i]==3)
            {
                if(stdr[i]>1)
                    aux[j*2+1]=aux[j*2+1]+distante[j];
                else
                    aux[j*2+1]=aux[j*2+1]-distante[j];
            }
            if(laFel[j]==4)
            {
                if(stdr[j]>0)
                {
                    aux[j*2]=aux[j*2]+distante[j];
                    aux[j*2+1]=-(ec[j].panta*aux[j*2]+ec[j].terlib);
                }
                else
                {
                    aux[j*2]=aux[j*2]-distante[j];
                    aux[j*2+1]=-(ec[j].panta*aux[j*2]+ec[j].terlib);
                }
            }
        }
        for(int k=0; k<2*n; k++)
            auxint[k]=(int)aux[k];
        bar(2,2,698,698);
        drawpoly(n,auxint);
        delay(10);


    }
    bar(2,2,698,698);
    drawpoly(n,bint);
}
void culoareoriginala(int c)  // folosit pt aducere butoanele 1 si 2 la normal
{
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    bar(B[c].D.SS.x, B[c].D.SS.y, B[c].D.DJ.x, B[c].D.DJ.y);
    setcolor(WHITE);
    setbkcolor(BLACK);
    outtextxy(B[c].D.SS.x+10,B[c].D.SS.y+15,B[c].text);
    setcolor(GREEN);
    rectangle(B[c].D.SS.x, B[c].D.SS.y,B[c].D.DJ.x,B[c].D.DJ.y);
    setcolor(WHITE);
}


int main()
{
    int enableimg1=0;//pt alegerea img1 dupa selectarea butonului 1
    int enableimg2=0;//pt alegerea img2 dupa selectarea butonului 2

    initwindow(1400,700);
    deseneazaMeniul();
    for(int i=1; i<=8; i++)
        for(int j=0; j<50; j++)
        {
            fin>>img[i][j];
            imgint[i][j]=img[i][j];
        }

    /// ----------------------------------------------------------------------

    int comanda=0, butonul_apasat=0;
    int prev1=0;
    int prev2=0;
    int imag=0; // folosit doar ca prescurtare pt butonul_apasat in cazu 1 si 2
    int lockbut=0;

    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
        {
            comanda=butonul_apasat;
            cout<<"Comanda "<<comanda<<endl; // retine comenzile folosite in compiler

            if(butonul_apasat==1 && lockbut==0)
            {
                enableimg1=1;
                enableimg2=0;

                setcolor(WHITE);

                setfillstyle(SOLID_FILL,RED);
                bar(B[1].D.SS.x, B[1].D.SS.y, B[1].D.DJ.x, B[1].D.DJ.y);
                setbkcolor(BLACK);
                outtextxy(B[1].D.SS.x+10,B[1].D.SS.y+15,B[1].text);

                culoareoriginala(2);
            }

            if(butonul_apasat==2 && lockbut==0)
            {
                enableimg1=0;
                enableimg2=1;

                setcolor(WHITE);

                setfillstyle(SOLID_FILL,GREEN);
                bar(B[2].D.SS.x, B[2].D.SS.y, B[2].D.DJ.x, B[2].D.DJ.y);
                setbkcolor(BLACK);
                outtextxy(B[2].D.SS.x+10,B[2].D.SS.y+15,B[2].text);

                culoareoriginala(1);
            }

            if(butonul_apasat==3 && lockbut==0) /// ALG TREBUIE INLOCUIT CU UN VOID START(IMG1, IMG2) !!! PLUS ATENTIE LA CAZUL IN CARE NU AU FOST ALESE IMG INCA (PREV1 SAU PREV2 = 0)
            {
                culoareoriginala(1);
                culoareoriginala(2);

                setviewport(700,80, 700,1400, 0);
                setcolor(WHITE);
                lockbut=1;
                ///---------
                morph(img[prev1-4],img[prev2-4],imgint[prev1-4],imgint[prev2-4],25);
                ///---------
                enableimg1=0;
                enableimg2=0;
            }

            if(butonul_apasat > 3)  //schimbarea culorii butonului imagine selectat si retinerea in prev1 si prev 2
            {

                if(enableimg1==1 && butonul_apasat!=prev2)
                {
                    if(prev1!=0)
                    {
                        setcolor(WHITE);
                        rectangle(B[prev1].D.SS.x, B[prev1].D.SS.y, B[prev1].D.DJ.x, B[prev1].D.DJ.y);
                    }
                    setcolor(RED);
                    imag=butonul_apasat;
                    rectangle(B[imag].D.SS.x, B[imag].D.SS.y, B[imag].D.DJ.x, B[imag].D.DJ.y);
                    prev1=imag;
                }//prev1 ramane valoarea imaginei 1 aleasa

                if(enableimg2==1 && butonul_apasat!=prev1)
                {
                    if(prev2!=0)
                    {
                        setcolor(WHITE);
                        rectangle(B[prev2].D.SS.x, B[prev2].D.SS.y, B[prev2].D.DJ.x, B[prev2].D.DJ.y);
                    }
                    setcolor(GREEN);
                    imag=butonul_apasat;
                    rectangle(B[imag].D.SS.x, B[imag].D.SS.y, B[imag].D.DJ.x, B[imag].D.DJ.y);
                    prev2=imag;
                }//prev2 ramane valoarea imaginiei 2 aleasa --. de folosir in functie start(prev1, prev2)

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
sa se poata morfa din oricare imagine in oricare alta imagine din cele 3 (asata trebuie vazut si cu partea de frontend)
*/
