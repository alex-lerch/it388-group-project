#include "MergeSortInt.h"
#include <vector>
class OMPMergeSortInt: public MergeSortInt
{
    public:
        ~OMPMergeSortInt(){};
        std::vector<int> sort(std::vector<int>& arr);
    private:
        void mergesort(std::vector<int>& arr);
        void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};