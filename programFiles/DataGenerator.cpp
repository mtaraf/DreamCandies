#include "DataGenerator.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


DataGenerator::DataGenerator(int num, string pathName): numCustomers(num), path(pathName){
}

// Creates ASCII input files: Customer.csv, Invoice.csv, Invoice_Item.csv
bool DataGenerator::createFile(){
    // Create new files in the path specified
    fstream customerOut, invoiceOut, invoiceItemOut;
    customerOut.open(path + "customer.csv", ios::out | ios::trunc);
    invoiceOut.open(path + "invoice.csv", ios::out | ios::trunc);
    invoiceItemOut.open(path + "invoice_item.csv", ios::out | ios::trunc);

    // Set file headings
    customerOut << "\"CUSTOMER_CODE\"" << "," << "\"FIRSTNAME\"" << "," << "\"LASTNAME\"" << "\n";
    invoiceOut << "\"CUSTOMER_CODE\"" << "," << "\"INVOICE_CODE\"" << "," << "\"AMOUNT\"" << "," << "\"DATE\"" << "\n";
    invoiceItemOut << "\"INVOICE_CODE\"" << "," << "\"ITEM_CODE\"" << "," << "\"AMOUNT\"" << "," << "\"QUANTITY\"" << "," << "\n";

    // Enter invoice_item data (for simplicity sake only 3 invoice items)
    invoiceItemOut << "\"IN0000001\"" << ","
                   << "\"ICE_CREAM\"" << ","
                   << "\"2\"" << ","
                   << "\"1\"" << ","
                   << "\n";
        
    invoiceItemOut << "\"IN0000002\"" << ","
                   << "\"SANDWICH\"" << ","
                   << "\"1\"" << ","
                   << "\"12\"" << ","
                   << "\n";
        
    invoiceItemOut << "\"IN0000003\"" << ","
                   << "\"TENNIS_BALL\"" << ","
                   << "\"10\"" << ","
                   << "\"123\"" << ","
                   << "\n";
        
    // Populate each file depending on numCustomers
    for (int i=0; i < numCustomers; i++){
        // Enter cusomter data
        customerOut << "\"CUST00000" + to_string(i) + "\"" << ","
                    << "\"First\"" << ","
                    << "\"Last\""
                    << '\n';

        // Enter invoice data
        if (i % 2 == 0){
            invoiceOut << "\"CUST00000" + to_string(i) + "\"" << "," << "\"IN0000001\"" << "," << "\"1\"" << "," << "\"01-Jan-2023\"" << "\n";
        }
        else if (i % 3 == 0){
            invoiceOut << "\"CUST00000" + to_string(i) + "\"" << "," << "\"IN0000002\"" << "," << "\"5\"" << "," << "\"04-Jan-2023\"" << "\n";
        }
        else {
            invoiceOut << "\"CUST00000" + to_string(i) + "\"" << "," << "\"IN0000003\"" << "," << "\"2\"" << "," << "\"08-Jan-2023\"" << "\n";
        }
    }

    // close fstreams
    customerOut.close();
    invoiceOut.close();
    invoiceItemOut.close();

    // return true if file created
    return true;
}