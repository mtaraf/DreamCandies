#include "DataGenerator.h"
#include "DataExtractor.h"
#include <string>
#include <iostream>

using namespace std; 

int main() 
{
    bool success = false;
    string str = "../asciiFiles/";


    // Create DataGenerator object
    DataGenerator inputFileObject(3000, str);
    
    success = inputFileObject.createFile();

    if (!success){
        return -1;
    }
    success = false;

    // Create Data Extractor object
    string outputPath = "../asciiFiles/";
    string inputFilePath = "../asciiFiles/preselected_customers.csv";
    DataExtractor extractor(outputPath, inputFilePath);

    // Extract data
    success = extractor.extractData();

    if (!success){
        return -1;
    }

    return 0; 
}