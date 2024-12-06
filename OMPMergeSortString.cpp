#include "MergeSortString.h"
#include "OMPMergeSortString.h"
#include <vector>
#include <string>
#include <iostream>
#include <omp.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;


std::vector<std::string> OMPMergeSortString::sort(std::vector<std::string>& arr, int nproc)
{
    mergesort(arr, nproc);
    return arr;
}

void OMPMergeSortString::mergesort(vector<string> &arr, int nproc)
{
    omp_set_num_threads(nproc);
    int arrSize = arr.size();

    #pragma parallel omp for if(arr.size()>1000)
    for (int curSize = 1; curSize <= arrSize - 1; curSize = 2 * curSize) {
        for (int leftStart = 0; leftStart < arrSize - 1; leftStart += 2 * curSize) {
            int mid = min(leftStart + curSize - 1, arrSize - 1);
            int rightEnd = min(leftStart + 2 * curSize - 1, arrSize - 1);

            merge(arr, leftStart, mid, rightEnd);
        }
    }
}

void OMPMergeSortString::merge(vector<string> &arr, int left, int mid, int right)
{
    int leftNumItems = mid - left + 1;
    int rightNumItems = right - mid;

    vector<string> leftArr(leftNumItems);
    vector<string> rightArr(rightNumItems);

    for (int i = 0; i < leftNumItems; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < rightNumItems; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < leftNumItems && j < rightNumItems) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftNumItems) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < rightNumItems) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
