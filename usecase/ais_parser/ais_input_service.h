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

    void createOrUpdateTarget(AISLib::AISTargetData *data);

signals:

private slots:

private:
    AISTargetRepository *aisRepo;

    AISTargetModel toModel(AISLib::AISTargetData *data);
    void updateModel(AISTargetModel *model, const AISLib::AISTargetData *data);
};

#endif // AISINPUTSERVICE_H
