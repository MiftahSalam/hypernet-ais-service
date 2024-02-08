#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QDir>

const QString NON_VOLATILE_AIS_INPUT_CONFIG = "AIS/input/config";
const QString NON_VOLATILE_AIS_OUTPUT_CONFIG = "AIS/output/config";

class Configuration
{
public:        
    Configuration(Configuration &other) = delete;
    void operator=(const Configuration&) = delete;
    ~Configuration();

    static Configuration* getInstance(const QString path);

    QString getAisInputConfig() const;
    QString getAisOutputConfig() const;

protected:
    Configuration(QString path);

private:
    static Configuration *config;

    QString aisInputConfig; //format -> serial;In;/dev/pts/4:38400:8:1:No:None
    QString aisOutputConfig; //format -> localhost:8083;3000
};

#endif // CONFIGURATION_H
