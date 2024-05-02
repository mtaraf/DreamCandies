#include <string>
#include <set>
#pragma once
using namespace std;

class DataExtractor {
    private: 
        string preselectedCustomers = "../asciiFiles/testSample.csv";
        string outputFilePath;
        string inputFilePath;

    public:
        bool extractData();
        bool extractCustomerData(set<string> customers);
        bool extractInvoiceData(set<string> customers);
        bool extractInvoiceItemData(set<string> invoiceCodes);
        DataExtractor(string outputFile, string input);
};