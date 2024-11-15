#include "MergeSortString.h"
#include <vector>
#include <string>
class OMPMergeSortString: MergeSortString
{
    public:
        ~OMPMergeSortString(){};
        std::vector<std::string> sort(std::vector<std::string>& arr, int nproc);
    private:
        void mergesort(std::vector<std::string>& arr,int nproc);
        void merge(std::vector<std::string>& arr, std::vector<std::string>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);
};