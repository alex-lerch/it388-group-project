#include <vector>
#include "MergeSortInt.h"
class MPIMergeSortInt: public MergeSortInt
{
    public:
        ~MPIMergeSortInt(){};
        std::vector<int> sort(std::vector<int> arr);
    private:
        void mergesort(std::vector<int>& arr);
        void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);

};