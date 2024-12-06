#pragma once
#include <vector>
#include <string>
using namespace std;
class MergeSortString
{
    public: 
        virtual ~MergeSortString()=0;
        virtual std::vector<std::string> sort(std::vector<std::string>& arr, int nproc)=0;
        virtual void mergesort(vector<string>& arr, int nproc)=0;
        virtual void merge(vector<string>& arr, int left, int mid, int right)=0;
};