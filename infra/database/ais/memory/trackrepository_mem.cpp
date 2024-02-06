#include "infra/database/ais/memory/trackrepository_mem.h"

AISTargetRepository_Mem::AISTargetRepository_Mem()
{
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
    }
}

std::list<AISTargetModel*> AISTargetRepository_Mem::FindAll()
{
    QList<AISTargetModel*> listTarget = model.values();
    return listTarget.toStdList();
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
