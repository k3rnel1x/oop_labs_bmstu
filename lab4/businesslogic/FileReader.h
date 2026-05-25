#pragma once
#include "abstract/IFileReader.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>
#define CSVFILEFORMAT ".csv"

class FileReader : public IFileReader {
public:
    Scene ReadScene(std::string path, NormalizationParameters nparams);

private:
    std::ifstream _openValidFile(std::string path);
};
