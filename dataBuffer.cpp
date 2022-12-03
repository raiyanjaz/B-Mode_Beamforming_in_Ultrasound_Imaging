#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer() {
    // Initializing all variables
    numElement = 0;
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline) {
    // Re-Initialzing the variables to 
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix(); // Calls function createDataMatrix
    int num = loadRFData(dataMatrix, imagFile, realFile); // Calls function loadRFData with parameter values
} 

dataBuffer::~dataBuffer() {
    deleteDataMatrix(); // To release the data stored in dataMatrix, the destructor calls the deleteDataMatrix function.
}

complex **dataBuffer::createDataMatrix() {
    complex **RFData; // Define a type complex double pointer called RFData
    RFData = new complex *[numElement]; // Creates a pointer array of type complex with numElement elements

    for (int i = 0; i < numElement; i++) 
        RFData[i] = new complex[numSample]; // For every element in RFData, creates a block of type complex with size numSample
    return RFData;    
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) { 
    if (imagFile->fail() || realFile->fail()) // Returns -1 if real or imag file cannot be open
        return -1;
    
    // Two temporary character arrays to store each line in files
    const int MAX = 100;
    char line[MAX];
    char line2[MAX];

    // Counters to be used in the while loop
    int elementCounter = 0; 
    int sampleCounter = 0;
   
    while (imagFile->getline(line, MAX) && realFile->getline(line2, MAX)) { // Runs until end of file (EOF) returns false in both
        // Converts char array to float and stores in the imaginary and real part of RFData
        RFData[elementCounter][sampleCounter].imag = atof(line); 
        RFData[elementCounter][sampleCounter].real = atof(line2);
        sampleCounter++;
        if (sampleCounter == numSample) { // Every 3338 samples, element counter is increased by 1.
            elementCounter++;
            sampleCounter = 0;
        }
    }
}

float dataBuffer::getRealRFData(int element,int sample) {
    // Returns the real component of the stored data
    return dataMatrix[element][sample].real; 
}

float dataBuffer::getImagRFData(int element,int sample) {
    // Returns the imaginary component of the stored data
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix() {
    for (int i = 0; i < numElement; i++) // Deletes every element in dataMatrix
        delete dataMatrix[i];
    delete dataMatrix; // Deletes the array itself
}