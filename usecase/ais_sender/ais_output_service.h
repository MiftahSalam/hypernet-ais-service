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
    int expiredTimeout;
    size_t sendLimit;
    size_t dataSendCounter;

    AISTargetRepository *aisRepo;

    std::list<AISTargetModel*> getTargets();
    void populateConfig(const QString cfg);
    QList<AISTargetModel *> sendTarget();
    void updateDataSendCounter();
    void checkAndDeleteStaleTarget(QList<AISTargetModel *> targets);
};

#endif // AISOUTPUTSERVICE_H
