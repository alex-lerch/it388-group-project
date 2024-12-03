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
#include <iostream>
#include <mpi.h>


//Compile: make mpi
//Run mpiexec -n <nThread> ./mpi_merger_sort <datatype> <inputfile>
using namespace std;


int main(int argc, char* argv[])
{
    printf("Program Started\n");
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
    printf("Initalized comm\n");
    if(rank ==0)
    {
        if(argc < 3)
        {
            exit(0);
        }

        file = (char*)argv[2];
        //sortTypeLength = strlen(argv[1]);
        dataTypeLength = strlen(argv[1]);
    }
    //MPI_Bcast(&sortTypeLength,1,MPI_INT,0,comm);//bcast lengths to all threads
    MPI_Bcast(&dataTypeLength,1,MPI_INT,0,comm);
    //char sortType[sortTypeLength];//allocate char buffers
    char dataType[dataTypeLength];
    printf("Broadcast 1\n");
    if(rank ==0)
    {
        //strcpy(sortType,argv[1]);
        strcpy(dataType, argv[1]);
        //sortType[sortTypeLength]='\0';
        dataType[dataTypeLength]='\0';
    }
    //MPI_Bcast(&sortType, sortTypeLength, MPI_CHAR,0,comm);
    MPI_Bcast(&dataType, dataTypeLength, MPI_CHAR,0,comm);
    printf("Broadcast 2");
    //sortType[sortTypeLength]='\0';
    dataType[dataTypeLength]='\0';
    printf("Sort type is %s in rank %d\n", dataType, rank);


    //string sort(sortType);
    string data(dataType);
    cout << "Sorting using MPI" << endl;
    if(data.compare("int")==0)
    {
        //create objects
        MPIMergeSortInt sorter;
        sorter.setComm(comm);

        //printf("rank: %d, nThread: %d\n", rank, nThreads);

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
        FileReader reader;
        FileWriter writer;
        std::vector<long> arr;
        reader.readFileLong(arr, (char*)file);
        //call sort
        start = MPI_Wtime();
        sorter.sort(arr,nThreads);
        elapsed = MPI_Wtime() - start;
        //write to file
        writer.writeFileLong(arr, (char*)"output.txt");
        //deconstuct objects
        sorter.~MPIMergeSortLong();
        reader.~FileReader();
        writer.~FileWriter();
        cout << "Sorting took " << elapsed * 1000<< " milliseconds" <<endl;
    }
    MPI_Finalize();
}
