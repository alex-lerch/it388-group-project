#include <vector>
#include "MergeSortLong.h"
class MPIMergeSortLong: MergeSortLong
{
    public:
        ~MPIMergeSortLong(){};
        std::vector<long> sort(std::vector<long>& arr, int nproc, int rank);
    private:
        void mergesort(std::vector<long>& arr, int nproc, int rank);
        void merge(std::vector<long>& arr, std::vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);

        virtual std::vector<long> sort(std::vector<long>& arr, int nproc){};
        virtual void mergesort(std::vector<long>& arr, int nproc){};
};