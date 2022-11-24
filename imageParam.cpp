#include "imageParam.h"

imageParam::imageParam()
{

}

imageParam::~imageParam()
{

}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{

}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{

}

float imageParam::getXPosition(int scanline, int pixel)
{

}

float imageParam::getYPosition(int scanline, int pixel)
{

}

float imageParam::getElementPosition(int element)
{

}

int imageParam::getNumElement()
{

}

int imageParam::getNumSample()
{

}

int imageParam::getNumScanline() 
{

}

int imageParam::getNumPixel() 
{

}

void imageParam::deletePositionArray()
{

}









