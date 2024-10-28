#include <string.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdint.h>
#include "FileReader.h"
#include "FileWriter.h"
#include "MergeSortInt.h"
#include "MergeSortLong.h"
#include "MPIMergeSortInt.h"
#include "MPIMergeSortLong.h"
#include "OMPMergeSortInt.h"
#include "OMPMergeSortLong.h"
#include <iostream>
#include <omp.h>


using namespace std;



int main(int argc, char** argv)
{
    int nThreads;
    if(argc < 5)
    {
        exit(0);
    }
    nThreads = atoi((char*)argv[1]);
    string sortType = (char*)argv[2];
    cout << "sortType is " << sortType << "." << endl;
    string dataType = (char*)argv[3];
    cout << "dataType is " << dataType << "."  << endl;
    const char* file = (char*)argv[4];
    double start =0;
    double elapsed =0;


    if(sortType.compare("MPI")==0)
    {
        cout << "Sorting using MPI" << endl;
        if(dataType.compare("int")==0)
        {
            cout << "Sorting using ints" << endl;
            //create objects
            MPIMergeSortInt sorter;
            FileReader reader;
            FileWriter writer;
            std::vector<int> arr;
            reader.readFileInt(arr, (char*)file);
            //call sort
            start = omp_get_wtime();
            sorter.sort(arr);
            cout << "index 0 is" << arr[0] << endl;
            elapsed = omp_get_wtime() - start;
            //write to file
            writer.writeFileInt(arr, (char*)"output.txt");
            //deconstuct objects
            sorter.~MPIMergeSortInt();
            reader.~FileReader();
            writer.~FileWriter();
            cout << "Sorting took " << elapsed << " seconds" <<endl;
        }
        if(dataType.compare("long")==0)
        {
            cout << "Sorting using longs" << endl;
            //create objects
            MPIMergeSortLong sorter;
            FileReader reader;
            FileWriter writer;
            std::vector<long> arr;
            reader.readFileLong(arr, (char*)file);
            //call sort
            start = omp_get_wtime();
            sorter.sort(arr);
            elapsed = omp_get_wtime() - start;
            //write to file
            writer.writeFileLong(arr, (char*)"output.txt");
            //deconstuct objects
            sorter.~MPIMergeSortLong();
            reader.~FileReader();
            writer.~FileWriter();
            cout << "Sorting took " << elapsed << " seconds" <<endl;
        }
    }
    else if(sortType.compare("OMP")==0)
    {
        cout << "Sorting using OMP" << endl;
        if(dataType.compare("int")==0)
        {
            //create objects
            OMPMergeSortInt sorter;
            FileReader reader;
            FileWriter writer;
            std::vector<int> arr;
            reader.readFileInt(arr, (char*)file);
            //call sort
            start = omp_get_wtime();
            sorter.sort(arr);
            elapsed = omp_get_wtime() - start;
            //write to file
            writer.writeFileInt(arr, (char*)"output.txt");
            //deconstuct objects
            sorter.~OMPMergeSortInt();
            reader.~FileReader();
            writer.~FileWriter();
        }
        if(dataType.compare("long")==0)
        {
            //create objects
            OMPMergeSortLong sorter;
            FileReader reader;
            FileWriter writer;
            std::vector<long> arr;
            reader.readFileLong(arr, (char*)file);
            //call sort
            start = omp_get_wtime();
            sorter.sort(arr);
            elapsed = omp_get_wtime() - start;
            //write to file
            writer.writeFileLong(arr, (char*)"output.txt");
            //deconstuct objects
            sorter.~OMPMergeSortLong();
            reader.~FileReader();
            writer.~FileWriter();
            cout << "Sorting took " << elapsed << " seconds" <<endl;
        }
    }
    else
        cout << "Invalid parallelism choice. Options are MPI or OMP" << endl;
}

