#ifndef DI_H
#define DI_H

#include "infra/stream/stream.h"
#include "interface/ais_input.h"
#include "shared/configuration.h"

class DI
{
public:
    DI();
    ~DI();

    void setup();

    Configuration *config;

    Stream *aisInput;

    AISTargetRepository *aisRepo;

    AISInputService *aisInputService;

    AISInput *inputAis;
};

#endif // DI_H
