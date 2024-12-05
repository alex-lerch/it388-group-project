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
    int n = arr.size();

    #pragma parallel omp for if(arr.size()>1000)
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            merge(arr, left_start, mid, right_end);
        }
    }
}

void OMPMergeSortString::merge(vector<string> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1);
    vector<string> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
