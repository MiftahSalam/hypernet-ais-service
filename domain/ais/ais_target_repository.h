#ifndef AIS_TARGET_REPOSITORY_H
#define AIS_TARGET_REPOSITORY_H

#include <list>

#include "domain/ais/ais_target_model.h"

class AISTargetRepository
{
public:
    static AISTargetRepository *Create();

    virtual ~AISTargetRepository() {}

    virtual void Insert(const AISTargetModel &TrackModel) = 0;
    virtual AISTargetModel *FindOne(const int &trackId) = 0;
    virtual std::list<AISTargetModel *> FindAll() = 0;
    virtual void Update(const AISTargetModel &TrackModel) = 0;
    virtual void Remove(const int &trackId) = 0;

protected:
    AISTargetRepository() {}

private:
    AISTargetRepository &operator=(
        const AISTargetRepository &repo);
};

#endif // AIS_TARGET_REPOSITORY_H
