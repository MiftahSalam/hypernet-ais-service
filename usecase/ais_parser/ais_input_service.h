#ifndef AISINPUTSERVICE_H
#define AISINPUTSERVICE_H

#include "domain/ais/ais_target_repository.h"

#include <QObject>

#include <aistargetdata.h>

class AISInputService : public QObject
{
    Q_OBJECT
public:
    explicit AISInputService(QObject *parent = nullptr, AISTargetRepository *repo = nullptr);

    void createNewTarget(AISLib::AISTargetData *data);

signals:

private:
    AISTargetRepository *aisRepo;
};

#endif // AISINPUTSERVICE_H
