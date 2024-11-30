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
    
    int leftArrayIndex; // the start index for the left logical array to be sorted
    int rightArrayIndex; // start index for the right logical array to be sorted
    int rightArrayEnd; // end index for the right logical array to be sorted



    // while we still have logical arrays to sort
    int nThreads;
    int rank;
    int n;//size of array
    MPI_Comm_size(comm, &nThreads);
    MPI_Comm_rank(comm, &rank);

    // the size of the logical arrays to sort
    if(rank ==0)
    {
        sizeOfSortedArrays = 1;
        n = arr.size();//size of array
    }
 
    MPI_Bcast(&sizeOfSortedArrays, 1, MPI_INT, 0, comm);//send size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);//send n to all processes
    int work = n/nThreads;//work for each thread to do 
    std::cout << "Work for rank: " << rank << " is " << work <<std::endl;
    std::cout << "SortedSize for rank: " << rank << " is " << sizeOfSortedArrays <<std::endl;
    std::cout << "N for rank: " << rank << " is " << n <<std::endl;

    std::vector<int> local(work); 
    MPI_Scatter(arr.data(),work, MPI_INT, local.data(), work, MPI_INT,0, comm);//Scatter equal work to processes

    while(sizeOfSortedArrays < work)
    {
        int merge_work = sizeOfSortedArrays*2;
        
        for(int i =0; i < work; i += merge_work)// loop for every 2 logical arrays to merge
        {
            leftArrayIndex = i;
            rightArrayIndex = leftArrayIndex+sizeOfSortedArrays;
            rightArrayEnd = rightArrayIndex+sizeOfSortedArrays-1;
            std::vector<int> tempVector(work); // temporary vector used to help sort the logical arrays
            merge(local, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
        }
        sizeOfSortedArrays *= 2;// double size of sorted arrays 
    }
    MPI_Gather(local.data(),work,MPI_INT,arr.data(),work, MPI_INT,0,comm);//gather back to 0 

    if(rank ==0)// merges the work each thread did
    {
        int merge_work = sizeOfSortedArrays*2;
        for(int i =0; i < arr.size(); i += merge_work)// merges the work each thread did
        {
            leftArrayIndex = i;
            rightArrayIndex = leftArrayIndex+sizeOfSortedArrays;
            rightArrayEnd = rightArrayIndex+sizeOfSortedArrays-1;
            std::vector<int> tempVector(n); // temporary vector used to help sort the logical arrays
            merge(arr, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
        }
    }
    if(rank==0)
    {
        for(int i =0; i < n; i++)
        {
            printf("%d: %d\n",i, arr[i]);
        }
    }
    MPI_Barrier(comm);
    std::cout << "Finished Sorting" << std::endl; 
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