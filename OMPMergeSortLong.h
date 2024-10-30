#include <vector>
#include "MergeSortLong.h"
class OMPMergeSortLong: public MergeSortLong
{
    public:
        ~OMPMergeSortLong(){};
        std::vector<long> sort(std::vector<long>& arr, int nproc);
    private:
        void mergesort(std::vector<long>& arr,int nproc);
        void merge(std::vector<long>& arr, std::vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};