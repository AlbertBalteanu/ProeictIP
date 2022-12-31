#include <iostream>
//#include <winbgim.h>
#include <graphics.h>
//#include <math.h>
//#include <conio.h>
//#include <stdlib.h>
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
buton B[20];
int nrButoane=16;

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


void deseneazaMeniul()      /// -----------MENIUL------------
{
    readimagefile("bkr.gif",0, 0,1400,700);
    setcolor(WHITE);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(564, 25, "MORPHING");

    line (0,80, 1400,80);  //linia orizontala

    int i=1;
    int nivel=200;

    B[i].D.SS.x=125;
    B[i].D.SS.y=nivel;

    B[i].D.DJ.x=425;
    B[i].D.DJ.y=nivel+70;

    for (i=2; i<=6; i++)
    {
        setcolor(WHITE);
        if(i==4) // schimbarea de nivel dupa 3 butoane
        {
            nivel=320;
            B[i].D.SS.x=125;
            B[i].D.SS.y=nivel;

            B[i].D.DJ.x=425;
            B[i].D.DJ.y=nivel+70;
        }
        else
        {
            B[i].D.SS.x=B[i-1].D.SS.x + 425;
            B[i].D.SS.y=nivel;

            B[i].D.DJ.x=B[i-1].D.DJ.x + 425;
            B[i].D.DJ.y=nivel+70;
        }
    }

    readimagefile("alege1.gif",B[1].D.SS.x, B[1].D.SS.y,B[1].D.DJ.x,B[1].D.DJ.y);
    readimagefile("alege2.gif",B[2].D.SS.x, B[2].D.SS.y,B[2].D.DJ.x,B[2].D.DJ.y);
    readimagefile("start.gif",B[3].D.SS.x, B[3].D.SS.y,B[3].D.DJ.x,B[3].D.DJ.y);
    readimagefile("deseneaza1.gif",B[4].D.SS.x, B[4].D.SS.y,B[4].D.DJ.x,B[4].D.DJ.y);
    readimagefile("deseneaza2.gif",B[5].D.SS.x, B[5].D.SS.y,B[5].D.DJ.x,B[5].D.DJ.y);
    readimagefile("iesire.gif",B[6].D.SS.x, B[6].D.SS.y,B[6].D.DJ.x,B[6].D.DJ.y);

    setcolor(WHITE);

}

void deseneazaBack()      /// -----------BUTONUL BACK------------
{
    B[7].D.SS.x=2;
    B[7].D.SS.y=2;

    B[7].D.DJ.x=202;
    B[7].D.DJ.y=62;
    readimagefile("inapoi.gif",B[7].D.SS.x, B[7].D.SS.y,B[7].D.DJ.x,B[7].D.DJ.y);
}

void deseneazaMBack()     /// -----------BUTONUL MORPH BACK------------
{
    B[16].D.SS.x=1170;
    B[16].D.SS.y=5;

    B[16].D.DJ.x=1395;
    B[16].D.DJ.y=65;
    readimagefile("morphback.gif",1170,5,1395,65);
}

void blocimg()   /// ----------BLOCARE BUTOANELOR------------
{
    int j;
    for(j=8; j<=16; j++)
    {
        B[j].D.SS.x=0;
        B[j].D.SS.y=0;

        B[j].D.DJ.x=0;
        B[j].D.DJ.y=0;
    }
}
void blocbut()
{
    int j;
    for(j=1; j<=6; j++)
    {
        B[j].D.SS.x=0;
        B[j].D.SS.y=0;

        B[j].D.DJ.x=0;
        B[j].D.DJ.y=0;
    }
}//butoanele din meniu puteau fi apasate din meniul cu poze si invers

