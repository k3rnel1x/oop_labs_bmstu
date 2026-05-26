#include "FacadeResult.h"

std::string FacadeResult::GetErrorMessage()
{
    return _errorMessage;
}

FacadeResult::operator bool()
{
    return _isSucceed();
}

inline bool FacadeResult::IsSucceed()
{
    return _isSucceed();
}

inline bool FacadeResult::_isSucceed()
{
    return _success;
}