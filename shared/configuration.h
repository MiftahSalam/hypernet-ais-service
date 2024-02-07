#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QDir>

const QString NON_VOLATILE_AIS_INPUT_CONFIG = "AIS/input/config";

class Configuration
{
public:        
    Configuration(Configuration &other) = delete;
    void operator=(const Configuration&) = delete;
    ~Configuration();

    static Configuration* getInstance(const QString path);

    QString getAisInputConfig() const;

protected:
    Configuration(QString path);

private:
    static Configuration *config;

    QString aisInputConfig;
};

#endif // CONFIGURATION_H
