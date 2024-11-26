#include "MergeSortString.h"
#include "OMPMergeSortString.h"
#include <vector>
#include <string>
#include <omp.h>

void OMPMergeSortString::merge(std::vector<std::string>& arr, std::vector<std::string>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {
    // variables used
    int leftArrayEnd = rightArrayIndex - 1; // end index of the left array
    int tempPosition = leftArrayIndex; // a temporary index used similarly to an iterator
    int numElements = rightArrayEnd - leftArrayIndex + 1; // the number of elements to be sorted

    // while both logical arrays have items left to merge
    while (leftArrayIndex <= leftArrayEnd && rightArrayIndex <= rightArrayEnd) {
        
        // if left is less than or equal to right
        //if (arr[leftArrayIndex] <= arr[rightArrayIndex]) {
        if (arr[leftArrayIndex].compare(arr[rightArrayIndex]) <= 0) {
            
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

void OMPMergeSortString::mergesort(std::vector<std::string>& arr, int nproc)
{
    // variables used
    int sizeOfSortedArrays; // the size of the logical arrays that are already sorted
    std::vector<std::string> tempVector(arr.size()); // temporary vector used to help sort the logical arrays
    int leftArrayIndex; // the start index for the left logical array to be sorted
    int rightArrayIndex; // start index for the right logical array to be sorted
    int rightArrayEnd; // end index for the right logical array to be sorted

    // the size of the logical arrays to sort
    sizeOfSortedArrays = 1;

    // while we still have logical arrays to sort
    #pragma parallel omp for firstprivate(rightArrayEnd, rightArrayIndex, leftArrayEnd, leftArrayIndex) lastprivate(rightArrayEnd, rightArrayIndex, leftArrayEnd, leftArrayIndex) if(arr.size()>1000)
    for( int i = 0; i < arr.size(); i++){    
        // set left index to 0
        leftArrayIndex = 0;

        // check for real group
        while ( leftArrayIndex < (arr.size() - sizeOfSortedArrays) ) {
            
            // calculate the start index for the right array
            rightArrayIndex = leftArrayIndex + sizeOfSortedArrays;

            // calculate rightArrayEnd
            if ( arr.size() - 1 < (rightArrayIndex + (sizeOfSortedArrays - 1)) ) {
                rightArrayEnd = arr.size() - 1;
            }
            else {
                rightArrayEnd = rightArrayIndex + (sizeOfSortedArrays - 1);
            }

            // merge the two logical arrays
            merge(arr, tempVector, leftArrayIndex, rightArrayIndex, rightArrayEnd);

            // move start index for the left array to the next unsorted logical array
            leftArrayIndex += 2 * sizeOfSortedArrays;
        }

        // copy what's left over
        for (int i = leftArrayIndex; i < arr.size(); i++) {
            tempVector[i] = arr[i];
        }

        // swap arr and tempVector
        arr.swap(tempVector);

        // update the size of sorted arrays
        sizeOfSortedArrays *= 2;
    }
}

std::vector<std::string> OMPMergeSortString::sort(std::vector<std::string>& arr, int nproc)
{
    mergesort(arr, nproc);
    return arr;
}