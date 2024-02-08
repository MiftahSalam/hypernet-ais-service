#ifndef AIS_TARGET_REPOSITORY_H
#define AIS_TARGET_REPOSITORY_H

#include <list>

#include "domain/ais/ais_target_model.h"

struct AISTargetQueryFilter
{
    size_t startIndex;
    int limit;
};

class AISTargetRepository
{
public:
    static AISTargetRepository *Create();

    virtual ~AISTargetRepository() {}

    virtual size_t Count() = 0;
    virtual void Insert(const AISTargetModel &TrackModel) = 0;
    virtual AISTargetModel *FindOne(const int &trackId) = 0;
    virtual std::list<AISTargetModel *> FindAll() = 0;
    virtual std::list<AISTargetModel *> Find(const AISTargetQueryFilter filter) = 0;
    virtual void Update(const AISTargetModel &TrackModel) = 0;
    virtual void Remove(const int &trackId) = 0;

protected:
    AISTargetRepository() {}

private:
    AISTargetRepository &operator=(
        const AISTargetRepository &repo);
};

#endif // AIS_TARGET_REPOSITORY_H
