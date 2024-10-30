#include <vector>
#include "MergeSortInt.h"
class MPIMergeSortInt:  MergeSortInt
{
    public:
        ~MPIMergeSortInt(){};
        std::vector<int> sort(std::vector<int>& arr, int nproc);
    private:
        void mergesort(std::vector<int>& arr, int nproc);
        void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);

};