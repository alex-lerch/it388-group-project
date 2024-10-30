#include "MergeSortInt.h"
#include <vector>
class OMPMergeSortInt: public MergeSortInt
{
    public:
        ~OMPMergeSortInt(){};
        std::vector<int> sort(std::vector<int>& arr, int nproc);
    private:
        void mergesort(std::vector<int>& , int nproc);
        void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};