#include "ViewBase.hpp"

ViewBaseException::ViewBaseException(const char* msg) noexcept
    : _msg { msg }
{
}

const char* ViewBaseException::what() const noexcept
{
    return _msg;
}

