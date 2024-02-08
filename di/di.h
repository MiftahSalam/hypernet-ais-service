#ifndef DI_H
#define DI_H

#include "infra/stream/stream.h"
#include "interface/ais_input.h"
#include "interface/ais_output/ais_output.h"
#include "shared/configuration.h"
#include "usecase/ais_sender/ais_output_service.h"

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
    AISOutputService *aisOutputService;

    AISInput *inputAis;
    AISOutput *outputAis;
};

#endif // DI_H
