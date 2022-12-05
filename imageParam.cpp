#include "imageParam.h"

using namespace std;

imageParam::imageParam()
{
    // Initiallizing variables
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    elementPosition = genElementPosition();                                      // Calls genElementPosition function
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // Calls genScanlinePosition function with parameters
}

imageParam::~imageParam()
{
    deletePositionArray();
}

float *imageParam::genElementPosition()
{
    // Create an array containing the element location (in x-direction) of the ultrasound transducer
    float *elePosition = new float[numElement]; // Defines elePosition array with 128 elements
    for (int i = 0; i < numElement + 1; i++)
        elePosition[i] = (i - ((float(numElement) - 1.0) / 2.0)) * PITCH; // Solves for eleLocation at each element
    return elePosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    // Prompt user to input values for depth and numPixels
    float depth;
    cout << "Enter scanline depth (>0): ";
    cin >> depth;
    cout << "Enter the number of pixels: ";
    cin >> numPixel;

    // For x and y components of scanlinePosition, an array pointer of size numScanline is created
    float2 **scanlinePosition = new float2 *[numScanline];

    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel]; // Each element in scanineposition is assigned an array of size numPixel of type float2
        for (int k = 0; k < numPixel; k++)
        {
            // Stores desired values at the x and y scanlinePosition
            scanlinePosition[i][k].x = (i - ((numScanline - 1.0) / 2.0)) * PITCH;
            scanlinePosition[i][k].y = (depth / numPixel) * k;
        }
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    // Returns x value of scanlinePosition
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    // Returns y value of scanlinePosition
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    // Returns elemenPosition array
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    // Returns the value of numElement
    return numElement;
}

int imageParam::getNumSample()
{
    // Returns the value of numSample
    return numSample;
}

int imageParam::getNumScanline()
{
    // Returns the value of numScanline
    return numScanline;
}

int imageParam::getNumPixel()
{
    // Returns the value of numPixel
    return numPixel;
}

void imageParam::deletePositionArray()
{
    for (int i = 0; i < numPixel; i++)
        delete scanlinePosition[i]; // Releases the memory of each element
    // Releases the memory allocated to both variables below
    delete elementPosition;
    delete scanlinePosition;
}