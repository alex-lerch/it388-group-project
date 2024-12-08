#include "MergeSortInt.h"
#include "MPIMergeSortInt.h"
#include <vector>
#include <iostream>

void MPIMergeSortInt::merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {
    int leftArrayEnd = rightArrayIndex - 1; // end index of the left array
    int numElements = rightArrayEnd - leftArrayIndex + 1; // the number of elements to be sorted
    int rank;
    MPI_Comm_rank(comm, &rank);
    if(numElements ==1)//handles case where there is only 1 element to be sorted
    {
        return;
    }

    int r= rightArrayIndex;//right iterator
    int l=leftArrayIndex;//left iterator
    int i=0;//index for tempVector
    while(r <= rightArrayEnd && l <= leftArrayEnd && i < numElements)//merges the two logical arrays
    {
        if(arr[l] <= arr[r])
        {
            tempVector[i]=arr[l];
            l++;
            i++;
        }
        else
        {
            tempVector[i]=arr[r];
            r++;
            i++;
        }
    }

    while(l <= leftArrayEnd)//copy left over left data if any
    {
        tempVector[i] = arr[l];
        i++;
        l++;
    }

    while(r <= rightArrayEnd)//copy left over right data if any
    {
        tempVector[i] = arr[r];
        i++;
        r++;
    }

    //Copy values back to origional array. 
    for(int j = leftArrayIndex; j <= rightArrayEnd; j++)
    {
        arr[j] = tempVector[j-leftArrayIndex];
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
    int work;
    MPI_Comm_size(comm, &nThreads);
    MPI_Comm_rank(comm, &rank);

    // the size of the logical arrays to sort
    if(rank ==0)
    {
        sizeOfSortedArrays = 1;//initial size of logical arrays
        n = arr.size();//size of array
        work = n/nThreads;//work for each thread to do 
        
    }
 
    MPI_Bcast(&sizeOfSortedArrays, 1, MPI_INT, 0, comm);//send size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);//send n to all processes
    MPI_Bcast(&work, 1, MPI_INT, 0, comm);

    std::vector<int> local(work);//local vector for each rank 
    MPI_Scatter(arr.data(),work, MPI_INT, local.data(), work, MPI_INT,0, comm);//Scatter equal work to processes

    while(sizeOfSortedArrays <= work)
    {
        int merge_work = sizeOfSortedArrays*2;
        
        for(int i =0; i < work; i += merge_work)// loop for every 2 logical arrays to merge
        {
            leftArrayIndex = i;
            rightArrayIndex = leftArrayIndex+sizeOfSortedArrays;
            rightArrayEnd = rightArrayIndex+sizeOfSortedArrays-1;
            int numElements = rightArrayEnd - leftArrayIndex + 1;
            //if statements handle case with odd amount of elements
            if(rightArrayIndex >= work)
            {
                rightArrayIndex = work-1;//Sets to end of array
            }
            if(rightArrayEnd >= work-1)
            {
                rightArrayEnd = work-1;//Sets to end of array
            }
            if(numElements < merge_work)
            {
                rightArrayEnd = work-1;
            }
            std::vector<int> tempVector(work); // temporary vector used to help sort the logical arrays
            merge(local, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
            printf("Rank: %d mergerd\n", rank);
        }
        sizeOfSortedArrays *= 2;// double size of sorted arrays 
    }

    MPI_Gather(local.data(),work,MPI_INT,arr.data(),work, MPI_INT,0,comm);//gather back to 0 

    if(rank ==0)// merges the work each thread did
    {
        sizeOfSortedArrays = work;//Each threads section is sorted
        while (sizeOfSortedArrays <= n)
        {
            int merge_work = sizeOfSortedArrays*2;
            for(int i =0; i < n; i += merge_work)// merges the work each thread did
            {
                leftArrayIndex = i;
                rightArrayIndex = leftArrayIndex+sizeOfSortedArrays;
                rightArrayEnd = rightArrayIndex+sizeOfSortedArrays-1;
                int numElements = rightArrayEnd - leftArrayIndex + 1;
                if(rightArrayEnd >= n)
                {
                    rightArrayEnd = n-1;
                }
                std::vector<int> tempVector(n); // temporary vector used to help sort the logical arrays
                merge(arr, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
            }
            sizeOfSortedArrays = sizeOfSortedArrays *2;
        }
    }
    MPI_Barrier(comm);
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