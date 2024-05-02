#include "DataExtractor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

DataExtractor::DataExtractor(string outputFile, string input){
    outputFilePath = outputFile;
    inputFilePath = input;
}


// Find all relevant entries from input files
bool DataExtractor::extractData() {
    // Create set of customer codes from preselectedCustomer File
    set<string> customers;

    ifstream file(inputFilePath);

    if (!file.is_open()){
        cerr << "Failed to open file: " << inputFilePath;
        return 1;
    }

    string line = "";
    // Flush title string
    getline(file, line);

    while (getline(file, line)){
        customers.insert(line);
    }

    file.close();

    bool success = false;

    success = extractCustomerData(customers);
    success = extractInvoiceData(customers);

    if (!success) {
        cerr << "Failed extracting data" << endl;
        return false;
    }

    
    return true;
}


bool DataExtractor::extractCustomerData(set<string> customers){
    // open customer data file
    fstream customerData;
    customerData.open(outputFilePath + "/customer.csv", ios::in);

    // create/open customer output file
    fstream customerOut;
    customerOut.open(outputFilePath + "/customerOutput.csv", ios::out | ios::trunc);

    if (!customerData.is_open() || !customerOut.is_open()){
        cerr << "Failed to open file";
        return 1;
    }

    vector<string> row;
    string word, temp, line;
    int rowNumber = -1;
    
    // Find row number of CUSTOMER_CODES
    getline(customerData,line);
    temp = line;
    int position = 0;

    while (position < temp.size()){
        position = temp.find(",");
        row.push_back(temp.substr(0,position));
        temp.erase(0,position+1);
    }

    // Get row number of CUSTOMER_CODE
    for (int i=0; i<row.size(); i++){
        if (row[i] == "\"CUSTOMER_CODE\""){
            rowNumber = i;
        }
    }

    if (rowNumber == -1) {
        cerr << "No row labeled \"CUSTOMER_CODE\"" << endl;
        return false;
    }

    // Filter through each line of customer data
    while(getline(customerData,line)) {
        row.clear();
        temp = line;
        
        while (position < temp.size()){
            position = temp.find(",");
            row.push_back(temp.substr(0,position));
            temp.erase(0,position+1);
        }

        // If customer is present in the set, add data to output file
        if (customers.count(row[rowNumber])){
            customerOut << line << "\n";
        }
    }

    customerOut.close();
    customerData.close();

    return true;
}




bool DataExtractor::extractInvoiceData(set<string> customers){
    set<string> items;

    // open invoice data file
    fstream invoiceData;
    invoiceData.open(outputFilePath + "/invoice.csv", ios::in);

    // create/open invoice output file
    fstream invoiceOut;
    invoiceOut.open(outputFilePath + "/invoiceOutput.csv", ios::out | ios::trunc);

    if (!invoiceData.is_open() || !invoiceOut.is_open()){
        cerr << "Failed to open file";
        return 1;
    }

    vector<string> row;
    string word, temp, line;
    int customerRowNumber = -1;
    int invoiceCodeRow = -1;
    
    // Find row number of CUSTOMER_CODES and INVOICE_CODES
    getline(invoiceData,line);
    temp = line;
    int position = 0;

    while (position < temp.size()){
        position = temp.find(",");
        row.push_back(temp.substr(0,position));
        temp.erase(0,position+1);
    }

    // Get row number of CUSTOMER_CODE and INVOICE_CODES
    for (int i=0; i<row.size(); i++){
        if (row[i] == "\"CUSTOMER_CODE\""){
            customerRowNumber = i;
        }
        if (row[i] == "\"INVOICE_CODE\""){
            invoiceCodeRow = i;
        }
    }

    if (customerRowNumber == -1) {
        cerr << "No row labeled \"CUSTOMER_CODE\"" << endl;
        return false;
    }

    if (invoiceCodeRow == -1) {
        cerr << "No row labeled \"INVOICE_CODE\"" << endl;
        return false;
    }

    // Filter through each line of invoice data
    while(getline(invoiceData,line)) {
        row.clear();
        temp = line;
        position = 0;
        
        while (position < temp.size()){
            position = temp.find(",");
            row.push_back(temp.substr(0,position));
            temp.erase(0,position+1);
        }

        // If customer is present in the set, add data to output file
        if (customers.count(row[customerRowNumber])){
            invoiceOut << line << endl;
        }

        // Adds invoice_codes to set
        items.insert(row[invoiceCodeRow]);
    }

    // Extract Invoice Item Data
    bool success = extractInvoiceItemData(items);

    if (!success){
        cerr << "Failed to extract item data";
        return 1;
    }

    invoiceData.close();
    invoiceOut.close();


    return true;
}



bool DataExtractor::extractInvoiceItemData(set<string> invoiceCodes){
    // open invoice item data file
    fstream invoiceItemData;
    invoiceItemData.open(outputFilePath + "/invoice_item.csv", ios::in);

    // create/open invoice item output file
    fstream invoiceItemOut;
    invoiceItemOut.open(outputFilePath + "/invoiceItemOutput.csv", ios::out | ios::trunc);

    if (!invoiceItemData.is_open() || !invoiceItemOut.is_open()){
        cerr << "Failed to open file";
        return 1;
    }

    vector<string> row;
    string word, temp, line;
    int rowNumber = -1;
    
    // Find row number of INVOICE_CODE
    getline(invoiceItemData,line);
    temp = line;
    int position = 0;

    while (position < temp.size()){
        position = temp.find(",");
        row.push_back(temp.substr(0,position));
        temp.erase(0,position+1);
    }

    // Get row number of INVOICE_CODE
    for (int i=0; i<row.size(); i++){
        if (row[i] == "\"INVOICE_CODE\""){
            rowNumber = i;
        }
    }

    if (rowNumber == -1) {
        cerr << "No row labeled \"INVOICE_CODE\"" << endl;
        return false;
    }

    // Filter through each line of invoice item data
    while(getline(invoiceItemData,line)) {
        row.clear();
        temp = line;
        position = 0;
        
        while (position < temp.size()){
            position = temp.find(",");
            row.push_back(temp.substr(0,position));
            temp.erase(0,position+1);
        }

        // If invoice code is present in the set, add data to output file
        if (invoiceCodes.count(row[rowNumber])){
            invoiceItemOut << line << "\n";
        }
    }

    invoiceItemOut.close();
    invoiceItemData.close();

    return true;
}