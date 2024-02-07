#ifndef ERRFILEOPERATION_H
#define ERRFILEOPERATION_H

#include "base_error.h"

class ErrFileNotFound: public BaseError
{
public:
    ErrFileNotFound();
};

class ErrFileCannotOpened: public BaseError
{
public:
    ErrFileCannotOpened();
};

#endif // ERRFILEOPERATION_H
