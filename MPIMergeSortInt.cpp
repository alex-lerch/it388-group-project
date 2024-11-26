#include "MergeSortInt.h"
#include "MPIMergeSortInt.h"
#include <vector>
#include <iterator>
#include <iostream>

void MPIMergeSortInt::merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {
    // variables used
    int leftArrayEnd = rightArrayIndex - 1; // end index of the left array
    int tempPosition = leftArrayIndex; // a temporary index used similarly to an iterator
    int numElements = rightArrayEnd - leftArrayIndex + 1; // the number of elements to be sorted

    // while both logical arrays have items left to merge
    while (leftArrayIndex <= leftArrayEnd && rightArrayIndex <= rightArrayEnd) {
        
        // if left is less than or equal to right
        if (arr[leftArrayIndex] <= arr[rightArrayIndex]) {
            
            // add left item and increment
            tempVector[tempPosition++] = arr[leftArrayIndex++];
        }
        else { // right is less than left

            // add right item and increment
            tempVector[tempPosition++] = arr[rightArrayIndex++];
        }
    }

    // while there are left over items in the left logical array
    while (leftArrayIndex <= leftArrayEnd) {

        // add item and increment
        tempVector[tempPosition++] = arr[leftArrayIndex++];
    }

    // while there are left over items in the righ logical array
    while (rightArrayIndex <= rightArrayEnd) {

        // add item and increment
        tempVector[tempPosition++] = arr[rightArrayIndex++];
    }

}

void MPIMergeSortInt::mergesort(std::vector<int>& arr, int nproc)
{
    // variables used
    int sizeOfSortedArrays; // the size of the logical arrays that are already sorted
    
    // int leftArrayIndex; // the start index for the left logical array to be sorted
    // int rightArrayIndex; // start index for the right logical array to be sorted
    // int rightArrayEnd; // end index for the right logical array to be sorted



    // while we still have logical arrays to sort
    int nThreads;
    int rank;
    int n;//size of array
    int* array;//use as array instead of vector
    MPI_Comm_size(comm, &nThreads);
    MPI_Comm_rank(comm, &rank);
    //int sorted[arr.size()];

    // the size of the logical arrays to sort
    if(rank ==0)
    {
        sizeOfSortedArrays = 1;
        n = arr.size();//size of array
        array = &arr[0];//use as array instead of vector
    }
    printf("got to loop \n");
    MPI_Bcast(&sizeOfSortedArrays, 1, MPI_INT, 0, comm);//send size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);//send n to all processes
    int work = n/nThreads;//work for each thread to do 
    int local[work];//local array for each thread
    while(sizeOfSortedArrays< n)
    {
        int local_work = sizeOfSortedArrays*2;
        MPI_Scatter(array,work, MPI_INT, &local, work, MPI_INT,0, comm);//Scatter equal work to processes
        std::cout << "Scattered\n" << std::endl;
        std::vector<int> temp(local, local+local_work);//convert local to vector to use merge
        for(int i =0; i < work; i = i + local_work)// loop for every 2 logical arrays to merge
        {
            std::vector<int> tempVector(work); // temporary vector used to help sort the logical arrays
            merge(temp, tempVector,i,i+sizeOfSortedArrays, i+local_work);//merges logical arrays
        }
        printf("Did merges\n");

        MPI_Gather(&local,work,MPI_INT,array,work, MPI_INT,0,comm);//gather back to 0 
        std::cout << "Gathered\n" << std::endl;
        if(rank ==0 )
        {
            sizeOfSortedArrays = sizeOfSortedArrays * 2;// double size of sorted arrays 
        }
        MPI_Bcast(&sizeOfSortedArrays, 1, MPI_INT, 0, comm);//send size to all processes
    }
}

std::vector<int> MPIMergeSortInt::sort(std::vector<int>& arr, int nproc)
{
    mergesort(arr, nproc);
    return arr;
}

void MPIMergeSortInt::setComm(MPI_Comm &communicator)
{
    MPIMergeSortInt::comm = communicator;
}