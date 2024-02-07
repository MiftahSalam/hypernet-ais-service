#include "ais_input_service.h"

AISInputService::AISInputService(QObject *parent, AISTargetRepository *repo)
    : QObject{parent}, aisRepo(repo)
{

}

void AISInputService::createNewTarget(AISLib::AISTargetData *data)
{
    //convert AISTargetData to AISTargetModel
//    aisRepo->Insert()
}
