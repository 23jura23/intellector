#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

#include "Board.hpp"

class ViewBaseException: public std::exception {
   public:
    explicit ViewBaseException(const char* val) noexcept;

    virtual const char* what() const noexcept;

   private:
    const char* _msg;
};

class viewBase {
   public:
    virtual ~viewBase() = default;

   protected:
};

#endif
