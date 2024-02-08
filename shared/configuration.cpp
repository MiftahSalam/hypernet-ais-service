#include "configuration.h"
#include "shared/error/err_file.h"

#include "qdebug.h"
#include <QSettings>

Configuration* Configuration::config = nullptr;

Configuration::Configuration(QString path)
{
    QSettings config(path, QSettings::IniFormat);

    aisInputConfig = config.value(NON_VOLATILE_AIS_INPUT_CONFIG, "").toString();
}

Configuration *Configuration::getInstance(const QString path)
{
    qDebug()<<Q_FUNC_INFO<<"path"<<path;

    if(config == nullptr)
    {
        if (!QFile::exists(path)) {
            throw ErrFileNotFound();
        }

        config = new Configuration(path);
    }

    return config;
}

QString Configuration::getAisInputConfig() const
{
    return aisInputConfig;
}

Configuration::~Configuration()
{
}
