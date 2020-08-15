#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

#include <stdexcept>

#include "Model/ModelImpl/Board.hpp"

class ViewBaseException : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};

class viewBase {
   public:
    virtual ~viewBase() = default;

   protected:
};

#endif
