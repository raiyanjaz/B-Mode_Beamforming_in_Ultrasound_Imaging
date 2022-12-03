#include "BmodeClass.h"

BmodeClass::BmodeClass() {
    // Initializing all variables
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;    
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline) {
    imparams = params;
    RFData = data;
    line = numline;

    scanline = createScanline(imparams->getNumPixel());
    beamform();    
}

BmodeClass::~BmodeClass() {
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel) {
    float *mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform() {
    // Initialize variables
    float tForward = 0;
    float tBackward = 0;
    float tTotal = 0;
    int s = 0;

    float pReal = 0;
    float pImag = 0;

    for (int i = 0; i < imparams->getNumPixel(); i++) {
        tForward = (imparams->getYPosition(line, i)) / imparams->SOS; // calculation for tforward

        for (int k = 0; k < imparams->getNumElement(); k++) {
            // tBackward = sqrt(pow(y, 2) + pow(elementPosition[k], 2)) / SoS;
            tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS; // calculation for tBackward
            tTotal = tForward + tBackward;                                                                                                                           // calculation for tTotal
            s = floor(tTotal * imparams->FS);

            if (s < imparams->getNumSample()) {
                pReal += RFData->getRealRFData(k, s); // calculation for pReal
                pImag += RFData->getImagRFData(k, s); // calculation for sample number (integer)
            }                                                // calculation for pImag
        }
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2)); // calculation to determine the echo magnitude and then store the value directly into scanline array
        pReal = 0;
        pImag = 0;
    }
}

void BmodeClass::getScanline(float *data) {
    for (int i = 0; i < imparams->getNumPixel(); i++)
        data[i] = scanline[i];
}

void BmodeClass::deleteScanline() {
    delete scanline; // Deletes the scanline
}