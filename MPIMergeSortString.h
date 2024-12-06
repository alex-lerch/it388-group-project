#include <vector>
#include "MergeSortString.h"
#include <mpi.h>
class MPIMergeSortString:  MergeSortString
{
    
    public:
        MPI_Comm  comm;
        ~MPIMergeSortString(){};
        std::vector<std::string> sort(std::vector<std::string>& arr, int nproc);
        void setComm(MPI_Comm &communicator);
    private:
        void mergesort(std::vector<std::string>& arr, int nproc);
        void merge(std::vector<std::string>& arr, std::vector<std::string>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};  