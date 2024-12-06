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
#include "MPIMergeSortInt.h"
#include "MPIMergeSortLong.h"
#include "MPIMergeSortString.h"
#include <iostream>
#include <mpi.h>


//Compile: make mpi
//Run mpiexec -n <nThread> ./mpi_merger_sort <datatype> <inputfile>
using namespace std;


int main(int argc, char* argv[])
{
    int nThreads;
    int rank;
    int dataSize;

    //int sortTypeLength;
    int dataTypeLength;
    const char* file;
    double start, elapsed;
    MPI_Comm  comm;
    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nThreads);
    MPI_Comm_rank(comm, &rank);

    if(rank ==0)
    {
        if(argc < 3)
        {
            exit(0);
        }

        file = (char*)argv[2];
        dataTypeLength = strlen(argv[1]);
    }
    MPI_Bcast(&dataTypeLength,1,MPI_INT,0,comm);
    char dataType[dataTypeLength];
    if(rank ==0)
    {
        strcpy(dataType, argv[1]);
        dataType[dataTypeLength]='\0';
    }
    MPI_Bcast(&dataType, dataTypeLength, MPI_CHAR,0,comm);

    dataType[dataTypeLength]='\0';
    string data(dataType);

    cout << "Sorting using MPI\n" << endl;
    if(data.compare("int")==0)
    {
        //create objects
        MPIMergeSortInt sorter;
        sorter.setComm(comm);
        FileReader reader;
        FileWriter writer;
        std::vector<int> arr;
        
        if(rank ==0)//rank 0 reads the file
        {
            reader.readFileInt(arr, (char*)file);
        }

        //call sort            
        MPI_Barrier(comm);
        start = MPI_Wtime();
        sorter.sort(arr,nThreads);
        MPI_Barrier(comm);
        elapsed = MPI_Wtime() - start;
        if(rank ==0)
        {
            cout << "Sorting took " << elapsed * 1000<< " milliseconds" <<endl;
            //write to file
            writer.writeFileInt(arr, (char*)"output.txt");    
        }
        //deconstuct objects
        sorter.~MPIMergeSortInt();
        reader.~FileReader();
        writer.~FileWriter();
    }
    if(data.compare("long")==0)
    {
        cout << "Sorting using longs" << endl;
        //create objects
        MPIMergeSortLong sorter;
        sorter.setComm(comm);
        FileReader reader;
        FileWriter writer;
        std::vector<long> arr;

        if(rank ==0)
        {
            reader.readFileLong(arr, (char*)file);
        }
        
        //call sort
        MPI_Barrier(comm);
        start = MPI_Wtime();
        sorter.sort(arr,nThreads);
        MPI_Barrier(comm);
        elapsed = MPI_Wtime() - start;
        //write to file
        if(rank ==0)
        {
            cout << "Sorting took " << elapsed * 1000<< " milliseconds" <<endl;
            writer.writeFileLong(arr, (char*)"output.txt");    
        }
        //deconstuct objects
        sorter.~MPIMergeSortLong();
        reader.~FileReader();
        writer.~FileWriter();
    }
    if(data.compare("string")==0)
    {
        cout << "Sorting using strings" << endl;
        //create objects
        MPIMergeSortString sorter;
        sorter.setComm(comm);
        FileReader reader;
        FileWriter writer;
        std::vector<std::string> arr;

        if(rank ==0)
        {
            reader.readFileString(arr, (char*)file);
        }
        
        //call sort
        MPI_Barrier(comm);
        start = MPI_Wtime();
        sorter.sort(arr,nThreads);
        MPI_Barrier(comm);
        elapsed = MPI_Wtime() - start;
        //write to file
        if(rank ==0)
        {
            cout << "Sorting took " << elapsed * 1000<< " milliseconds" <<endl;
            writer.writeFileString(arr, (char*)"output.txt");    
        }
        //deconstuct objects
        sorter.~MPIMergeSortString();
        reader.~FileReader();
        writer.~FileWriter();
    }
    MPI_Finalize();
}
