#pragma once
#include <string>
#include "IFileReader.h"
#include "NormalizationParams.h"

class IFileReader {
public:
    virtual Scene ReadScene(std::string path, NormalizationParameters nparams);
};