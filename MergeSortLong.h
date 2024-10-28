#pragma once
#include <vector>
class MergeSortLong
{
    public: 
        virtual ~MergeSortLong()=0;
        virtual std::vector<long> sort(std::vector<long>& arr)=0;
        virtual void mergesort(std::vector<long>& arr)=0;
        virtual void merge(std::vector<long>& arr, std::vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd)=0;
};
