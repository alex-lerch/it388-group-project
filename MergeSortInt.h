#pragma once
#include <vector>
class MergeSortInt
{
    public: 
        virtual ~MergeSortInt()=0;
        virtual std::vector<int> sort(std::vector<int> arr)=0;
        virtual void mergesort(std::vector<int>& arr)=0;
        virtual void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd)=0;
};
