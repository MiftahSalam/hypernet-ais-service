#ifndef AIS_TARGET_REPOSITORY_MEM_H
#define AIS_TARGET_REPOSITORY_MEM_H

#include <QStandardItemModel>

#include "domain/ais/ais_target_repository.h"

class AISTargetRepository_Mem: public AISTargetRepository
{
public:
    AISTargetRepository_Mem();

    ~AISTargetRepository_Mem() override { }
    void Insert(const AISTargetModel& targetModel) override;
    AISTargetModel* FindOne(const int& mmsi) override;
    std::list<AISTargetModel*> FindAll() override;
    void Update(const AISTargetModel& targetModel) override;
    void Remove(const int& mmsi) override;

private:
    QMap<int, AISTargetModel*> model;
};

AISTargetRepository* AISTargetRepository::Create()
{
    return new AISTargetRepository_Mem();
}

#endif // AIS_TARGET_REPOSITORY_MEM_H
