#include <vector>
#include "MergeSortLong.h"
#include <mpi.h>
class MPIMergeSortLong: MergeSortLong
{
    
    public:
        MPI_Comm  comm;
        ~MPIMergeSortLong(){};
        std::vector<long> sort(std::vector<long>& arr, int nproc);
        void setComm(MPI_Comm &communicator);
    private:
        void mergesort(std::vector<long>& arr, int nproc);
        void merge(std::vector<long>& arr, std::vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};