#include "di.h"

const QString COMMON_CONFIG_PATH = QDir::homePath()+QDir::separator()+".hypernet/ais_service.conf";

DI::DI()
{
    config = Configuration::getInstance(COMMON_CONFIG_PATH);
}

DI::~DI()
{
    delete inputAis;
    delete aisInputService;
    delete aisRepo;
    delete aisInput;
    delete config;
}

void DI::setup()
{
    aisInput = new Stream(nullptr, config->getAisInputConfig());

    aisRepo = AISTargetRepository::Create();

    aisInputService = new AISInputService(nullptr, aisRepo);
    aisOutputService = new AISOutputService(nullptr, aisRepo, config->getAisOutputConfig());

    inputAis = new AISInput(aisInput, aisInputService);
}
