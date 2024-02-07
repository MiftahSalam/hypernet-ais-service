#include "di.h"

const QString COMMON_CONFIG_PATH = QDir::homePath()+QDir::separator()+".ais_service.conf";

DI::DI()
{
    config = Configuration::getInstance(COMMON_CONFIG_PATH);
}

void DI::setup()
{
    aisInput = new Stream(nullptr, COMMON_CONFIG_PATH);
}
