#pragma once
#include <io/abstract/IFileReader.h>
#include <io/NormalizationParams.h>
#include <renderer/Scene.h>
#include <fstream>
#include <string>

#define OBJFILEFORMAT ".obj"

// TODO!
class ObjFileReader : public IFileReader {
public:
    Scene ReadScene(std::string path, NormalizationParameters nparams);

protected:
    std::ifstream _openValidFile(std::string path);
    std::vector<std::string> _split(const std::string& s, char delim);
};
