#include "ais_input_service.h"

AISInputService::AISInputService(QObject *parent, AISTargetRepository *repo)
    : QObject{parent}, aisRepo(repo)
{
    if(!repo) qFatal("ais repo is null");
}

void AISInputService::createOrUpdateTarget(AISLib::AISTargetData *data)
{
    qDebug()<<Q_FUNC_INFO<<"ais mmsi"<<data->MMSI;

    //convert AISTargetData to AISTargetModel
    auto model = toModel(data);
    model.timestamp = QDateTime::currentMSecsSinceEpoch();

    if(aisRepo->FindOne(model.MMSI)) aisRepo->Update(model);
    else aisRepo->Insert(model);
}

void AISInputService::update()
{
    //check ais expired/stale target
    qDebug()<<Q_FUNC_INFO;
}

AISTargetModel AISInputService::toModel(const AISLib::AISTargetData *data)
{
    AISTargetModel model;

    model.MMSI = data->MMSI;
    model.IMO = data->IMO;
    model.Class = data->Class;
    model.VendorID = data->VendorID;
    model.ShipType = data->ShipType;
    model.ShipName = data->ShipName;
    model.ShipNameExtension = data->ShipNameExtension;
    model.CallSign = data->CallSign;
    model.NavStatus = data->NavStatus;
    model.Lat = data->Lat;
    model.Lon = data->Lon;
    model.SOG = data->SOG;
    model.HDG = data->HDG;
    model.COG = data->COG;
    model.ROTAIS = data->ROTAIS;
    model.ROTIND = data->ROTIND;
    model.DimA = data->DimA;
    model.DimB = data->DimB;
    model.DimC = data->DimC;
    model.DimD = data->DimD;
    model.Draft = data->Draft;
    model.Euro_Length = data->Euro_Length;
    model.Euro_Beam = data->Euro_Beam;
    model.Euro_Draft = data->Euro_Draft;
    model.Euro_VIN = data->Euro_VIN;
    model.UN_shiptype = data->UN_shiptype;
    model.ETA_Mo = data->ETA_Mo;
    model.ETA_Day = data->ETA_Day;
    model.ETA_Hr = data->ETA_Hr;
    model.ETA_Min = data->ETA_Min;
    model.ETA_Simulation = data->ETA_Simulation;
    model.Destination = data->Destination;
    model.PositionReportTicks = data->PositionReportTicks;
    model.StaticReportTicks = data->StaticReportTicks;

    return model;
}
