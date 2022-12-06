#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // Initializing all variables
    numElement = 0;
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // Re-Initialzing the variables to their input variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix();                      // Calls function createDataMatrix
    int num = loadRFData(dataMatrix, imagFile, realFile); // Calls function loadRFData with parameter values
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // To release the data stored in dataMatrix, the destructor calls the deleteDataMatrix function.
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData;                   // Define a type complex double pointer called RFData
    RFData = new complex *[numElement]; // Creates a pointer array of type complex with numElement elements

    for (int i = 0; i < numElement; i++)
        RFData[i] = new complex[numSample]; // For every element in RFData, creates a block of type complex with size numSample
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{
    const int MAX = 100;
    char line[MAX];

    if (imagFile->fail() || realFile->fail()) // Returns -1 if the files fail to open
        return -1;

    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            imagFile->getline(line, MAX);   // Gets each line from the imaginary file
            RFData[i][j].imag = atof(line); // Converts the character array to float and then stores it in the imaginary part of the RFData array

            realFile->getline(line, MAX);   // Gets each line from the real file
            RFData[i][j].real = atof(line); // Converts the character array to float and then stores it in the real part of the RFData array
        }
    }

    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    // Returns the real component of the stored data
    return dataMatrix[element][sample].real;
}

float dataBuffer::getImagRFData(int element, int sample)
{
    // Returns the imaginary component of the stored data
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    for (int i = 0; i < numElement; i++) // Deletes every element in dataMatrix
        delete dataMatrix[i];
    delete dataMatrix; // Deletes the array itself
}