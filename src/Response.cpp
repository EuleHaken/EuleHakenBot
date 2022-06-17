#include "Response.hpp"

namespace EuleHakenBot {

Response::Response(bool success)
{
    this->_success = success;
    this->_failure = !success;
}

bool Response::isSuccess() const
{
    return this->_success;
}

bool Response::isFailure() const
{
    return this->_failure;
}

}  // namespace EuleHakenBot
