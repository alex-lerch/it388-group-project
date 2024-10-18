// simple C++ program to read in an array of longs, sort
// the array using bottom up mergesort 
// and then write the sorted data to a file
// By Mary Elaine Califf and Alex Lerch

/*------------------------------------------------------------------------------*
 *   included libraries                                                         *
 *------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


/*------------------------------------------------------------------------------*
 *   namespaces                                                                 *
 *------------------------------------------------------------------------------*/
using namespace std;


/*------------------------------------------------------------------------------*
 *   function declarations                                                      *
 *------------------------------------------------------------------------------*/
// read the file into the vector
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using bottom up mergesort
void mergesort(vector<long>& arr);

// merge the two logical arrays
void merge(vector<long>& arr, vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);


/*------------------------------------------------------------------------------*
 *   main function                                                              *
 *------------------------------------------------------------------------------*/
// do not modify the main function -- you must complete/modify the methods below
int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " infile outfile\n";
        exit(1);
    }
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    vector<long> theArray;

    readFile(theArray, inFileName);

    mergesort(theArray);

    writeFile(theArray, outFileName);

    return 0;
} // end of main function


/*------------------------------------------------------------------------------*
 *   function definitions                                                       *
 *------------------------------------------------------------------------------*/
// read the file into the vector
void readFile(vector<long>& arr, char* fileName)
{
    // variables used
    ifstream infile; // the file that we are reading from
    long currentNum; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process the number
        arr.push_back(currentNum);
    }

    // close the file
    infile.close();
}



// write the vector to the file
void writeFile(const vector<long>& arr, char* fileName)
{
    // variables used
    ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of longs to the outfile
    for (long num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}



// sort the vector using bottom up mergesort
void mergesort(vector<long>& arr)
{
    // variables used
    int sizeOfSortedArrays; // the size of the logical arrays that are already sorted
    std::vector<long> tempVector(arr.size()); // temporary vector used to help sort the logical arrays
    int leftArrayIndex; // the start index for the left logical array to be sorted
    int rightArrayIndex; // start index for the right logical array to be sorted
    int rightArrayEnd; // end index for the right logical array to be sorted

    // the size of the logical arrays to sort
    sizeOfSortedArrays = 1;

    // while we still have logical arrays to sort
    while (sizeOfSortedArrays < arr.size()) {

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


// merge the two logical arrays
void merge(vector<long>& arr, vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {

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
