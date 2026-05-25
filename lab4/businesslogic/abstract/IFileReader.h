#pragma once
#include <string>
#include "IFileReader.h"
#include "../NormalizationParams.h"
#include "../Scene.h"

class IFileReader {
public:
    virtual Scene ReadScene(std::string path, NormalizationParameters nparams) = 0;
    ~IFileReader() = default;
};