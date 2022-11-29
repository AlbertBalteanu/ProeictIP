#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

using namespace std;

int trapez[] = {190,256, 384,258, 288,256, 190,256, 70,419, 500,419, 385,256};
int casa[] = {190,256, 384,258, 288,116, 190,256, 190,419, 385,419, 385,256};

void drawpoly( int number, int *polypoints );

int main()
{
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

    return 0;
}
