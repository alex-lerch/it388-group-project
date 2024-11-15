#pragma once
#include <vector>
#include <string>
class MergeSortString
{
    public: 
        virtual ~MergeSortString()=0;
        virtual std::vector<std::string> sort(std::vector<std::string>& arr, int nproc)=0;
        virtual void mergesort(std::vector<std::string>& arr, int nproc)=0;
        virtual void merge(std::vector<std::string>& arr, std::vector<std::string>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd)=0;
};