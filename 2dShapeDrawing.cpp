#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

const double CircleRadius = 45;

char displayArray[100][100];

//int circleRadius = 25;

void debugFillBox();
void drawShape(int numPoints);
void clearDisplayArray ();
void lineDrawing(int x0, int y0, int x1, int y1);
float toDegrees(float Radians);
float toRadians(float Degrees);

int main()
{

    //debugFillBox();
    //getchar();

    clearDisplayArray();

    drawShape(8);
    getchar();

    return 0;
}

void drawShape(int numPoints)
{
    //find the angle betwen each point from the centre of the circle.
    double angleSpacingRad = (2*M_PI) / numPoints;

    //Find the point coords.
    double currentAngleRad = -M_PI;

    for (int i = 0; i < numPoints; i++)
    {
        currentAngleRad = currentAngleRad + angleSpacingRad;

        double xPos = CircleRadius * cos(currentAngleRad);
        double yPos = CircleRadius * sin(currentAngleRad);

        cout << "Point " << i << ": (" << fixed << setprecision(3) << xPos << "," << yPos << ")" << endl;

        //Set diplayArray 'pixel'
        int xPosRnd = (round(xPos) + 50)/2;
        int yPosRnd = round(yPos) + 50;

        displayArray[xPosRnd][yPosRnd] = 'X';
    }

    //Print displayArray
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            cout << displayArray[x][y];
        }

        cout << endl;
    }
    
 
}

float toDegrees(float Radians){return (Radians * (180 / M_PI));}

float toRadians(float Degrees){return (Degrees * (M_PI / 180));}

void debugFillBox()
{
 for (int i = 0; i < 100; i++)
   {
    for (int i = 0; i < 100; i++)
   {
    cout << "X";
   }
   cout << endl;
   }
}

void clearDisplayArray()
{
    //Clears the displayArray buffer before drawing the next points.
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            displayArray[x][y] = ' ';
        }
    } 
}

void plotLineLow(int x0, int y0, int x1, int y1)
{
    //Find difference in coord positions
    int dx = x1 - x0;
    int dy = y1 - y0;

    int yi = 1;
    
    //find if y is reversed
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {

        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D + 2*dy;
        }
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1)
{
    //Find difference in coord positions
    int dx = x1 - x0;
    int dy = y1 - y0;

    int yi = 1;
    
    //find if y is reversed
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {

        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D + 2*dy;
        }
    }
}
