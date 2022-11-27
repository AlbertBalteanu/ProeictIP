#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

using namespace std;
int triunghi[] = {190,256, 384,258, 288,116, 190,256, 70,419, 500,419, 385,256};
int casa[] = {190,256, 384,258, 288,116, 190,256, 190,419, 385,419, 385,256};
void drawpoly( int number, int *polypoints );

void morph(int *img1, int *img2){
    drawpoly(7,img1);

}

int main()
{
     initwindow(600,600);

     drawpoly(7,casa);

     while(triunghi[8]!=casa[8]){ // while -> subprogram (cord img1, cord img 2)
        delay(600);
        clearviewport();
        casa[8]=casa[8]-30; //diferenta calculata in notepad -> algoritm de calcul
        casa[10]=casa[10]+28;
        drawpoly(7,casa);
     }

     getch();
     closegraph();

    return 0;
}
