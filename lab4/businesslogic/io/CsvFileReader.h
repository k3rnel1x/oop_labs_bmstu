#pragma once
#include <io/abstract/IFileReader.h>
#include <io/NormalizationParams.h>
#include <renderer/Scene.h>
#include <fstream>
#include <string>

#define CSVFILEFORMAT ".csv"

class CsvFileReader : public IFileReader {
public:
    Scene ReadScene(std::string path, NormalizationParameters nparams);

private:
    std::ifstream _openValidFile(std::string path);
};
