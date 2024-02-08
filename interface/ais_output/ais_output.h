#ifndef AIS_OUTPUT_H
#define AIS_OUTPUT_H

#include "usecase/ais_sender/ais_output_service.h"

#include <QObject>

class AISOutput: public QObject
{
    Q_OBJECT
public:
    AISOutput(
            QObject *parent = nullptr,
            AISOutputService* service = nullptr,
            QString config = "")
        : QObject(parent), m_config(config) {
        m_service = service;

        connect(m_service, &AISOutputService::signalSendAISTargetRaw, this, &AISOutput::SendRaw);
    }

    virtual void Open() = 0;

protected:
    virtual void Close() = 0;
    virtual void InitConfig() = 0;

protected slots:
    virtual void SendRaw(const QByteArray data) = 0;

protected:
    QString m_config;
    AISOutputService* m_service;
};
#endif // AIS_OUTPUT_H
