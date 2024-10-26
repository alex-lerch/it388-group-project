#include <vector>
#include <string>
#include "FileWriter.h"
#include <fstream>


void FileWriter::writeFileInt(const std::vector<int>& arr, char* fileName)
{
    // variables used
    std::ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of ints to the outfile
    for (int num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}

void FileWriter::writeFileLong(const std::vector<long>& arr, char* fileName)
{
    // variables used
    std::ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of longs to the outfile
    for (long num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}

void FileWriter::writeFileString(const std::vector<std::string>& arr, char* fileName)
{
    // variables used
    std::ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of strings to the outfile
    for (std::string num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}

void FileWriter::writeFileObj(const std::vector<void*>& arr, char* fileName)
{
    // variables used
    std::ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of objs to the outfile
    for (void* num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}

