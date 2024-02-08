#ifndef AISOUTPUTSERVICE_H
#define AISOUTPUTSERVICE_H

#include "domain/ais/ais_target_repository.h"

#include <QTimer>
#include <QObject>

class AISOutputService : public QObject
{
    Q_OBJECT
public:
    explicit AISOutputService(
            QObject *parent = nullptr,
            AISTargetRepository *repo = nullptr,
            QString cfg = "");

signals:
    void signalSendAISTargetRaw(const QByteArray data);

private slots:
    void onTimeout();

private:
    QTimer timer;
    int timeout;
    size_t sendLimit;
    size_t dataSendCounter;

    AISTargetRepository *aisRepo;

    void populateConfig(const QString cfg);
    void sendTarget();
};

#endif // AISOUTPUTSERVICE_H
