#ifndef AIS_TARGET_REPOSITORY_MEM_H
#define AIS_TARGET_REPOSITORY_MEM_H

#include <QMap>

#include "domain/ais/ais_target_repository.h"

class AISTargetRepository_Mem: public AISTargetRepository
{
public:
    AISTargetRepository_Mem();

    // AISTargetRepository interface
    ~AISTargetRepository_Mem() override { }

    size_t Count() override;
    void Insert(const AISTargetModel& targetModel) override;
    AISTargetModel* FindOne(const int& mmsi) override;
    std::list<AISTargetModel*> FindAll() override;
    std::list<AISTargetModel *> Find(const AISTargetQueryFilter filter) override;
    void Update(const AISTargetModel& targetModel) override;
    void Remove(const int& mmsi) override;

private:
    QMap<int, AISTargetModel*> model;

public:
};

AISTargetRepository* AISTargetRepository::Create()
{
    return new AISTargetRepository_Mem();
}

#endif // AIS_TARGET_REPOSITORY_MEM_H
