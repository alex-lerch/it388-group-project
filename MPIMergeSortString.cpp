#include "MergeSortString.h"
#include "MPIMergeSortString.h"
#include <vector>
#include <iostream>
#include <string.h>

void MPIMergeSortString::merge(std::vector<std::string>& arr, std::vector<std::string>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {
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

void MPIMergeSortString::mergesort(std::vector<std::string>& arr, int nproc)
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

    int total_size;
    if(rank ==0 )
    {
        for(int i=0; i < n; i++)
        {
            total_size += strlen(arr[i].c_str());
        }
    }
    MPI_Bcast(&total_size, 1, MPI_INT, 0, comm);


    std::vector<char*> temp(work);
    std::vector<std::string> local(work);//local vector for each rank 
    //MPI_Scatter(arr.data(),total_size+work, MPI_CHAR, local.data(), total_size+work, MPI_CHAR,0, comm);//Scatter equal work to processes

    // printf("Got Past Scatter\n");
    // printf("index 0 is %c\n", local[0]);
    int sizes[n];
    if(rank ==0)
    {
        for(int i =0; i < n; i++)//Get the size of every string
        {
            sizes[i] = strlen(arr[i].c_str());
        }
        
    }

    MPI_Bcast(sizes, n,MPI_INT, 0,comm);

    if(rank ==0)
    {
        for(int i=0; i < nThreads; i++)//For each rank i represents the rank
        {
            for(int j=0; j < work; j++)
            {
                if(i==0)
                {
                    temp[j][sizes[j]];//allocate memory
                    temp[j] = (char*)arr[j].c_str();//move string
                }
                else
                {
                    char* buffer = (char*)arr[i*work+j].c_str();
                    MPI_Send(buffer,sizes[i*work+j],MPI_CHAR,i,i,comm);//send string
                    //printf("Rank: 0 Sent\n");
                }
            }
            //printf("Finished Sending\n");
        }
    }
    else
    {
        for(int i=0; i<work; i++)
        {
            temp[i] = new char[sizes[work*rank + i]];//set memory for location
            MPI_Recv(temp[i],sizes[work*rank +i],MPI_CHAR, 0, rank, comm, MPI_STATUS_IGNORE);//Recieve
            //printf("Rank: %d Recieved\n", rank);
        }
        //printf("Rank: %d finished recieving\n", rank);
    }


    for(int i=0; i < work; i++)
    {
        local[i] = string(temp[i]);//convert back to strings
    }
    printf("Rank: %d converted back to strings\n", rank);











    //Sort for each rank
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
            std::vector<std::string> tempVector(work); // temporary vector used to help sort the logical arrays
            merge(local, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
        }
        sizeOfSortedArrays *= 2;// double size of sorted arrays 
    }
    printf("Rank: %d Got past first sort\n", rank);


    if(rank == 1)
    {
        for(int i=0; i < work; i++)
            printf("%d: %s\n",i, local[i].c_str());
    }




    // Gather Section Starts Here
    int local_sizes[work];//array with the local sizes of each string
    temp.clear();
    for(int i=0; i < work; i++)//gets the new local sizes of strings and converts back to char* for mpi
    {
        if(rank != 0)
        {
            temp[i] = (char*)local[i].c_str();
            local_sizes[i] = (int)strlen(local[i].c_str());
        }
        else//rank 0 does not convert because there is no need to send
        {
            local_sizes[i] = (int)strlen(local[i].c_str());
        }
    }

    int new_sizes[n];//new list of all sizes
    printf("Rank: %d converted char* to string\n", rank);
    MPI_Allgather(local_sizes, work, MPI_INT, new_sizes, work, MPI_INT, comm);//gathers all string sizes to all arrays
    printf("gathered succesfully\n");


   if(rank ==0)
   {
        for(int i=0; i < rank; i++)//i represent rank
        {
            for(int j=0; j < work; j++)//j is index value
            {
                if(i==0)//if rank 0 just copy to arr
                {
                    arr[j] = string(local[j]);
                }
                else//otherwise recieve from other thread
                {
                    char buff[new_sizes[i*work+j]];//set memory for buffer
                    MPI_Recv(buff, new_sizes[i*work+j], MPI_CHAR, i,i, comm,MPI_STATUS_IGNORE);//Recieve string
                    arr[i*work+j] = string(buff);
                }
            }
        }
        printf("Rank 0 finished recieving\n");
   }
   else
   {
        for(int i =0; i < work; i++)//Sends each string to rank 0
        {
            MPI_Send(temp[i],new_sizes[i*rank], MPI_CHAR, 0,rank,comm);
        }
        printf("Rank: %d finished sending", rank);
   }
    //Gather Section ends here. 

    // if(rank==0)
    // {
    //     for(int i =0; i < n; i++)
    //     {
    //         printf("%d: %s\n", i, arr[i].c_str());
    //     }
    // }

    //Second sort that merges each threads work
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
                std::vector<std::string> tempVector(n); // temporary vector used to help sort the logical arrays
                merge(arr, tempVector,leftArrayIndex,rightArrayIndex, rightArrayEnd);//merges logical arrays
            }
            sizeOfSortedArrays = sizeOfSortedArrays *2;
        }
    }
    MPI_Barrier(comm);
}

std::vector<std::string> MPIMergeSortString::sort(std::vector<std::string>& arr, int nproc)
{
    mergesort(arr, nproc);
    return arr;
}

void MPIMergeSortString::setComm(MPI_Comm &communicator)
{
    MPIMergeSortString::comm = communicator;
}