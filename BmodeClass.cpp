#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    // Initializing all variables
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    // Initializing variables based on the constructor parameters
    imparams = params;
    RFData = data;
    line = numline;

    scanline = createScanline(imparams->getNumPixel()); // Allocating memory for scanline
    beamform();                                         // Scanline beamforming
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // Release scanline array memory
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel]; // Allocating a 1D float array of size numPixel
    return mem;
}

void BmodeClass::beamform()
{
    // Initialize array variables
    float tForward[imparams->getNumPixel()];
    float tBackward[imparams->getNumPixel()][imparams->getNumElement()];
    float tTotal[imparams->getNumPixel()];
    int s[imparams->getNumPixel()][imparams->getNumElement()];

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        // Initialize pReal and pImag
        float pReal = 0;
        float pImag = 0;

        tForward[i] = (imparams->getYPosition(line, i)) / imparams->SOS; // Calculate tForward

        for (int k = 0; k < imparams->getNumElement(); k++)
        {
            // Calculates for tBackward and tTotal
            tBackward[i][k] = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS;
            tTotal[i] = tForward[i] + tBackward[i][k];
            s[i][k] = floor(tTotal[i] * imparams->FS); // Floor function to convert it into a int

            if (s[i][k] < imparams->getNumSample())
            { // Incremenets pReal and pImag
                pReal += RFData->getRealRFData(k, s[i][k]);
                pImag += RFData->getImagRFData(k, s[i][k]);
            }
        }
        // Calculates echo magnitude stores scanline array
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2));
        pReal = 0;
        pImag = 0;
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
        data[i] = scanline[i]; // Every element in scanline is copied into data array at corresponding index
}

void BmodeClass::deleteScanline()
{
    delete scanline; // Releases allocated scanline memory
}