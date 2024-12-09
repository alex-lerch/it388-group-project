#include <string.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdint.h>
#include "FileReader.h"
#include "FileWriter.h"
#include "MergeSortInt.h"
#include "MergeSortLong.h"
#include "MergeSortString.h"
#include "OMPMergeSortInt.h"
#include "OMPMergeSortLong.h"
#include "OMPMergeSortString.h"
#include <iostream>
#include <omp.h>


//Compile: make omp
//Run: ./omp_merge_sort <nThread> <dataType> <inputFile>
using namespace std;


int main(int argc, char* argv[])
{
    int nThreads;
    int rank;
    int dataSize;
    const char* file;
    double start, elapsed;

    file = (char*)argv[3];
    nThreads = atoi(argv[1]);
    string data(argv[2]);

    cout << "Sorting using OMP" << endl;
    if(data.compare("int")==0)
    {
        cout << "Sorting using ints with " << nThreads << " threads" << endl;
        //create objects
        OMPMergeSortInt sorter;
        FileReader reader;
        FileWriter writer;
        std::vector<int> arr;
        
        reader.readFileInt(arr, (char*)file);
        //call sort
        start = omp_get_wtime();
        sorter.sort(arr,nThreads);
        elapsed = omp_get_wtime() - start;
        //write to file
        writer.writeFileInt(arr, (char*)"output.txt");
        cout << "Sorting using OMP took " << elapsed * 1000<< " milliseconds" <<endl;
        //deconstuct objects
        sorter.~OMPMergeSortInt();
        reader.~FileReader();
        writer.~FileWriter();
    }
    if(data.compare("long")==0)
    {
        cout << "Sorting using longs with " << nThreads << " threads" << endl;
        //create objects
        OMPMergeSortLong sorter;
        FileReader reader;
        FileWriter writer;
        std::vector<long> arr;
        reader.readFileLong(arr, (char*)file);

        //call sort
        start = omp_get_wtime();
        sorter.sort(arr,nThreads);
        elapsed = omp_get_wtime() - start;
        //write to file
        writer.writeFileLong(arr, (char*)"output.txt");
        cout << "Sorting took " << elapsed * 1000 << " milliseconds" <<endl;
        //deconstuct objects
        sorter.~OMPMergeSortLong();
        reader.~FileReader();
        writer.~FileWriter();
        
    }
    if(data.compare("string")==0)
    {
        //create objects
        OMPMergeSortString sorter;
        FileReader reader;
        FileWriter writer;
        std::vector<std::string> arr;
        cout << "read file" << endl;
        reader.readFileString(arr, (char*)file);
        //call sort
        start = omp_get_wtime();
        cout << "got start time" << endl;
        sorter.sort(arr,nThreads);
        elapsed = omp_get_wtime() - start;

        //write to file
        writer.writeFileString(arr, (char*)"output.txt");
        cout << "Sorting took " << elapsed * 1000 << " milliseconds" <<endl;
        //deconstuct objects
        sorter.~OMPMergeSortString();
        reader.~FileReader();
        writer.~FileWriter();

    }

}