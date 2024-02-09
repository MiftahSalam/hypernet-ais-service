#include "infra/database/ais/memory/ais_target_repository_mem.h"

#include <QList>
#include <QDebug>

AISTargetRepository_Mem::AISTargetRepository_Mem()
{
}

size_t AISTargetRepository_Mem::Count()
{
    return model.size();
}

void AISTargetRepository_Mem::Insert(const AISTargetModel &targetModel)
{
    AISTargetModel *track = model.value(targetModel.MMSI);
    if (track == nullptr) {
        model.insert(targetModel.MMSI,new AISTargetModel(targetModel));
    }
}

void AISTargetRepository_Mem::Update(const AISTargetModel &targetModel)
{
    AISTargetModel *track = model.value(targetModel.MMSI);
    if (track) {
        model.insert(targetModel.MMSI,new AISTargetModel(targetModel));
    } else qWarning()<<Q_FUNC_INFO<<"ais data not found";
}

std::list<AISTargetModel*> AISTargetRepository_Mem::FindAll()
{
    QList<AISTargetModel*> listTarget = model.values();
    return std::list<AISTargetModel*>(listTarget.begin(), listTarget.end());
}

std::list<AISTargetModel *> AISTargetRepository_Mem::Find(const AISTargetQueryFilter filter)
{
    QList<AISTargetModel*> listTarget = model.values();
    QList<AISTargetModel*> listTargetFiltered;

    int counter = filter.startIndex;
    int limit = counter + filter.limit;
    while (counter < limit && counter < listTarget.size()) {
        listTargetFiltered.append(listTarget.at(counter));
        counter++;
    }

    return std::list<AISTargetModel*>(listTargetFiltered.begin(), listTargetFiltered.end());
}

AISTargetModel* AISTargetRepository_Mem::FindOne(const int &mmsi)
{
    AISTargetModel* target = model.value(mmsi);

    return target;
}

void AISTargetRepository_Mem::Remove(const int &mmsi)
{
    model.remove(mmsi);
}
