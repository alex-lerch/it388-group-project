#include <vector>
#include <stdlib.h>
#include "FileWriter.h"
using namespace std;


int main(int argc, char* argv[])
{
    // std::vector<int> arr;

    // for(int i=0; i < 1000000; i++)
    // {
    //     int num = rand()%2000000;
    //     printf("%d: %d\n",i,num);
    //     arr.push_back(num);
    // }
    // FileWriter writer;
    // writer.writeFileInt(arr, (char*)"d1000000.rand");

    std::vector<long> arr;

    for(int i=0; i < 1000; i++)
    {
        long num = rand()%100000000000000000;
        printf("%d: %ld\n",i,num);
        arr.push_back(num);
    }
    FileWriter writer;
    writer.writeFileLong(arr, (char*)"l1000.rand");

}