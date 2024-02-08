#include "di.h"
#include "interface/ais_output/ais_output_websocket_server.h"

const QString COMMON_CONFIG_PATH = QDir::homePath()+QDir::separator()+".hypernet/ais_service.conf";

DI::DI()
{
    config = Configuration::getInstance(COMMON_CONFIG_PATH);
}

DI::~DI()
{
    delete inputAis;
    delete outputAis;
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
    outputAis = new AISOutput_WebSocketServer(nullptr, aisOutputService, config->getAisOutputConfig());

    outputAis->Open();
}
