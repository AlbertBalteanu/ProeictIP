#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

using namespace std;
int triunghi[] = {190,256,384,258,288,116,190,256,70,419,500,419,385,256};
int casa[] = {190,256,384,258,288,116,190,256,190,419,385,419,385,256};
void drawpoly( int number, int *polypoints );
int main()
{
     initwindow(600,600);
    // circle(250,250,100);
    drawpoly(7,casa);
     getch();
     closegraph();

    return 0;
}
