#include <vector>
#include "MergeSortInt.h"
#include <mpi.h>
class MPIMergeSortInt:  MergeSortInt
{
    
    public:
        MPI_Comm  comm;
        ~MPIMergeSortInt(){};
        std::vector<int> sort(std::vector<int>& arr, int nproc);
        void setComm(MPI_Comm &communicator);
    private:
        void mergesort(std::vector<int>& arr, int nproc);
        void merge(std::vector<int>& arr, std::vector<int>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
        
};