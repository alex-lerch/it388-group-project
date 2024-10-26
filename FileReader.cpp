#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "FileReader.h"

void FileReader::readFileInt(std::vector<int>& arr, char* fileName)
{
    // variables used
    std::ifstream infile; // the file that we are reading from
    int currentNum; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process the number
        arr.push_back(currentNum);
    }

    // close the file
    infile.close();
}

void FileReader::readFileLong(std::vector<long>& arr, char* fileName)
{
    // variables used
    std::ifstream infile; // the file that we are reading from
    long currentNum; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process the number
        arr.push_back(currentNum);
    }

    // close the file
    infile.close();
}

void FileReader::readFileString(std::vector<std::string>& arr, char* fileName)
{
    // variables used
    std::ifstream infile; // the file that we are reading from
    std::string currentVal; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentVal) {
        // process the number
        arr.push_back(currentVal);
    }

    // close the file
    infile.close();
}

void FileReader::readFileObj(std::vector<void*>& arr, char* fileName)
{
    // variables used
    std::ifstream infile; // the file that we are reading from
    void* current; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> current) {
        // process the number
        arr.push_back(current);
    }

    // close the file
    infile.close();
}

