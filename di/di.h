#ifndef DI_H
#define DI_H

#include "infra/stream/stream.h"
#include "shared/configuration.h"

class DI
{
public:
    DI();

    void setup();

    Configuration *config;

    Stream *aisInput;
};

#endif // DI_H
