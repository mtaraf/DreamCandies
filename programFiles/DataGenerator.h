#include <string>
#pragma once

using namespace std;


class DataGenerator {
    private: 
        int numCustomers;
        string path;

    public:
        DataGenerator(int num, string pathName);
        bool createFile();
};