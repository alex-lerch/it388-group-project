#pragma once
#include <vector>
class MergeSortObj
{
    public: 
        virtual ~MergeSortObj()=0;
        virtual std::vector<void*> sort(std::vector<void*> arr)=0;
        virtual void mergesort(std::vector<void*>& arr)=0;
        virtual void merge(std::vector<void*>& arr, std::vector<void*>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd)=0;
};
