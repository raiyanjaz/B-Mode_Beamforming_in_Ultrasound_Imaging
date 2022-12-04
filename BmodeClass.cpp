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
    imparams = params;
    RFData = data;
    line = numline;

    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    // Initialize variables
    float tForward = 0;
    float tBackward = 0;
    float tTotal = 0;
    int s = 0;

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        // Initialize pReal and pImag
        float pReal = 0;
        float pImag = 0;

        tForward = (imparams->getYPosition(line, i)) / imparams->SOS; // Calculate tForward

        for (int k = 0; k < imparams->getNumElement(); k++)
        {
            // Calculates for tBackward and tTotal
            tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS;
            tTotal = tForward + tBackward;
            s = floor(tTotal * imparams->FS); // Floor function to convert it into a int

            if (s < imparams->getNumSample())
            { // Incremenets pReal and pImag
                pReal += RFData->getRealRFData(k, s);
                pImag += RFData->getImagRFData(k, s);
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