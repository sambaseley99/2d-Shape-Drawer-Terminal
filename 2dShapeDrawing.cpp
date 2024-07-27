//Includes
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
#include <vector>

//Namespaces
using namespace std;

//Constants
const double CircleRadius = 55;
const int ResolutionY = 120;
const int ResolutionX = ResolutionY * 2;

//Arrays & Vectors
char displayArray[ResolutionX][ResolutionY];

struct pointStruct{ int pointXPos, pointYPos; };
vector<pointStruct> pointArray;

//Global Variables
int numberOfLines; 

//Method Declarations
void drawShape(int numPoints, bool allOrPerimeter);
void printDisplayArray();
void clearDisplayArray();
void chooseLineDraw (int x0, int y0, int x1, int y1);
void plotLineLow(int x0, int y0, int x1, int y1);
void plotLineHigh(int x0, int y0, int x1, int y1);


int main()
{

    /*
    for (int i = 0; i < 100; i++)
    {
        clearDisplayArray();
        drawShape(i);
        printDisplayArray();
        getchar();
    }
    */
    
    
    clearDisplayArray();

    cout << "How many points does the shape have?:";
    int numPoints;
    cin >> numPoints;

    cout << "Do you want points to draw lines to all other points(1) or just the perimeter(0)?:";
    bool allOrPerimeter;
    cin >> allOrPerimeter;

    drawShape(numPoints, allOrPerimeter);
    printDisplayArray();
    getchar();
    
    

    return 0;
}

void drawShape(int numPoints, bool allOrPerimeter)
{
    //find the angle betwen each point from the centre of the circle.
    double angleSpacingRad = (2*M_PI) / numPoints;

    //Find the point coords.
    double currentAngleRad = -M_PI / 2;

    for (int i = 0; i < numPoints; i++)
    {

        currentAngleRad = currentAngleRad + angleSpacingRad;

        //Due to letters being almost twice as tall as wide, the points need to be adjusted. This "stretches" the position so they are mathematically wrong, but look correct in terminal.
        double xPos = ((CircleRadius * 2) * cos(currentAngleRad)) + (ResolutionX / 2);
        double yPos = (CircleRadius * sin(currentAngleRad)) + (ResolutionY / 2);

        cout << "Point " << i << ": (" << fixed << setprecision(3) << xPos << "," << yPos << ")" << endl;

        //Set diplayArray 'pixel'
        int xPosRnd = round(xPos);
        int yPosRnd = round(yPos);
        int xPosRndLast, yPosRndLast, xPosRndFirst, yPosRndFirst;

        displayArray[xPosRnd][yPosRnd] = 'X';

        if (allOrPerimeter == true)
        {
            //Draw lines to all other existing points.
            for (int i = 0; i < pointArray.size(); i++)
            {
                chooseLineDraw(xPosRnd, yPosRnd, pointArray[i].pointXPos, pointArray[i].pointYPos);
                numberOfLines++;
            }
            
            //Add the point's position to the array for recall by later points.
            pointStruct currentPoint;
            currentPoint.pointXPos = xPosRnd;
            currentPoint.pointYPos = yPosRnd;
            pointArray.push_back(currentPoint);

        }
        else
        {
     
            //Save the first point's coords for recall by the last to make a full perimeter.
            if (i == 0)
            {
                xPosRndFirst = xPosRnd;
                yPosRndFirst = yPosRnd;
            }
            else
            {
                chooseLineDraw(xPosRnd, yPosRnd, xPosRndLast, yPosRndLast);
            }

            //Create a line from the last point to the first point.
            if (i == numPoints -1 && i != 0)
            {
                chooseLineDraw(xPosRndFirst, yPosRndFirst, xPosRnd, yPosRnd);
            }

            //Save current point coords for use by next point.
            xPosRndLast = xPosRnd;
            yPosRndLast = yPosRnd;

        }

    }

    //Display centre point.
    displayArray[ResolutionX / 2][ResolutionY / 2] = '0';

}

void printDisplayArray()
{

    cout << numberOfLines << endl;

    for (int y = 0; y < ResolutionY; y++)
    {
        for (int x = 0; x < ResolutionX; x++)
        {
            cout << displayArray[x][y];
        }

        cout << endl;
    }

}

void clearDisplayArray()
{
    //Clears the displayArray buffer before drawing the next points.
    for (int y = 0; y < ResolutionY; y++)
    {
        for (int x = 0; x < ResolutionX; x++)
        {
            displayArray[x][y] = ' ';
        }
    } 
}

void chooseLineDraw (int x0, int y0, int x1, int y1)
{
    //Changes line draw type and point order based on slope steepness and direction. Bresenham's Line.

    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1){ plotLineLow(x1, y1, x0, y0); }
        else { plotLineLow(x0, y0, x1, y1); } 
    }
    else
    {
        if (y0 > y1){ plotLineHigh(x1, y1, x0, y0);}
        else { plotLineHigh(x0, y0, x1, y1);}
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

        if (displayArray[x][y] == ' ')
        {
            displayArray[x][y] = '-';
        }

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

    int xi = 1;
    
    //find if x is reversed
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y < y1; y++)
    {

        if (displayArray[x][y] == ' ')
        {
            displayArray[x][y] = '-';
        }

        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
        {
            D = D + 2*dx;
        }
    }
}
