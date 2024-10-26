#pragma once
#include <vector>
#include <string>
class FileReader
{
    public:
        ~FileReader(){};

        void readFileInt(std::vector<int>& arr, char* fileName);
        void readFileLong(std::vector<long>& arr, char* fileName);
        void readFileString(std::vector<std::string>& arr, char* fileName);
        void readFileObj(std::vector<void*>& arr, char* fileName);
};