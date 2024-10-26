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
    const char* sortType = (char*)argv[2];
    const char* dataType = (char*)argv[3];
    const char* file = (char*)argv[4];
    double start =0;
    double elapsed =0;


    if(strcmp(sortType,"MPI")==0)
    {
        if(strcmp(dataType,"int"))
        {
            //create objects
            MPIMergeSortInt sorter;
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
            sorter.~MPIMergeSortInt();
            reader.~FileReader();
            writer.~FileWriter();
            cout << "Sorting took " << elapsed << " seconds" <<endl;
        }
        if(strcmp(dataType,"long"))
        {
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
    else if(strcmp(sortType,"OMP")==0)
    {
        if(strcmp(dataType,"int"))
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
        if(strcmp(dataType,"long"))
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

