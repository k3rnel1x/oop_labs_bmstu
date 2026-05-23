#pragma once
#include <string>

class FacadeResult {
public:
    std::string GetErrorMessage();
    bool IsSuccess();
private:
    bool _isSucceed();
};