void deseneazaPoze()     /// -----------MENIUL PENTRU ALES IMAGINI------------
{
    blocbut();
    initwindow(1400,700);
    readimagefile("bkr.gif",0, 0,1400,700);
    setcolor(WHITE);
    deseneazaBack();

    int i=8; //primul buton imagine
    int niv=75;

    B[i].D.SS.x=75;
    B[i].D.SS.y=niv;

    B[i].D.DJ.x=75+250;
    B[i].D.DJ.y=niv+250; //300 este latura patratului

    rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);//creeaza primul patrat/buton imagine ca referinta

    readimagefile("poza1.gif",B[i].D.SS.x+1, B[i].D.SS.y+1,B[i].D.DJ.x-1,B[i].D.DJ.y-1); /// POZAA


    for(i=9; i<=15; i++)
    {
        if(i==12) // schimbarea de nivel dupa 4 butoane imagine
        {
            niv=375;
            B[i].D.SS.x=75;
            B[i].D.SS.y=niv;

            B[i].D.DJ.x=75+250;
            B[i].D.DJ.y=niv+250;
        }
        else
        {
            B[i].D.SS.x=B[i-1].D.SS.x + 333 ;
            B[i].D.SS.y=niv;

            B[i].D.DJ.x=B[i-1].D.DJ.x + 333;
            B[i].D.DJ.y=niv+250;
        }

        rectangle(B[i].D.SS.x, B[i].D.SS.y,B[i].D.DJ.x,B[i].D.DJ.y);

    } // creeaza restul butoanelor imagini

    readimagefile("poza2.gif",B[9].D.SS.x+1, B[9].D.SS.y+1,B[9].D.DJ.x-1,B[9].D.DJ.y-1);
    readimagefile("poza3.gif",B[10].D.SS.x+1, B[10].D.SS.y+1,B[10].D.DJ.x-1,B[10].D.DJ.y-1);
    readimagefile("poza4.gif",B[11].D.SS.x+1, B[11].D.SS.y+1,B[11].D.DJ.x-1,B[11].D.DJ.y-1);
    readimagefile("poza5.gif",B[12].D.SS.x+1, B[12].D.SS.y+1,B[12].D.DJ.x-1,B[12].D.DJ.y-1);
    readimagefile("poza6.gif",B[13].D.SS.x+1, B[13].D.SS.y+1,B[13].D.DJ.x-1,B[13].D.DJ.y-1);
    readimagefile("poza7.gif",B[14].D.SS.x+1, B[14].D.SS.y+1,B[14].D.DJ.x-1,B[14].D.DJ.y-1);
    readimagefile("poza8.gif",B[15].D.SS.x+1, B[15].D.SS.y+1,B[15].D.DJ.x-1,B[15].D.DJ.y-1);

}

float img[11][50];
int imgint[11][50];

void calculeazaEcuatia(int x1, int y1, int x2, int y2,float &panta, float &terlib, int &coefy, int &lafel) /// -----------ECUATIILE FOLOSITE------------
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

int prev1=0;
int prev2=0;

void morph(float a[],float b[],int aint[], int bint[],int n)  /// -----------CALCULAREA SI AFISAREA TRECERII DE LA O IMAGINE LA ALTA------------
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
        afisecuatii<<" dis"<<i+1<<":"<<distante[i]<<'\n';

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
        // cout<<" stdr:"<<stdr[i]<<' '<<" susjos:"<<susjos[i];
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
            if(laFel[j]==2)
            {
                if(susjos[j]>0)
                    aux[j*2+1]=aux[j*2+1]-distante[j];
                else
                    aux[j*2+1]=aux[j*2+1]+distante[j];
            }
            if(laFel[j]==3)
            {
                if(stdr[j]>0)
                    aux[j*2]=aux[j*2]+distante[j];
                else
                    aux[j*2]=aux[j*2]-distante[j];
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
        //bar(2,2,698,698);
        clearviewport();
        drawpoly(n,auxint);
        delay(10);
    }
    clearviewport();
    drawpoly(n,bint); //-> asa era inainte sa ma bag eu (in loc de if else )
    // if(prev2!=15)drawpoly(n,bint); //  cand e nike face cu un pas mai putin gen
    //  else drawpoly(n,auxint);
}
void deseneazaImaginea(int a[],float floata[]) ///-------------------------------DESENEAZA IMAGINEA----------------------------
{   int X=0,Y=0,i=0;
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN)==1)
            {
                getmouseclick(WM_LBUTTONDOWN,X,Y);
                a[0]=X;
                a[1]=Y;
                break;
            }
    a[48]=a[0];
    a[49]=a[1];
    line(X,Y,X+1,Y+1);
    while(1)
            if(ismouseclick(WM_LBUTTONDOWN)==1)
            {
                getmouseclick(WM_LBUTTONDOWN,X,Y);
                a[2]=X;
                a[3]=Y;
                break;
            }
            clearviewport();
        line(a[0],a[1],a[2],a[3]);
    for(i=2; i<24; i++)
    {
        while(1)
            if(ismouseclick(WM_LBUTTONDOWN)==1)
            {
                getmouseclick(WM_LBUTTONDOWN,X,Y);
                a[2*i]=X;
                a[2*i+1]=Y;
                break;
            }
        line(a[i*2-2],a[i*2-1],a[i*2],a[i*2+1]);
    }
    line(a[i*2-2],a[i*2-1],a[i*2],a[i*2+1]);
    for(i=0;i<50;i++)
        floata[i]=a[i];
  //  getch();
}

