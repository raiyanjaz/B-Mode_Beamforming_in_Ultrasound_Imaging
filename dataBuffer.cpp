#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer() {
    int numElement;
    int numSample;
    int scanline;

    complex** dataMatrix;
    dataMatrix = new [numElement];

}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{

} 

dataBuffer::~dataBuffer()
{

}

complex **dataBuffer::createDataMatrix()
{
 
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 

}

float dataBuffer::getRealRFData(int element,int sample)
{

}
float dataBuffer::getImagRFData(int element,int sample)
{

}

void dataBuffer::deleteDataMatrix()
{

}




