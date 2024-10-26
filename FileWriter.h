#pragma once
#include <vector>
#include <string>
class FileWriter
{
    public:
        ~FileWriter(){};
        void writeFileInt(const std::vector<int>& arr, char* fileName);
        void writeFileLong(const std::vector<long>& arr, char* fileName);
        void writeFileString(const std::vector<std::string>& arr, char* fileName);
        void writeFileObj(const std::vector<void*>& arr, char* fileName);
};