int main()          /// -------------------------------------MAIN-------------------------------------------------
{
    int enableimg1=0;//pt alegerea img1 dupa selectarea butonului 1
    int enableimg2=0;//pt alegerea img2 dupa selectarea butonului 2

    initwindow(1400,700);
    deseneazaMeniul();

    /// ---------------------------------------------------------------------

    for(int i=1; i<=8; i++) /// PANA LA 10, 9 SI 10 FIIND IMAGINILE DESENATE
        for(int j=0; j<50; j++)
        {
            fin>>img[i][j];
            imgint[i][j]=img[i][j];
        }

    /// ----------------------------------------------------------------------

    int comanda=0, butonul_apasat=0;
    int imag=0; // folosit doar ca prescurtare pt butonul_apasat in cazul imaginilor
    int mback1=0;
    int mback2=0;

    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
        {
            comanda=butonul_apasat;
            cout<<"Comanda "<<comanda<<endl; // retine comenzile folosite in compiler

            if(butonul_apasat==1 )
            {
                deseneazaPoze();
                enableimg1=1;
                enableimg2=0;

                setcolor(WHITE);
            }

            if(butonul_apasat==2 )
            {
                deseneazaPoze();
                enableimg1=0;
                enableimg2=1;

                setcolor(WHITE);
            }

            if(butonul_apasat==3 && (prev1!=0 && prev2!=0))
            {
                initwindow(1400,700);
                setviewport(350,50, 1400,700, 0);
                setcolor(WHITE);
                ///---------
                morph(img[prev1-7],img[prev2-7],imgint[prev1-7],imgint[prev2-7],25);
                ///---------
                setviewport(0,0,1400,700,0);
                enableimg1=0;
                enableimg2=0;
                deseneazaBack();
                deseneazaMBack();

                mback1=prev1;
                prev1=0;
                mback2=prev2;
                prev2=0;
            }
            if(butonul_apasat==16)  // butonul morphback -- merge repetat (mai putin la nike)
            {
                prev1=mback2;
                prev2=mback1;

                clearviewport();
                setviewport(350,50, 1400,700, 0);
                setcolor(WHITE);
                ///---------
                morph(img[prev1-7],img[prev2-7],imgint[prev1-7],imgint[prev2-7],25);
                ///---------
                setviewport(0,0,1400,700,0);
                enableimg1=0;
                enableimg2=0;
                deseneazaBack();
                deseneazaMBack();
                mback1=prev1;
                prev1=0;
                mback2=prev2;
                prev2=0;
            }

            if(butonul_apasat==7)  // butonul back
            {
                closegraph();
                initwindow(1400,700);
                deseneazaMeniul();
                blocimg();
            }

            if(butonul_apasat > 7 && butonul_apasat!=16)  //butoanele imagine
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
                }//prev2 ramane valoarea imaginiei 2 aleasa

            }

            if(butonul_apasat==4)
            {
                initwindow(700,620);
                deseneazaImaginea(imgint[9],img[9]);
                //void deseneazaImaginea(1) (cu un for de la 1 la 25 pentru a marca punctele (salvate intr un vector)si afisarea imaginii desenate)
                //dupa ce creezi vectorul il implementez eu in start, tre sa modific cv la butoane
                deseneazaBack();
                  //  getch();
                prev1=16;

            }

            if(butonul_apasat==5)
            {
                initwindow(700,620);
                deseneazaImaginea(imgint[10],img[10]);
                //deseneazaImaginea(2)
                deseneazaBack();
                  //  getch();
                prev2=17;


            }

        }
    }
    while (comanda!=6);
    //getch();
    closegraph();
    return 0;
}
