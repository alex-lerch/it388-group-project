#include "MergeSortString.h"
#include <vector>
#include <string>
using namespace std;
class OMPMergeSortString: MergeSortString
{
    public:
        ~OMPMergeSortString(){};
        std::vector<std::string> sort(std::vector<std::string>& arr, int nproc);
    private:
        void mergesort(vector<string>& arr,int nproc);
        void merge(vector<string>& arr, int left, int mid, int right);
};