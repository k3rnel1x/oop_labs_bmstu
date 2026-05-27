#pragma once
#include <string>

class FacadeResult {
public:
    FacadeResult() = default;
    explicit FacadeResult(const char* errorMessage): _errorMessage(errorMessage) {};
    std::string GetErrorMessage();
    explicit operator bool();
    inline bool IsSucceed();

private:
    inline bool _isSucceed();
    std::string _errorMessage;
};


