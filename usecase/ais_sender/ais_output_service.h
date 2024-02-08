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

private slots:
    void onTimeout();

private:
    QTimer timer;
    int timeout;

    AISTargetRepository *aisRepo;

    void populateConfig(const QString cfg);
};

#endif // AISOUTPUTSERVICE_H
