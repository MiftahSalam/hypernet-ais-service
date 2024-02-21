#include "ais_input_service.h"

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
LOG4QT_DECLARE_STATIC_LOGGER(logger, AISInputService)
#else
#include <QDebug>
#endif

AISInputService::AISInputService(QObject *parent, AISTargetRepository *repo)
    : QObject{parent}, aisRepo(repo)
{
#ifdef USE_LOG4QT
    if(!repo) logger()->fatal("ais repo is null");
#else
    if(!repo) qFatal("ais repo is null");
#endif
}

void AISInputService::createOrUpdateTarget(AISLib::AISTargetData *data)
{
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - ais mmsi: "<<data->MMSI;
#else
    qDebug()<<Q_FUNC_INFO<<" - ais mmsi: "<<data->MMSI;
#endif

    //convert AISTargetData to AISTargetModel

    if(aisRepo->FindOne(data->MMSI))
    {
        auto model = aisRepo->FindOne(data->MMSI);
        model->timestamp = QDateTime::currentMSecsSinceEpoch();
        updateModel(model, data);
    }
    else
    {
        auto model = toModel(data);
        model.timestamp = QDateTime::currentMSecsSinceEpoch();
        aisRepo->Insert(model);
    }
}

void AISInputService::updateModel(AISTargetModel *model, const AISLib::AISTargetData *data)
{
    switch (data->MID) {
    case 1:
    case 2:
    case 3:
        model->NavStatus = data->NavStatus;
        model->SOG = data->SOG;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }
        model->COG = data->COG;
        model->HDG = data->HDG;
        model->ROTAIS = data->ROTAIS;
        model->ROTIND = data->ROTIND;
        model->Class = data->Class;

        break;
    case 4:
        model->SOG = data->SOG;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }
        model->COG = data->COG;
        model->HDG = data->HDG;
        model->Class = data->Class;

        break;
    case 5:
        //todo check ais_indication_version
        model->IMO = data->IMO;
        model->CallSign = data->CallSign;
        model->ShipName = data->ShipName;
        model->ShipType = data->ShipType;
        model->DimA = data->DimA;
        model->DimB = data->DimB;
        model->DimC = data->DimC;
        model->DimD = data->DimD;
        model->ETA_Day = data->ETA_Day;
        model->ETA_Hr = data->ETA_Hr;
        model->ETA_Min = data->ETA_Min;
        model->ETA_Mo = data->ETA_Mo;
        model->Destination = data->Destination;
        model->Draft = data->Draft;
        model->StaticReportTicks = data->StaticReportTicks;

        break;
    case 8:
        model->Euro_Beam = data->Euro_Beam;
        model->Euro_Draft = data->Euro_Draft;
        model->UN_shiptype = data->UN_shiptype;
        model->Euro_Length = data->Euro_Length;
        model->Euro_VIN = data->Euro_VIN;

        break;
    case 9:
        model->SOG = data->SOG;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }
        model->COG = data->COG;

        break;
    case 18:
        model->NavStatus = data->NavStatus;
        model->SOG = data->SOG;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }
        model->COG = data->COG;
        model->HDG = data->HDG;
        model->Class = data->Class;

        break;
    case 19:
        model->NavStatus = data->NavStatus;
        model->SOG = data->SOG;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }
        model->COG = data->COG;
        model->HDG = data->HDG;
        model->Class = data->Class;
        model->ShipName = data->ShipName;
        model->ShipType = data->ShipType;
        model->DimA = data->DimA;
        model->DimB = data->DimB;
        model->DimC = data->DimC;
        model->DimD = data->DimD;
        model->Class = data->Class;

        break;
    case 21:
        model->IMO = data->IMO;
        model->ShipType = data->ShipType;
        model->SOG = data->SOG;
        model->COG = data->COG;
        model->HDG = data->HDG;
        model->ROTAIS = data->ROTAIS;
        model->Draft = data->Draft;
        model->DimA = data->DimA;
        model->DimB = data->DimB;
        model->DimC = data->DimC;
        model->DimD = data->DimD;
        model->NavStatus = data->NavStatus;
        model->ShipName = data->ShipName;
        model->ShipNameExtension = data->ShipNameExtension;
        model->Class = data->Class;
        if (!data->b_positionDoubtful) {
            model->Lat = data->Lat;
            model->Lon = data->Lon;
        }

        break;
    case 24:
        model->ShipType = data->ShipType;
        model->DimA = data->DimA;
        model->DimB = data->DimB;
        model->DimC = data->DimC;
        model->DimD = data->DimD;
        model->VendorID = data->VendorID;
        model->ShipName = data->ShipName;
        model->CallSign = data->CallSign;

        break;
    default:
        break;
    }

    aisRepo->Update(*model);
}

AISTargetModel AISInputService::toModel(AISLib::AISTargetData *data)
{
    AISTargetModel model;

    model.MMSI = data->MMSI;
    model.IMO = data->IMO;
    model.Class = data->Class;
    model.ClassStr = data->getClassString(true).toStdString();
    model.VendorID = data->VendorID;
    model.ShipType = data->ShipType;
    model.ShipTypeString = data->getShipTypeString().toStdString();
    model.ShipName = data->ShipName;
    model.ShipNameExtension = data->ShipNameExtension;
    model.CallSign = data->CallSign;
    model.NavStatus = data->NavStatus;
    model.NavStatusString = data->getNavStatusString().toStdString();
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
